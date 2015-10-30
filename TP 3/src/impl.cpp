#include "header.h"

void methodDispatch(int argc, char **argv) 
{
    switch (params.metodo)
    {
        case 0:
        {
			Parametros params(argc, argv);
            vecinoMasCercano(params);
            break;
        }
        case 1:
        {
			Parametros params(argc, argv);
            lineal(params);
            break;
        }
        case 2:
        {
			Parametros params(argc, argv);
            splines(params);
            break;
        }
		case default:
		{
			cout << "Ese no es un metodo soportado.\n";
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
