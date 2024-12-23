#ifndef CGNSREADER_H
#define CGNSREADER_H

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkUnstructuredGrid.h>

#include <vtkPolyData.h>
#include <vtkCellArray.h>
#include <vtkPolyDataWriter.h>

#include "cgnslib.h"

#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkNew.h>


typedef float Node[3];

typedef struct {
    int cnt;
    char name[33];
} Variable;

class CGNSReader
{

    public:
        CGNSReader(string);
        ~CGNSReader();

        void setFileName(const string);

        void readNode();
        void readSection();
        int get_variables();
        void readSolution(int* mask);

        int getNumberOfNode();

        vector<vtkSmartPointer<vtkUnstructuredGrid>> getDataSet();
        vector<string> getDataSetName();

    private:
        void FATAL(const char *) const; //display error message

        string fileName;

        int fileNumber; int baseNumber; int zoneNumber; int sectionNumber;
        int nFile; int nBase; int nZone; int nSection;

        int nNode;

        int cellDim; int phyDim;
        
        CGNS_ENUMT(ZoneType_t) zoneType;
        cgsize_t sizes[9];
        char zoneName[30];
        char baseName[30];

        vector<string> sectionName;
        vector<vtkSmartPointer<vtkUnstructuredGrid>> unstructuredGrid;
        vector<vtkSmartPointer<vtkPolyData>> polydata;


        Node* nodes;

        int nvars, ndata;
        Variable *vars;
        cgsize_t varrng[2][3];
        CGNS_ENUMT(GridLocation_t) varloc;
        int cgnssol;
};



#endif