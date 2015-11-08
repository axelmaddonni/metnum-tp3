#ifndef HEADER_HH
#define HEADER_HH

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <memory>

using std::cout;
using std::ofstream;
using std::ifstream;
using std::atoi;
using std::vector;
using std::unique_ptr;

auto inputLambda = [](ifstream &input, int temp){ return input >> temp, temp;};

struct Parametros
{
    Parametros (int argc, char **argv)
        :   input(argv[1], ifstream::in),
            output(argv[2]),
            metodo(atoi(argv[3])),
            framesIntermedios(atoi(argv[4])),
            frames(inputLambda(input, 0)),
            height(inputLambda(input, 0)),
            width(inputLambda(input, 0)),
            framerate(inputLambda(input, 0))
            {}

    virtual ~Parametros()
    { 
        input.close();
        output.close(); 
    }

    ifstream input;
    ofstream output;
    const int metodo;
    const int framesIntermedios;
    const int frames;
    const int height;
    const int width;
    const double framerate;
};

struct ParametrosConBloques : public Parametros
{
    ParametrosConBloques (int argc, char **argv)
		:	Parametros(argc, argv),
			tamBloque(atoi(argv[5]))
			{}
	
	const int tamBloque;
};

void methodDispatch(int, char **);
void vecinoMasCercano(Parametros&);
void lineal(Parametros&);
void splines(Parametros&);
void splinesPorBloques(ParametrosConBloques&);
void eliminarFrames(Parametros&);
double ecm (Parametros&, Parametros&);
double psnr (Parametros&, Parametros&);

void imprimirFrame (ofstream &output, const vector<vector<int>> &f, const int height, const int width);
void imprimirNframes (ofstream &output, const vector<vector<int>> &f, const int height, const int width, const int n);

#endif //HEADER_HH
