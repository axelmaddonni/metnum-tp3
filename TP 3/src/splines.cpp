#include "header.h"
#include <vector>
#include <tgmath.h>

using std::endl;
using std::vector;

void splinesPorBloques(ParametrosConBloques &params) {
	params.output << (params.frames - 1) * params.framesIntermedios + params.frames << endl;
	params.output << params.height << " " << params.width << endl;
	params.output << params.framerate << endl;

	vector<vector<vector<int>>> Frames(params.tamBloque, vector<vector<int>>(params.height, vector<int>(params.width, 0)));
	

	//vector de vectores de los resultados (la derecha la igualdad de las ecuaciones de C)
	vector<vector<vector<double>>> res (params.height, vector<vector<double>>(params.width, vector<double>(params.tamBloque, 1)));

	double aux;


	int fin_bloque = 0;
	int indice = 0;
	int ultimo_indice = 0;
	double B;

	//mientras no llega al final de los bloques
	while (fin_bloque < params.frames -1) {
		//calcula el fin de bloques
		if (indice + params.tamBloque >= params.frames ) {
			fin_bloque = params.frames - 1;
		} else if (indice + (params.tamBloque * 2) >= params.frames ) {
			fin_bloque = indice + round( (params.frames - indice) / 2 );
		} else {
			fin_bloque = indice + params.tamBloque - 1;
		}
		

		for (int k = 0; k <= fin_bloque - indice; k++) {
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


		//-----matriz de Cs------
		vector<vector<double>> M_C (params.tamBloque, vector<double>(params.tamBloque, 0));


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


		
		//----diagonalizamos la matriz
		for (int k = 1; k < fin_bloque - indice - 1; k++) {
			aux = M_C[k][k-1] / M_C[k-1][k-1];
			M_C[k][k-1] = 0;
			for (int i = 0; i < params.height; i++) {
				for (int j = 0; j < params.width; j++) {
					res[i][j][k] = res[i][j][k] - res[i][j][k-1] * aux;
				}
			}
			aux = M_C[fin_bloque - indice - 1 - k][fin_bloque - indice - 1 - k] / M_C[fin_bloque - indice - k][fin_bloque - indice - k];
			M_C[fin_bloque - indice - 2 - k][fin_bloque - indice - 1 - k] = 0;
			for (int i = 0; i < params.height; i++) {
				for (int j = 0; j < params.width; j++) {
					res[i][j][fin_bloque - indice - 1 - k] = res[i][j][fin_bloque - indice - 1 - k] - res[i][j][fin_bloque - indice - k] * aux;
				}
			}
		}


		//---En M_sal vamos a guardar los valores de los frames intermedios que vamos sacando
		vector<vector<vector<int>>> M_sal (params.framesIntermedios * params.tamBloque, vector<vector<int>>(params.height, vector<int>(params.width, 0)));
		vector<double> C(params.tamBloque, 0);
		vector<double> D(params.tamBloque, 0);

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
						M_sal[(k * params.framesIntermedios) + f][i][j] = round(Frames[k][i][j] + B * aux + C[k] * pow(aux, 2) + D[k] * pow(aux, 3));
					}

				}
			}
		}


		for (int k = 0; k < fin_bloque - indice; k++) {

			//imprimo el primer frame tal cual
			imprimirFrame(params.output, Frames[k], params.height, params.width);

			//---Imprimimos los nuevos frames
			for (int f = 0; f < params.framesIntermedios; f++) {
				imprimirFrame(params.output, M_sal[(k * params.framesIntermedios) + f], params.height, params.width);
			}
		}



		//recalcula el indice
		ultimo_indice = fin_bloque - indice;
		indice = fin_bloque;
	}
	//imprimimos el último
	imprimirFrame(params.output, Frames[ultimo_indice], params.height, params.width);


	return;

}