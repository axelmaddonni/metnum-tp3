#include "header.h"

void methodDispatch(Parametros &params) 
{
    switch (params.metodo)
    {
        case 0:
        {
            vecinoMasCercano(params);
            break;
        }
        case 1:
        {
            lineal(params);
            break;
        }
        case 2:
        {
            splines(params);
            break;
        }
    }
}

void imprimirFrame (ofstream &output, const vector<vector<int>> &f, const int height, const int width)
{
    for (int i=0; i < height; i++)
    {
        for (int j=0; j < width; j++)
        {
            output << f[i][j];
            if (j != (width-1)) output << " ";
        }
        output << std::endl;
    }
}

void imprimirNframes (ofstream &output, const vector<vector<int>> &f, const int height, const int width, const int n)
{
    for (int i=0; i< n; i++)
    {
        imprimirFrame (output, f, height, width);
    }
}
