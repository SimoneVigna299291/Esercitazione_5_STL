#pragma once

#include <string>
#include "PolygonalMesh.hpp"  // includo la struttura definita in PolygonalMesh

using namespace std;

namespace PolygonalLibrary {
// funzione per importare una mesh da file, dei vertici,dei segmenti e dei poligoni
bool ImportMesh(const string &filepath, PolygonalMesh& mesh);
bool ImportCell0Ds(const string &filename, PolygonalMesh& mesh);
bool ImportCell1Ds(const string &filename, PolygonalMesh& mesh);
bool ImportCell2Ds(const string &filename, PolygonalMesh& mesh);
}

