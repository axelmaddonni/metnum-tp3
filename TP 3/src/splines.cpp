#include "header.h"
#include <vector>
#include <tgmath.h>

using std::endl;
using std::vector;

void splines(Parametros &params) {
	params.output << (params.frames - 1) * params.framesIntermedios + params.frames << endl;
	params.output << params.height << " " << params.width << endl;
	params.output << params.framerate << endl;

	//-----matriz de Cs------
	vector<vector<double>> M_C (params.frames, vector<double>(params.frames, 0));
	//----en la primera fila queda: 1 0 ... 0
	M_C[0][0] = 1;
	for (int i=1; i < params.frames-1; i++) {
		//--i-1 = 1*(x_i+1 - x_i)
		M_C[i][i - 1] = params.framesIntermedios + 1;
		//--i = 4*(x_i+1 - x_i)
		M_C[i][i] = 4 * (params.framesIntermedios + 1);
		//--i+1 = 1*(x_i+1 - x_i)
		M_C[i][i + 1] = params.framesIntermedios + 1;
	}
	//----en la última fila queda: 0 ... 0 1
	M_C[params.frames - 1][params.frames - 1] = 1;

	//vector de los resultados (la derecha la igualdad de las ecuaciones)
	vector<double> res (params.frames, 0);

	double aux;
	//----diagonalizamos la matriz
	for (int i=1; i < params.frames - 1; i++) {
		aux = M_C[i][i-1] / M_C[i-1][i-1];
		M_C[i][i-1] = 0;
		res[i] = res[i] - res[i-1] * aux;
		aux = M_C[params.frames - 1 - i][params.frames - i] / M_C[params.frames - i][params.frames - i];
		M_C[params.frames - 1 - i][params.frames - i] = 0;
		res[params.frames - 1 - i] = res[params.frames - 1 - i] - res[params.frames - i] * aux;
	}

	//---Sacamos los valores de C
	vector<double> C (params.frames, 0);
	for (int i = 0; i < params.frames; i++) {
		//---Como M_C es diagonal solo tenemos que pasar dividiendo el valor de la diagonal
		C[i] = res[i] / M_C[i][i];
	}

	//---Despejamos los valores de D (usando C)
	vector<double> D(params.frames, 0);
	for (int i = 0; i < params.frames; i++) {
		D[i] = (C[i+1] - C[i]) / ( (params.framesIntermedios + 1) * 3);
	}


	double B;

	//---M1: cada pixel es un x_i-1
	vector<vector<int>> M1 (params.height, vector<int>(params.width, 0));
	//---M2: cada pixel es un x_i
	vector<vector<int>> M2 (params.height, vector<int>(params.width, 0));

	for (int i = 0; i < params.height; i++) {
		for (int j = 0; j < params.width; j++) {
			params.input >> M2[i][j];
		}
	}
	//---En M_sal vamos a guardar los valores de los frames intermedios que vamos sacando
	vector<vector<vector<int>>> M_sal (params.framesIntermedios, vector<vector<int>>(params.height, vector<int>(params.width, 0)));

	for (int k = 0; k < params.frames - 1; k++) {
		
		for (int i = 0; i < params.height; i++) {
			for (int j = 0; j < params.width; j++) {
				M1[i][j] = M2[i][j];
			}
		}
		for (int i = 0; i < params.height; i++) {
			for (int j = 0; j < params.width; j++) {
				params.input >> M2[i][j];
			}
		}

		//---Imprimimos x_i
		imprimirFrame(params.output, M1, params.height, params.width);
		for (int i = 0; i < params.height; i++) {
			for (int j = 0; j < params.width; j++) {
				//---Sacamos el b_i
				B = M2[i][j] - M1[i][j] - C[k] * pow(params.framesIntermedios + 1, 2) - D[k] * pow(params.framesIntermedios + 1, 3);
				B = B / (params.framesIntermedios + 1);

				for (int f = 0; f < params.framesIntermedios; f++) {
					//---aux = (x - x_i) //distancia entre el x_i y el x del nuevo frame
					int aux = f + 1;
					//---Aplicamos la función al x del nuevo frame
					M_sal[f][i][j] = M1[i][j] + B * aux + C[k] * pow(aux, 2) + D[k] * pow(aux, 3);
				}
			}
		}
		
		for (int f = 0; f < params.framesIntermedios; ++f) {
			//---Imprimimos los nuevos frames
			imprimirFrame(params.output, M_sal[f], params.height, params.width);
		}
	}
	//---Al salir nos falta imprimir el último frame
	imprimirFrame(params.output, M2, params.height, params.width);
}
