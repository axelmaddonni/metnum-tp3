#include "header.h"
#include <vector>
#include <tgmath.h>
#include "string.h"
#include "stdlib.h"
#include "stdio.h"

using std::endl;
using std::vector;
using std::move;

int maxMEM = 0;

void actualizarMem() {
	int mem = getValue();
	if (mem > maxMEM) {
		maxMEM = mem;
	}
}

int parseLine(char* line){
    int i = strlen(line);
    while (*line < '0' || *line > '9') line++;
    line[i-3] = '\0';
    i = atoi(line);
    return i;
}

int getValue(){ //Note: this value is in KB!
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];


    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmRSS:", 6) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}

void splinesPorBloques(ParametrosConBloques &params) {
	params.output << (params.frames - 1) * params.framesIntermedios + params.frames << endl;
	params.output << params.height << " " << params.width << endl;
	params.output << params.framerate << endl;

	vector<vector<vector<int>>> Frames((params.tamBloque*2), vector<vector<int>>(params.height, vector<int>(params.width, 0)));
	

	//vector de vectores de los resultados (la derecha la igualdad de las ecuaciones de C)
	vector<vector<vector<double>>> res (params.height, vector<vector<double>>(params.width, vector<double>((params.tamBloque*2), 0))); //ACA HAY QUE CAMBIAR POR 0

	double aux;

	int fin_bloque = 0;
	int indice = 0;
	int ultimo_indice = 0;
	double B;

	actualizarMem();

	//cargo primer frame
	for (int i = 0; i < params.height; i++) {
		for (int j = 0; j < params.width; j++) {
			//guarda las imagenes del bloque actual
			params.input >> Frames[0][i][j];
		}
	}	
	actualizarMem();

	//mientras no llega al final de los bloques
	while (fin_bloque < params.frames -1) {
		//calcula el fin de bloques
		if (indice + (params.tamBloque * 2) > params.frames) { //perfecto
			fin_bloque = params.frames - 1;
		} else {
			fin_bloque = indice + params.tamBloque - 1;
		}
		

		for (int k = 1; k <= fin_bloque - indice; k++) {
			for (int i = 0; i < params.height; i++) {
				for (int j = 0; j < params.width; j++) {
					//guarda las imagenes del bloque actual
					params.input >> Frames[k][i][j];
					if (k>1) {
						//calcula los valores de los vectores de resultados (la derecha de la igualdad de las ecuaciones de C)
						res[i][j][k-1] = 3 * ( (double)(Frames[k][i][j] - (2 * Frames[k-1][i][j]) + Frames[k-2][i][j]) / (double)(params.framesIntermedios + 1) );
					}
				}
			}
		}

		actualizarMem();


		//-----matriz de Cs------
		vector<vector<double>> M_C ((params.tamBloque*2), vector<double>((params.tamBloque*2), 0));


		actualizarMem();

		//Matriz de Cs
		//----en la primera fila queda: 1 0 ... 0
		M_C[0][0] = 1;
		for (int i=1; i < fin_bloque - indice; i++) {
			//--i-1 = 1*(x_i+1 - x_i)
			M_C[i][i - 1] = params.framesIntermedios + 1;
			//--i = 4*(x_i+1 - x_i)
			M_C[i][i] = 4 * (params.framesIntermedios + 1);
			//--i+1 = 1*(x_i+1 - x_i)
			M_C[i][i + 1] = params.framesIntermedios + 1;
		}
		//----en la última fila queda: 0 ... 0 1
		M_C[fin_bloque - indice][fin_bloque - indice] = 1;


		actualizarMem();
		
		//----diagonalizamos la matriz
		for (int k = 1; k < fin_bloque - indice - 1; k++) {
			aux = M_C[k][k-1] / M_C[k-1][k-1];
			M_C[k][k-1] = 0; 
			for (int i = 0; i < params.height; i++) {
				for (int j = 0; j < params.width; j++) {
					res[i][j][k] = res[i][j][k] - res[i][j][k-1] * aux;
				}
			}
			aux = M_C[fin_bloque - indice - 1 - k][fin_bloque - indice - k] / M_C[fin_bloque - indice - k][fin_bloque - indice - k];
			M_C[fin_bloque - indice - 2 - k][fin_bloque - indice - 1 - k] = 0;
			for (int i = 0; i < params.height; i++) {
				for (int j = 0; j < params.width; j++) {
					res[i][j][fin_bloque - indice - 1 - k] = res[i][j][fin_bloque - indice - 1 - k] - res[i][j][fin_bloque - indice - k] * aux;
				}
			}
		}


		actualizarMem();


		//---En M_sal vamos a guardar los valores de los frames intermedios que vamos sacando
		vector<vector<vector<int>>> M_sal (params.framesIntermedios * (params.tamBloque*2), vector<vector<int>>(params.height, vector<int>(params.width, 0)));
		vector<double> C((params.tamBloque*2), 0);
		vector<double> D((params.tamBloque*2), 0);

		actualizarMem();

		for (int i = 0; i < params.height; i++) {
			for (int j = 0; j < params.width; j++) {
				//---Sacamos los valores de C
				for (int k = 0; k <= fin_bloque - indice; k++) {
					//---Como M_C es diagonal solo tenemos que pasar dividiendo el valor de la diagonal
					C[k] = res[i][j][k] / M_C[k][k];
				}
				//---Despejamos los valores de D (usando C)
				for (int k = 0; k < fin_bloque - indice; k++) {
					D[k] = (C[k+1] - C[k]) / ( (params.framesIntermedios + 1) * 3);
				}

				for (int k = 0; k < fin_bloque - indice; k++) {
					
					//---Sacamos el b_i
					B = Frames[k+1][i][j] - Frames[k][i][j] - C[k] * pow(params.framesIntermedios + 1, 2) - D[k] * pow(params.framesIntermedios + 1, 3);
					B = B / (params.framesIntermedios + 1);

					for (int f = 0; f < params.framesIntermedios; f++) {
						//---aux = (x - x_i) //distancia entre el x_i y el x del nuevo frame
						int aux = f + 1;
						//---Aplicamos la función al x del nuevo frame
						int valor = round(Frames[k][i][j] + B * aux + C[k] * pow(aux, 2) + D[k] * pow(aux, 3));
						if (valor < 0) valor = 0;
						if (valor > 255) valor = 255;
						M_sal[(k * params.framesIntermedios) + f][i][j] = valor;
					}

				}
			}
		}

		actualizarMem();


		for (int k = 0; k < fin_bloque - indice; k++) {

			//imprimo el primer frame tal cual
			imprimirFrame(params.output, Frames[k], params.height, params.width);

			//---Imprimimos los nuevos frames
			for (int f = 0; f < params.framesIntermedios; f++) {
				imprimirFrame(params.output, M_sal[(k * params.framesIntermedios) + f], params.height, params.width);
			}
		}

		actualizarMem();

		//recalcula el ultimoindice
		ultimo_indice = fin_bloque - indice;

		//El ultimo frame del bloque es el primero del siguiente

		for (int i = 0; i < params.height; i++) {
			for (int j = 0; j < params.width; j++) {
				Frames[0][i][j] = Frames[ultimo_indice][i][j]; 
			}
		}	
		
		//Frames[0] = move(Frames[fin_bloque - indice]);

		indice = fin_bloque;

		actualizarMem();

	}
	
	//imprimimos el último
	imprimirFrame(params.output, Frames[ultimo_indice], params.height, params.width);

	actualizarMem();

	cout << maxMEM;

	return;

}