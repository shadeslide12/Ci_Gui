#ifndef VTK_FLUENT_CFF_READER_H
#define VTK_FLUENT_CFF_READER_H

#include <vtkSmartPointer.h>
#include <vtkUnstructuredGrid.h>
#include <vtkPolyData.h>
#include <vtkPoints.h>
#include <string>
#include <vector>


namespace Geometry {
    class Mesh;
}

typedef float Node[3];


class vtkFluentCFFReader
{
public:
    vtkFluentCFFReader(const std::string& filename = "");
    ~vtkFluentCFFReader();

    void setFileName(const std::string& name);

    int getNumberOfNode() const;
    std::vector<vtkSmartPointer<vtkUnstructuredGrid>> getDataSet();
    std::vector<std::string> getDataSetName();

private:

    void readMeshData();
    void extractNodeCoordinates(); 
    void extractCellConnectivity();
    void buildVTKDataStructures();
    

    std::string getElementTypeName(int geometryType) const;
    int convertGeometryToVTKType(int geometryType) const;
    void FATAL(const char* message) const;


    std::string fileName;
    

    int nNode;
    int cellDim, phyDim;
    

    Node* nodes;
    

    std::vector<vtkSmartPointer<vtkUnstructuredGrid>> unstructuredGrid;
    std::vector<std::string> sectionName;
    

    Geometry::Mesh* meshData;
};

#endif 
