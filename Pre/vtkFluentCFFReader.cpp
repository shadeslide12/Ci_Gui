#include "vtkFluentCFFReader.h"
#include "FileIO/MeshReader.h"
#include "Geometry/Mesh.h"
#include "Geometry/Element.h"
#include "Geometry/Vertex.h"

#include <vtkUnstructuredGrid.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkTriangle.h>
#include <vtkQuad.h>
#include <vtkTetra.h>
#include <vtkHexahedron.h>
#include <vtkPyramid.h>
#include <vtkWedge.h>
#include <iostream>
#include <stdexcept>

vtkFluentCFFReader::vtkFluentCFFReader(const std::string& filename) 
    : fileName(filename), nNode(0), cellDim(3), phyDim(3), nodes(nullptr), meshData(nullptr)
{
    if (!filename.empty()) {
        setFileName(filename);
    }
    else {
        std::cerr << "File name is empty" << std::endl;
    }
}

vtkFluentCFFReader::~vtkFluentCFFReader()
{

    if (meshData) {
        delete meshData;
    }
    if (nodes) {
        delete[] nodes;
    }
}

void vtkFluentCFFReader::setFileName(const std::string& name)
{

    fileName = name;
    
    //* Clear existing data
    unstructuredGrid.clear();
    sectionName.clear();
    
    if (meshData) {
        delete meshData;
        meshData = nullptr;
    }
    if (nodes) {
        delete[] nodes;
        nodes = nullptr;
    }
    
    try {
        readMeshData();
        extractNodeCoordinates();
        extractCellConnectivity(); 
        buildVTKDataStructures();
    } catch (const std::exception& e) {
        FATAL(("Failed to read Fluent CAS.H5 file: " + std::string(e.what())).c_str());
    }

    getDataSetName();
}

void vtkFluentCFFReader::readMeshData()
{
    if (fileName.empty()) {
        FATAL("No file name set");
    }

    if (!meshData) {
        meshData = new Geometry::Mesh(false); 
    }

    try {
        std::string extension = ".cas.h5";
        auto mr = FileIO::GetMeshReaderFactory().Create(extension, fileName, meshData);

        mr->Process();
        mr->SetConnectivity();
        mr->SetBoundaryVertex();
        nNode = static_cast<int>(meshData->m_numGlobVertex);
        cellDim = meshData->m_dim;
        phyDim = meshData->m_dim;
    }
    catch (const std::exception& e) {
        if (meshData) {
            delete meshData;
            meshData = nullptr;
        }
        FATAL(("Error: " + std::string(e.what())).c_str());
    }
}

void vtkFluentCFFReader::extractNodeCoordinates()
{
    if (!meshData) {
        FATAL("Mesh data not available");
    }
    nodes = new Node[nNode];
    const auto& vertices = meshData->m_vertexList;
    
    for (uint32_t i = 0; i < meshData->m_numGlobVertex; ++i) {
        const auto& vertex = vertices[i];
        const double* coord = vertex.GetCoordPtr();
        
        nodes[i][0] = static_cast<float>(coord[0]);
        nodes[i][1] = static_cast<float>(coord[1]);
        nodes[i][2] = (phyDim > 2) ? static_cast<float>(coord[2]) : 0.0f;
    }
    
    std::cout << "[DEBUG] Node coordinates extracted: " << nNode << " nodes" << std::endl;
}

void vtkFluentCFFReader::extractCellConnectivity()
{
    if (!meshData) {
        FATAL("Mesh data not available");
    }
    
    const auto& elements = meshData->m_cellList;
    
    std::map<int, std::vector<size_t>> cellTypeGroups;
    
    for (size_t i = 0; i < elements.size(); ++i) {
        const auto& element = elements[i];
        int geometryType = element->GetTag();
        cellTypeGroups[geometryType].push_back(i);
    }
    
    unstructuredGrid.resize(cellTypeGroups.size() + 1); 
    sectionName.resize(cellTypeGroups.size() + 1);
    
    unstructuredGrid[0] = vtkSmartPointer<vtkUnstructuredGrid>::New();
    sectionName[0] = "Empty";
    
    size_t sectionIndex = 1;
    for (const auto& group : cellTypeGroups) {
        int geometryType = group.first;
        const auto& cellIndices = group.second;
        
        unstructuredGrid[sectionIndex] = vtkSmartPointer<vtkUnstructuredGrid>::New();
        
        std::string typeName = getElementTypeName(geometryType);
        sectionName[sectionIndex] = typeName + "_Section";
        
        sectionIndex++;
    }
    
}

void vtkFluentCFFReader::buildVTKDataStructures()
{
    if (!meshData || !nodes) {
        FATAL("Mesh data or nodes not available");
    }

    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    points->SetNumberOfPoints(nNode);
    
    for (int i = 0; i < nNode; ++i) {
        points->SetPoint(i, nodes[i][0], nodes[i][1], nodes[i][2]);
    }

    const auto& elements = meshData->m_cellList;
    std::map<int, std::vector<size_t>> cellTypeGroups;
    
    for (size_t i = 0; i < elements.size(); ++i) {
        const auto& element = elements[i];
        int geometryType = element->GetTag();
        cellTypeGroups[geometryType].push_back(i);
    }
    
    size_t sectionIndex = 1;
    for (const auto& group : cellTypeGroups) {
        int geometryType = group.first;
        const auto& cellIndices = group.second;
        
        unstructuredGrid[sectionIndex]->SetPoints(points);
        
        for (size_t cellIdx : cellIndices) {
            const auto& element = elements[cellIdx];
            
            int vtkCellType = convertGeometryToVTKType(geometryType);
            const auto& vertexList = element->GetVertexList();

            vtkSmartPointer<vtkIdList> idList = vtkSmartPointer<vtkIdList>::New();
            idList->SetNumberOfIds(vertexList.GetLength());
            for (uint32_t j = 0; j < vertexList.GetLength(); ++j) {
                idList->SetId(j, vertexList(j));
            }
            
            unstructuredGrid[sectionIndex]->InsertNextCell(vtkCellType, idList);
        }
        
        sectionIndex++;
    }
    

}

std::string vtkFluentCFFReader::getElementTypeName(int geometryType) const
{
    switch (geometryType) {
        case Geometry::TRIANGLE: return "Triangle";
        case Geometry::QUADRILATERAL: return "Quadrilateral";  
        case Geometry::TETRAHEDRON: return "Tetrahedron";
        case Geometry::HEXAHEDRON: return "Hexahedron";
        case Geometry::PRISM: return "Prism";
        case Geometry::PYRAMID: return "Pyramid";
        default: return "Unknown";
    }
}

int vtkFluentCFFReader::convertGeometryToVTKType(int geometryType) const
{
    switch (geometryType) {
        case Geometry::TRIANGLE: return VTK_TRIANGLE;
        case Geometry::QUADRILATERAL: return VTK_QUAD;
        case Geometry::TETRAHEDRON: return VTK_TETRA;
        case Geometry::HEXAHEDRON: return VTK_HEXAHEDRON;
        case Geometry::PRISM: return VTK_WEDGE;
        case Geometry::PYRAMID: return VTK_PYRAMID;
        default: return VTK_VERTEX;
    }
}

int vtkFluentCFFReader::getNumberOfNode() const
{
    return nNode;
}

std::vector<vtkSmartPointer<vtkUnstructuredGrid>> vtkFluentCFFReader::getDataSet()
{

    return unstructuredGrid;
}

std::vector<std::string> vtkFluentCFFReader::getDataSetName()
{
    //* Debug
    for (auto section : sectionName)
        std::cout << section << std::endl;
    return sectionName;
}

void vtkFluentCFFReader::FATAL(const char* message) const
{

    throw std::runtime_error(message);
}
