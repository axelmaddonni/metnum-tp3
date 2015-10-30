#include "header.h"

void vecinoMasCercano(Parametros &params) {

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

	int i, j, k;

	// Si framesIntermedios es impar, el frame intermedio toma el valor del vecino anterior. 

	//Imprimo parámetros actualizados
	params.output << (params.frames - 1)* params.framesIntermedios + params.frames << std::endl;
	params.output << params.height << " " << params.width << std::endl;
	params.output << params.framerate << std::endl ; //MODIFICAR POR EL FRAMERATE NUEVO


/* VERSION CARGANDO EN MEMORIA SOLO UN FRAME */

	vector<vector<int> >* frame = new vector<vector<int>>(params.height, vector<int>(params.width));
	
	for (k=0; k < params.frames ; k++){

		//Cargo la imagen actual
		for (i=0; i< params.height; i++){
			for (j=0; j<params.width; j++){
				params.input >> (*frame)[i][j];
			}
		}

		if (k != 0){
			imprimirNframes(params.output, *frame, params.height, params.width, params.framesIntermedios/2);
		}

		//Imprimo imagen original
		imprimirFrame(params.output, *frame, params.height, params.width);

		if (k != params.frames-1){
			if (params.framesIntermedios%2 == 0)
				imprimirNframes(params.output, *frame, params.height, params.width, params.framesIntermedios/2);
			else
				imprimirNframes(params.output, *frame, params.height, params.width, params.framesIntermedios/2 +1);
		}

	}
        delete frame;
}


/*

	
	// VERSION CARGANDO EN MEMORIA FRAME ANTERIOR Y SIGUIENTE //
	
	vector<vector<int> >* frameAnt = new vector<vector<int>>(params.height, vector<int>(params.width));
	vector<vector<int> >* frameSig = new vector<vector<int>>(params.height, vector<int>(params.width));
	vector<vector<int> >* aux;

	//Guardo primera imagen (original)	
	for (i=0; i< params.height; i++){
		for (j=0; j<params.width; j++){
			params.input >> (*frameAnt)[i][j];
		}
	}


	for (k=0; k< params.frames -1; k++){

		//imprimo imagen anterior
		imprimirFrame(params.output, *frameAnt, params.height, params.width);

		//Guardo imagen siguiente (original)
		for (i=0; i< params.height; i++){
			for (j=0; j<params.width; j++){
				params.input >> (*frameSig)[i][j];
			}
		}
 

		for (i=0; i< params.framesIntermedios; i++){
			if (i <= (params.framesIntermedios/2))
				imprimirFrame(params.output, *frameAnt, params.height, params.width);
			else
				imprimirFrame(params.output, *frameSig, params.height, params.width);
		}

		//Reutilizo la memoria allocada para los frames
		aux = frameAnt;
		frameAnt = frameSig;
		frameSig = aux;

	}

	//imprimo ultima imagen
	imprimirFrame(params.output, *frameAnt, params.height, params.width);

}

*/
