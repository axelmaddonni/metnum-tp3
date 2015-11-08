#include "header.h"
#include <assert.h>
#include <stdlib.h> 
#include <math.h>

//Imprime en el primer output los ECM de cada frame y devuelve el ECM promedio entre todos

/* ejemplo modo de uso

./main tests/tenis/tenis_Lineal_FramesInt2.out tests/tenis/ecm_fi2_lineal.out 4 2 tests/tenis/tenisReal.in basura.out 4 2

*/

double ecm (Parametros &params, Parametros &params2){

	/* Parámetros:
	ifstream input;
	const int metodo;
	const int framesIntermedios;
	const int frames;
	const int height;
	const int width;
	const int framerate; 
	ofstream output;
	*/

	assert(params.height == params2.height);
	assert(params.width == params2.width );

	int frames = (params.frames <= params2.frames) ? params.frames : params2.frames;

	double promedio = 0;
	double ecm;
	double max = 0;
	int i,j,k;
	
	vector<vector<double> >* frameA = new vector<vector<double>>(params.height, vector<double>(params.width));
	vector<vector<double> >* frameB = new vector<vector<double>>(params.height, vector<double>(params.width));

	for (k=0; k< frames; k++){

		//cargo Frame A
		for (i=0; i < params.height; i++){
			for (j=0; j < params.width; j++){
			params.input >> (*frameA)[i][j];
			}
		}

		//cargo Frame B
		for (i=0; i < params.height; i++){
			for (j=0; j < params.width; j++){
			params2.input >> (*frameA)[i][j];
			}
		}

		ecm = 0;

		for (i=0; i < params.height; i++){
			for (j=0; j < params.width; j++){
			ecm +=  pow ( abs( (*frameA)[i][j] - (*frameB)[i][j] ), 2);
			}
		}

		//cout << ecm << std::endl;

		promedio += ecm; //sumo el ecm sin haberlo dividido por el mn , lo divido al final una vez sumados todos

		ecm = ecm / (params.width * params.height);

		//Imprimo ECM del frame k
		params.output << "ECM frame " << k << ": " << ecm << std::endl ;
 
 		max = (ecm > max) ? ecm : max ;
		
	}

	promedio = promedio / (params.width * params.height);

	promedio = promedio / frames;

	params.output << "ECM promedio: " << promedio << std::endl;
	params.output << "Máximo error obtenido: " << max << std::endl;

	return promedio;

}


