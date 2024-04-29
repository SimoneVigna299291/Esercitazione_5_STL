#include "Utils.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

namespace PolygonalLibrary {

bool ImportMesh(const string& filepath, PolygonalMesh& mesh) {
    if (!ImportCell0Ds(filepath + "/Cell0Ds.csv", mesh) ||
        !ImportCell1Ds(filepath + "/Cell1Ds.csv", mesh) ||
        !ImportCell2Ds(filepath + "/Cell2Ds.csv", mesh)) {
        cerr << "Errore nell'importazione di una o più componenti della mesh." << endl;
        return false;
    }
    return true;
}

bool ImportCell0Ds(const string &filename, PolygonalMesh& mesh) {
    ifstream file(filename);
    if (!file) {
        cerr << "Errore apertura del file! " << filename << endl;
        return false;
    }
    string line;
    getline(file, line); // Salta header del file
    while (getline(file, line)) {
        istringstream iss(line);
        unsigned int id;
        unsigned int marker;
        double x, y;
        char delim;

        if (!(iss >> id >> delim >> marker >> delim >> x >> delim >> y)) {
            cerr << "Errore in " << filename << " nella riga: " << line << endl;
            continue;
        }

        mesh.Cell0DId.push_back(id);
        mesh.Cell0DCoordinates.push_back(Vector2d(x, y));
        mesh.Cell0DMarkers[marker].push_back(id);
    }
    file.close();
    return true;
}

bool ImportCell1Ds(const string &filename, PolygonalMesh& mesh) {
    ifstream file(filename);
    if (!file) {
        cerr << "Errore apertura " << filename << endl;
        return false;
    }
    string line;
    getline(file, line); // salta header file
    while (getline(file, line)) {
        istringstream iss(line);
        unsigned int id, marker, origin, end;
        char delim;

        if (!(iss >> id >> delim >> marker >> delim >> origin >> delim >> end)) {
            cerr << "Errore in " << filename << " nella riga: " << line << endl;
            continue;
        }

        mesh.Cell1DId.push_back(id);
        mesh.Cell1DVertices.push_back(Vector2i(origin, end));
        mesh.Cell1DMarkers[marker].push_back(id);
    }
    file.close();
    return true;
}

bool ImportCell2Ds(const string &filename, PolygonalMesh& mesh) {
    ifstream file(filename);
    if (!file) {
        cerr << "Errore di apertura " << filename << endl;
        return false;
    }
    string line;
    getline(file, line); // Salta header del file
    while (getline(file, line)) {
        istringstream iss(line);
        unsigned int id, marker, numVertices, numEdges;
        char delim;
        vector<unsigned int> vertices, edges;

        iss >> id >> delim >> marker >> delim >> numVertices;
        for (unsigned int i = 0; i < numVertices; ++i) {
            unsigned int vertex;
            iss >> delim >> vertex;
            vertices.push_back(vertex);
        }

        iss >> delim >> numEdges;
        for (unsigned int i = 0; i < numEdges; ++i) {
            unsigned int edge;
            iss >> delim >> edge;
            edges.push_back(edge);
        }

        mesh.Cell2DId.push_back(id);
        mesh.Cell2DVertices.push_back(vertices);
        mesh.Cell2DEdges.push_back(edges);
    }
    file.close();
    return true;
}

// scrivo una funzione che verifica che i segmenti non abbiano lunghezza nulla
void CheckSegmentLengths(const PolygonalMesh& mesh)
{
    for (const auto& vertices : mesh.Cell1DVertices)
    {
        Vector2d start = mesh.Cell0DCoordinates[vertices(0)]; //inizio lato
        Vector2d end = mesh.Cell0DCoordinates[vertices(1)]; //fine lato
        double length = (end - start).norm();  //lunghezza lato
        if (length == 0)
        {
            cerr << "Il segmento di vertici " << vertices(0) << " e " << vertices(1) << " ha lunghezza nulla" << endl;
        }
    }
}

//scrivo una funzione che verifichi che le aree dei poligoni non siano nulle
void CheckPolygonAreas(const PolygonalMesh& mesh)
{
    for (const auto& vertices : mesh.Cell2DVertices)
    {
        double area = 0;
        int n = vertices.size();
        if (n >= 3) //se un poligono non ha almeno 3 vertici, ha sicuramente area nulla
        {
            //uso formula di gauss per il calcolo dell' area del poligono date le coordinate dei suoi vertici
            for (int i = 0; i < n; ++i)
            {
                Vector2d current = mesh.Cell0DCoordinates[vertices[i]];
                Vector2d next = mesh.Cell0DCoordinates[vertices[(i + 1) % n]];
                area += current[0] * next[1] - next[0] * current[1];
            }
            area = 0.5 * abs(area);

            if (area == 0)
            {
                cerr << "Il poligono di vertici: ";
                for (int i = 0; i < n; ++i) { cerr << vertices[i] << " "; }
                cerr << "ha area nulla" << endl;
            }
        }
    }

}
}
