// Algoritmo para eliminar frames intermedios de un video

#include "header.h"
#include <assert.h>
#include <limits>

void eliminarFrames (Parametros &params){
	
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

	//std::cout << params.framesIntermedios << ' ' << params.frames << std::endl;

	assert(params.framesIntermedios < (params.frames -2));

	params.output << (params.frames/(params.framesIntermedios+1)) + ( (params.frames % (params.framesIntermedios+1) != 0) ? 1 : 0 ) << std::endl;
	params.output << params.height << " " << params.width << std::endl;
	params.output << params.framerate << std::endl ;

	int k = 0;
	int i, j;

	vector<vector<int> >* frame = new vector<vector<int>>(params.height, vector<int>(params.width));

	while (k < params.frames){

		if (k % (params.framesIntermedios+1) == 0 ){
			
			//Cargo la imagen actual
			for (i=0; i < params.height; i++){
				for (j=0; j < params.width; j++){
				params.input >> (*frame)[i][j];
				}
			}

			imprimirFrame(params.output, *frame, params.height, params.width);
		
		}else{
			// tiro el frame
			for (i=0; i < params.height; i++){
				//ignoro la linea
				//params.input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				for (j=0; j < params.width; j++){
					params.input >> (*frame)[i][j];
					}
				}
			}
		
		k++;

	}

	delete frame;

}