#include "vtkCGNSReader.h"

#include "cgnslib.h"
#include <iostream>
using std::cin; using std::cout; using std::endl;

#include <string.h>
#include <math.h>

#include <vtkIdList.h>
#include <vtkUnstructuredGridWriter.h>
#include <vtkDataSetReader.h>
#include <vtkDoubleArray.h>
#include <vtkPointData.h>

static int sort_variables (const void *v1, const void *v2)
{
    Variable *var1 = (Variable *)v1;
    Variable *var2 = (Variable *)v2;

    return (strcmp (var1->name, var2->name));
}

CGNSReader::CGNSReader(string filename)
{
    baseNumber = zoneNumber = 1;
    setFileName(filename);
    cg_base_read(fileNumber, baseNumber, baseName, &cellDim, &phyDim);
    readNode();
    readSection();
}

CGNSReader::~CGNSReader()
{
    free (nodes);
}

void CGNSReader::setFileName(const string name)
{
    fileName = name;
    if(cg_open(fileName.c_str(), CG_MODE_READ, &fileNumber)) FATAL(nullptr);
    cg_base_read(fileNumber, baseNumber, baseName, &cellDim, &phyDim);

    cout << "read file: " << fileName << endl;
    cout << "if make no changes, the reader read 1st base, 1st zone" << endl;
    cout << "the celldim and phydim is: " << cellDim << " and " << phyDim << endl;
}

void CGNSReader::readNode()
{
    if (cg_zone_type (fileNumber, baseNumber, zoneNumber, &zoneType) || 
    cg_zone_read (fileNumber, baseNumber, zoneNumber, zoneName, sizes))
    FATAL (NULL);

    int i, j, n, ncoords;
    int rind[6];
    cgsize_t nn, rng[2][3];
    CGNS_ENUMT(DataType_t) datatype;
    float *xyz;
    double rad, theta, phi;
    char name[33], coordtype[4];

    if (cg_ncoords (fileNumber, baseNumber, zoneNumber, &ncoords))
        FATAL (NULL);
    if (ncoords < phyDim)
        FATAL ("less than PhyDim coordinates");
    if (cg_goto (fileNumber, baseNumber, "Zone_t", zoneNumber,
        "GridCoordinates_t", 1, "end"))
        FATAL (NULL);
    if ((i = cg_rind_read (rind)) != CG_OK) {
        if (i != CG_NODE_NOT_FOUND)
            FATAL (NULL);
        for (n = 0; n < 6; n++)
            rind[n] = 0;
    }
    if (zoneType == CGNS_ENUMV(Structured)) {
        for (n = 0; n < 3; n++) {
            rng[0][n] = 1;
            rng[1][n] = 1;
        }
        nn = 1;
        for (n = 0; n < cellDim; n++) {
            rng[0][n] = rind[2*n] + 1;
            rng[1][n] = rind[2*n] + sizes[n];
            nn *= sizes[n];
        }
    }
    else {
        nn = sizes[0] + rind[0] + rind[1];
        rng[0][0] = 1;
        rng[1][0] = nn;
    }

    nNode = (int) nn;
    
        strcpy (coordtype, "   ");
    xyz = (float *) malloc (nNode * sizeof(float));
    nodes = (Node *) malloc (nNode * sizeof(Node));
    if (xyz == NULL || nodes == NULL)
        FATAL ("malloc failed for nodes");

    for (i = 1; i <= ncoords; i++) {
        if (cg_coord_info (fileNumber, baseNumber, zoneNumber, i, &datatype, name) ||
            cg_coord_read (fileNumber, baseNumber, zoneNumber, name,
                CGNS_ENUMV(RealSingle), rng[0], rng[1], xyz))
            FATAL (NULL);
        if (0 == strcmp (name, "CoordinateX") ||
            0 == strcmp (name, "CoordinateR"))
            j = 0;
        else if (0 == strcmp (name, "CoordinateY") ||
                 0 == strcmp (name, "CoordinateTheta"))
            j = 1;
        else if (0 == strcmp (name, "CoordinateZ") ||
                 0 == strcmp (name, "CoordinatePhi"))
            j = 2;
        else
            continue;
        if (coordtype[j] == ' ' || strchr ("XYZ", name[10]) != NULL)
            coordtype[j] = name[10];
        for (n = 0; n < nNode; n++)
            nodes[n][j] = xyz[n];
    }
    free (xyz);

    /* change coordinate system to cartesian */

    if (0 == strncmp (coordtype, "RTZ", phyDim)) {
        for (n = 0; n < nNode; n++) {
            rad   = nodes[n][0];
            theta = nodes[n][1];
            nodes[n][0] = (float)(rad * cos (theta));
            nodes[n][1] = (float)(rad * sin (theta));
        }
    }
    else if (0 == strcmp (coordtype, "RTP")) {
        for (n = 0; n < nNode; n++) {
            rad   = nodes[n][0];
            theta = nodes[n][1];
            phi   = nodes[n][2];
            nodes[n][0] = (float)(rad * sin (theta) * cos (phi));
            nodes[n][1] = (float)(rad * sin (theta) * sin (phi));
            nodes[n][2] = (float)(rad * cos (theta));
        }
    }
    else if (strncmp (coordtype, "XYZ", phyDim))
        FATAL ("unknown coordinate system");

    cout << "there are " << getNumberOfNode() << " points in zone.\n" << endl;

}

void CGNSReader::readSection()
{
    get_variables();
    int i, n, nsect, nn, ip;
    int elemcnt, elemsize, cell[9];
    int *nodemap, *types;
    cgsize_t is, ie, nelems;
    cgsize_t size, *conn;
    CGNS_ENUMT(ElementType_t) elemtype, et;
    char name[30];

    if (cg_nsections (fileNumber, baseNumber, zoneNumber, &nSection))
        FATAL (NULL);
    if (nSection < 1) FATAL ("no sections defined");

    cout << "there are " << nSection << " sections in zone. \n" << endl;    
    
    nodemap = (int *) malloc (nNode * sizeof(int));
    if (nodemap == NULL)
    FATAL ("malloc failed for node mapping data");

    for (sectionNumber = 1; sectionNumber <= nSection; sectionNumber++)
    {
        if (cg_section_read(fileNumber, baseNumber, zoneNumber, sectionNumber,
                name, &elemtype, &is, &ie, &nn, &ip) ||
            cg_ElementDataSize (fileNumber, baseNumber, zoneNumber, sectionNumber, &size))
            FATAL (NULL);
        sectionName.push_back(name);
        if (size > CG_MAX_INT32)
            FATAL("element data too large for 32-bit integer");
        nelems = ie - is + 1;
        conn = (cgsize_t *) malloc ((size_t)size * sizeof(cgsize_t));
        if (conn == NULL)
            FATAL ("malloc failed for element connectivity");
        if (cg_elements_read (fileNumber, baseNumber, zoneNumber, sectionNumber, conn, NULL))
            FATAL (NULL);
        for (n = 0; n < nNode; n++)
            nodemap[n] = 0;
        et = elemtype;
        elemcnt = elemsize = 0;
        for (is = 0, ie = 0; ie < nelems; ie++) {
            // if (elemtype == CGNS_ENUMV(MIXED)) et = CGNS_ENUMV(conn[is++]);
            switch (et) {
                case CGNS_ENUMV(NODE):
                    nn = 1;
                    break;
                case CGNS_ENUMV(BAR_2):
                case CGNS_ENUMV(BAR_3):
                    nn = 2;
                    break;
                case CGNS_ENUMV(TRI_3):
                case CGNS_ENUMV(TRI_6):
                    nn = 3;
                    break;
                case CGNS_ENUMV(QUAD_4):
                case CGNS_ENUMV(QUAD_8):
                case CGNS_ENUMV(QUAD_9):
                case CGNS_ENUMV(TETRA_4):
                case CGNS_ENUMV(TETRA_10):
                    nn = 4;
                    break;
                case CGNS_ENUMV(PYRA_5):
                case CGNS_ENUMV(PYRA_14):
                    nn = 5;
                    break;
                case CGNS_ENUMV(PENTA_6):
                case CGNS_ENUMV(PENTA_15):
                case CGNS_ENUMV(PENTA_18):
                    nn = 6;
                    break;
                case CGNS_ENUMV(HEXA_8):
                case CGNS_ENUMV(HEXA_20):
                case CGNS_ENUMV(HEXA_27):
                    nn = 8;
                    break;
                default:
                    nn = 0;
                    break;
            }
            if (nn) {
                elemcnt++;
                elemsize += (nn + 1);
                for (i = 0; i < nn; i++) {
                    n = (int)conn[is+i] - 1;
                    (nodemap[n])++;
                }
            }
            if (cg_npe (et, &nn) || nn == 0)
                FATAL ("invalid element type");
            is += nn;
        }
        if (elemcnt == 0) {
            free (conn);
            continue;
        }

        for (nn = 0, n = 0; n < nNode; n++) {
            if (nodemap[n]) {
                nodemap[n] = ++nn;
            }
        }
        cout << "there are " << nn << " points in " << sectionName[sectionNumber - 1] << endl;
        cout << "create data set: " << sectionName[sectionNumber - 1] << endl;
        unstructuredGrid.push_back(vtkSmartPointer<vtkUnstructuredGrid>::New());
        polydata.push_back(vtkSmartPointer<vtkPolyData>::New());
        vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
        vtkSmartPointer<vtkCellArray> vertices = vtkSmartPointer<vtkCellArray>::New();
        for (n = 0; n < nNode; n++) {
            if (nodemap[n]) {
                vertices->InsertNextCell(1);
                vertices->InsertCellPoint(points->InsertNextPoint(nodes[n]));

                }
        }

        unstructuredGrid[sectionNumber - 1]->SetPoints(points);
        
        // polydata[sectionNumber - 1]->SetPoints(points);
        // polydata[sectionNumber - 1]->SetVerts(vertices);
        // vtkSmartPointer<vtkPolyDataWriter> writer = vtkSmartPointer< vtkPolyDataWriter>::New();
        // writer->SetInputData(polydata[sectionNumber - 1]);
        // writer->SetFileName(sectionName[sectionNumber-1].c_str());
        // writer->Write();
        types = (int *) malloc (elemcnt * sizeof(int));
        if (types == NULL) {
          FATAL("malloc failed for element types");
          et = elemtype;
          cout << elemtype << endl;
        }
        elemcnt = 0;
        for (is = 0, ie = 0; ie < nelems; ie++) {
            // if (elemtype == CGNS_ENUMV(MIXED)) et = (int)conn[is++];
            switch (et) {
                case CGNS_ENUMV(NODE):
                    nn = 1;
                    types[elemcnt++] = 1;
                    break;
                case CGNS_ENUMV(BAR_2):
                case CGNS_ENUMV(BAR_3):
                    nn = 2;
                    types[elemcnt++] = 3;
                    break;
                case CGNS_ENUMV(TRI_3):
                case CGNS_ENUMV(TRI_6):
                    nn = 3;
                    types[elemcnt++] = 5;
                    break;
                case CGNS_ENUMV(QUAD_4):
                case CGNS_ENUMV(QUAD_8):
                case CGNS_ENUMV(QUAD_9):
                    nn = 4;
                    types[elemcnt++] = 9;
                    break;
                case CGNS_ENUMV(TETRA_4):
                case CGNS_ENUMV(TETRA_10):
                    nn = 4;
                    types[elemcnt++] = 10;
                    break;
                case CGNS_ENUMV(PYRA_5):
                case CGNS_ENUMV(PYRA_14):
                    nn = 5;
                    types[elemcnt++] = 14;
                    break;
                case CGNS_ENUMV(PENTA_6):
                case CGNS_ENUMV(PENTA_15):
                case CGNS_ENUMV(PENTA_18):
                    nn = 6;
                    types[elemcnt++] = 13;
                    break;
                case CGNS_ENUMV(HEXA_8):
                case CGNS_ENUMV(HEXA_20):
                case CGNS_ENUMV(HEXA_27):
                    nn = 8;
                    types[elemcnt++] = 12;
                    break;
                default:
                    nn = 0;
                    break;
            }
            if (nn) {
                cell[0] = nn;
                for (i = 0; i < nn; i++) cell[i+1] = nodemap[(int)conn[is+i]-1] - 1;
                // vtkSmartPointer<vtkCellArray> cellArray = vtkSmartPointer<vtkCellArray>::New();
                // cellArray->InsertNextCell(cell[0]);
                // for (i = 0; i < nn; i++)
                // {
                //     cellArray->InsertCellPoint(cell[i+1]);
                // }
                vtkSmartPointer<vtkIdList> idlist =vtkSmartPointer<vtkIdList>::New();
                idlist->SetNumberOfIds(cell[0]);
                for (i = 0; i < cell[0]; i++) 
                {
                    idlist->SetId(i, cell[i+1]); 
                }
                unstructuredGrid[sectionNumber - 1]->InsertNextCell(types[elemcnt - 1], idlist);
            }

            // if(nn == 4) unstructuredGrid[sectionNumber - 1]->InsertNextCell(9, 4, cell);
            
            cg_npe (et, &nn);
            is += nn;
        }


        free (conn);
        free (types);

        if (nvars) {
            if (varloc == CGNS_ENUMV(Vertex) && ndata == nNode) ;
                if(sectionNumber == 1) readSolution(nodemap);
        }


    }
    free (nodemap);
}

int CGNSReader::get_variables()
{
    char name[33];
    int n, len, nv, nsols;
    int rind[6];
    CGNS_ENUMT(DataType_t) datatype;
    cgnssol = 1;

    nvars = 0;
    if (cg_nsols (fileNumber, baseNumber, zoneNumber, &nsols))
        FATAL (NULL);
    if (cgnssol < 1 || cgnssol > nsols) return 0;

    if (cg_sol_info (fileNumber, baseNumber, zoneNumber, cgnssol, name, &varloc) ||
        cg_nfields (fileNumber, baseNumber, zoneNumber, cgnssol, &nv))
        FATAL (NULL);
    if (nv < 1) return 0;
    if (varloc != CGNS_ENUMV(Vertex) && varloc != CGNS_ENUMV(CellCenter)) return 0;
    nvars = nv;

    if (cg_goto (fileNumber, baseNumber, "Zone_t", zoneNumber,
        "FlowSolution_t", cgnssol, "end"))
        FATAL (NULL);
    if ((n = cg_rind_read (rind)) != CG_OK) {
        if (n != CG_NODE_NOT_FOUND)
            FATAL (NULL);
        for (n = 0; n < 6; n++)
            rind[n] = 0;
    }

    /* get solution data range */

    if (zoneType == CGNS_ENUMV(Structured)) {
        nv = varloc == CGNS_ENUMV(Vertex) ? 0 : cellDim;
        for (n = 0; n < 3; n++) {
            varrng[0][n] = 1;
            varrng[1][n] = 1;
        }
        ndata = 1;
        for (n = 0; n < cellDim; n++) {
            varrng[0][n] = rind[2*n] + 1;
            varrng[1][n] = rind[2*n] + sizes[n+nv];
            ndata *= (int)sizes[n+nv];
        }
    }
    else {
        nv = varloc == CGNS_ENUMV(Vertex) ? 0 : 1;
        ndata = (int)sizes[nv];
        varrng[0][0] = rind[0] + 1;
        varrng[1][0] = rind[0] + ndata;
    }


    /* get variable names */

    vars = (Variable *) malloc (nvars * sizeof(Variable));
    if (vars == NULL)
        FATAL ("malloc failed for variable names");

    for (nv = 0; nv < nvars; nv++) {
        if (cg_field_info (fileNumber, baseNumber, zoneNumber, cgnssol, nv+1,
                &datatype, name))
            FATAL (NULL);
        vars[nv].cnt = 1;
        strcpy (vars[nv].name, name);
    }
    qsort (vars, nvars, sizeof(Variable), sort_variables);

    /* get number of scalars and vectors */

    for (nv = 2; nv < nvars; nv++) {
        len = (int)strlen(vars[nv].name) - 1;
        if (vars[nv].name[len] == 'Z') {
            strcpy (name, vars[nv].name);
            name[len] = 'Y';
            if (0 == strcmp (name, vars[nv-1].name)) {
                name[len] = 'X';
                if (0 == strcmp (name, vars[nv-2].name)) {
                    vars[nv-2].cnt = 3;
                    vars[nv-1].cnt = 0;
                    vars[nv].cnt = 0;
                }
            }
        }
    }
//    cout << varrng[0][0] << "  " << varrng[0][1] <<"  " << varrng[0][2]<< endl;
//    cout << varrng[1][0] << "  " << varrng[1][1] <<"  " << varrng[1][2]<< endl;
    return nvars;
}

void CGNSReader::readSolution(int* mask)
{
    char name[33];
    int n, nv, nd;
    int nscal, nvect;
    float *data, v[3];
    int nn = 0;

    nscal = nvect = 0;
    for (nv = 0; nv < nvars; nv++) {
        if (vars[nv].cnt == 1)
            nscal++;
        else if (vars[nv].cnt == 3)
            nvect++;
    }

    if (nvect)
        data = (float *) malloc (3 * ndata * sizeof(float));
    else
        data = (float *) malloc (ndata * sizeof(float));
    if (data == NULL)
        FATAL ("malloc failed for solution data");

    if (mask == NULL)
        nd = ndata;
    else {
        for (nd = 0, n = 0; n < ndata; n++) {
            if (mask[n]) nd++;
        }
    }
        if (nscal) {
        for (nv = 0; nv < nvars; nv++) {
            if (vars[nv].cnt != 1) continue;
            if (cg_field_read (fileNumber, baseNumber, zoneNumber, cgnssol,
                    vars[nv].name, CGNS_ENUMV(RealSingle),
                    varrng[0], varrng[1], data))
                FATAL (NULL);
            for (n = 0; n < ndata; n++) {
                if (mask == NULL || mask[n])
                {
                    nn++;
                }
            }
            vtkSmartPointer<vtkDoubleArray> scaler = vtkSmartPointer<vtkDoubleArray>::New();
            scaler->SetNumberOfValues(nn);
            for (n = 0; n < ndata; n++) {
                if (mask == NULL || mask[n])
                {
                    scaler->SetValue(n, data[n]);
                }
            }
            unstructuredGrid[0]->GetPointData()->SetScalars(scaler);
        }
    }


}

int CGNSReader::getNumberOfNode()
{
    return nNode;
}

/*---------- FATAL ----------------------------------------------------
 * display message
 *---------------------------------------------------------------------*/

void CGNSReader::FATAL(const char *errorMessage) const
{
    if (errorMessage == nullptr) cout << "CGNS error: " << cg_get_error() << endl;
    else cout << errorMessage << endl;
}

vector<vtkSmartPointer<vtkUnstructuredGrid>> CGNSReader::getDataSet()
{
    return unstructuredGrid;
}

vector<string> CGNSReader::getDataSetName()
{
    return sectionName;
}

