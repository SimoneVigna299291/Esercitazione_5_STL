#include <iostream>
#include "PolygonalMesh.hpp"
#include "Utils.hpp"

using namespace std;
using namespace PolygonalLibrary;

int main() {
    PolygonalMesh mesh;
    string filepath = "PolygonalMesh";

    if (!ImportMesh(filepath, mesh)) {
        cerr << "Errore nel caricamento della mesh!" << endl;
        return 1;  // Codice di errore quando la mesh non è importata correttamente o se ci sono errori
    }

    // stampa di importanzione riuscita e alcune informazioni della mesh
    cout << "Mesh importata correttamente" << endl;
    cout << "Numero di elementi Cell0D: " << mesh.Cell0DId.size() << endl;
    cout << "Numero di elementi Cell1D: " << mesh.Cell1DId.size() << endl;
    cout << "Numero di elementi Cell2D: " << mesh.Cell2DId.size() << endl;

    return 0;
}
