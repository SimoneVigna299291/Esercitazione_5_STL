#pragma once

#include <vector>
#include <map>
#include <list>
#include "Eigen/Dense"

using namespace std;
using namespace Eigen;

namespace PolygonalLibrary {


// definisco una struttura che rappresenta una mesh poligonale
struct PolygonalMesh {
    // informazioni cell0D: vertici
    vector<unsigned int> Cell0DId;
    vector<Vector2d> Cell0DCoordinates;
    map<unsigned int, list<unsigned int>> Cell0DMarkers;

    // informaioni cell1D: segmenti
    vector<unsigned int> Cell1DId;
    vector<Vector2i> Cell1DVertices;
    map<unsigned int, list<unsigned int>> Cell1DMarkers;

    // informazioni cell2D: poligoni
    vector<unsigned int> Cell2DId;
    vector<vector<unsigned int>> Cell2DVertices;
    vector<vector<unsigned int>> Cell2DEdges;
};

}
