#include "header.h"

using std::endl;
using std::move;

void lineal(Parametros &params) 
{
    params.output << (params.frames - 1) * params.framesIntermedios + params.frames << endl;
    params.output << params.height << " " << params.width << endl;
    params.output << params.framerate << endl;

    vector<vector<int>> frameAnt(params.height, vector<int>(params.width));
    vector<vector<int>> frameSig(params.height, vector<int>(params.width));
    //despues lo necesito, pero no lo inicializo
    vector<vector<int>> dummy;
    //matriz frames intermedios
    vector<vector<vector<int>>> frameInt(params.framesIntermedios, vector<vector<int>>(params.height, vector<int>(params.width)));
        
    //cargo el primer frame y lo imprimo
    for (int i = 0; i < params.height; i++)
    {
        for (int j = 0; j < params.width; j++)
        {
            params.input >> frameAnt[i][j];
        }
    }
    imprimirFrame(params.output, frameAnt, params.height, params.width);

    for (int k = 0; k < params.frames - 1; k++)
    {
        //cargo el frame actual
        for (int i = 0; i < params.height; i++)
        {
            for (int j = 0; j < params.width; j++)
            {
                params.input >> frameSig[i][j];
            }
        }


        for (int i = 0; i < params.height; i++)
        {
            for (int j = 0; j < params.width; j++)
            {
                double m = ((double) (frameSig[i][j] - frameAnt[i][j])) / ((double) (params.framesIntermedios + 1));
                double b = frameAnt[i][j];
                for (int x = 1; x <= params.framesIntermedios; x++)
                {
                    // el " + 0.5 " es para que el cast a entero de double sea redondeando y no tomando floor (parte entera)
                    frameInt[x - 1][i][j] = m * x + b + 0.5;
                }
            }
        }


        //imprimo los frames intermedios
        for (int i = 0; i < params.framesIntermedios; i++)
        {
            imprimirFrame(params.output, frameInt[i], params.height, params.width);
        }
        //imprimo el frame siguiente
        imprimirFrame(params.output, frameSig, params.height, params.width);

        dummy = move(frameAnt);
        frameAnt = move(frameSig);
        frameSig = move(dummy);
    }
}
