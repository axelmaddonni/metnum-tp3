#include "header.h"
#include <assert.h>
#include <stdlib.h> 
#include <math.h>

//Imprime en el primer output los PSNR de cada frame y devuelve el PSNR promedio entre todos

/* ejemplo modo de uso

./main tests/tenis/tenis_Lineal_FramesInt2.out tests/tenis/psnr_fi2_lineal.out 5 2 tests/tenis/tenisReal.in basura.out 5 2

*/

double psnr (Parametros &params, Parametros &params2){

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
	double max = 0;
	double ecm, psnr;
	int cant_inf = 0;
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
			params2.input >> (*frameB)[i][j];
			}
		}

		ecm = 0;
		for (i=0; i < params.height; i++){
			for (j=0; j < params.width; j++){
			ecm +=  pow ( abs( (*frameA)[i][j] - (*frameB)[i][j] ), 2);
			}
		}

		ecm = ecm / (params.width * params.height);
		psnr = 10 * log10 ( pow(255,2) / ecm);

		//Imprimo PSNR del frame k
		params.output << "PSNR frame " << k << ": " << psnr << std::endl ;

		if (ecm != 0){
			//Sumo para calcular el promedio entre todos
			promedio += psnr;
			max = (psnr > max) ? psnr : max ;

		} else{
			cant_inf++;
		}

	}

	promedio = promedio / (frames - cant_inf);

	params.output << "PSNR promedio: " << promedio << std::endl;
	params.output << "Máximo psnr obtenido: " << max << std::endl;
	params.output << "Nota: el promedio y el max no tiene en cuenta los valores inf." << std::endl; 

	cout << "PSNR promedio: " << promedio << std::endl;
	cout << "Máximo psnr obtenido: " << max << std::endl;

	return promedio;

}


	