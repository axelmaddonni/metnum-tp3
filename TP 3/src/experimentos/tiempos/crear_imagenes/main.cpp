#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;
using std::ofstream;

int main (int argc, char **argv) {
	if (argc < 5) {
		cout << endl;
        cout << "Modo de uso: ./ejecutable archivoSalida alto ancho cantidadFrames framerate modo valorExtra(Optativo)\n";
        cout << "----Modos Validos: 0. Aleatorio\n";
        cout << "                   1. Constante (Valor extra: NUMERO)\n";
        cout << "                   2. Ola (Valor extra: TAMAÑO OLA)\n";
        cout << endl;
        return 0;
	}

    ofstream output(argv[1]);
    const int alto = atoi(argv[2]);
    const int ancho = atoi(argv[3]);
    const int cantidadFrames = atoi(argv[4]);
    const int framerate = atoi(argv[5]);
    const int modo = atoi(argv[6]);
    const int valorExtra = atoi(argv[7]);


    output << cantidadFrames << endl;
    output << alto << " " << ancho << endl;
	output << framerate << endl;

	switch (modo) {
		case 0:
		{
			srand (time(NULL));
			//Aleatorio
			for (int f = 0; f < cantidadFrames; f++) {
				for (int i = 0; i < alto; i++) {
					for (int j = 0; j < ancho; j++) {
						if (j>0) {
							output << " ";
						}
						output << rand() % 256;
					}
					output << endl;
				}
			}
			break;
		}
		case 1:
		{
			//Constante
			for (int f = 0; f < cantidadFrames; f++) {
				for (int i = 0; i < alto; i++) {
					for (int j = 0; j < ancho; j++) {
						if (j>0) {
							output << " ";
						}
						output << valorExtra;
					}
					output << endl;
				}
			}
			break;
		}
		case 2:
		{
			//Ola
			bool subida = true;
			int cambio = ceil(255 / (double)valorExtra);
			int actual = 0;
			for (int f = 0; f < cantidadFrames; f++) {
				if (f % valorExtra == 0 &&  f != 0) {
					subida = !subida;
				}
				if (subida) {
					actual += cambio;
				} else {
					actual -= cambio;
				}
				for (int i = 0; i < alto; i++) {
					for (int j = 0; j < ancho; j++) {
						if (j>0) {
							output << " ";
						}
						output << actual;
					}
					output << endl;
				}
			}
			break;
		}
	}



    output.close();
    return 0;
}