#include <iostream>
#include "header.h"

using namespace std;

int main (int argc, char **argv)
{
    if (argc != 5)
    {
        cout << "Modo de uso: ./ejecutable archivoDeEntrada archivoDeSalida metodoAEjecutar cantidadDeFramesIntermedios\n";
        return 0;
    }
    Parametros params(argc, argv); 
    methodDispatch(params);
    return 0;
}
