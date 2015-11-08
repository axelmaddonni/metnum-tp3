#include "header.h"

void methodDispatch(int argc, char **argv) 
{
    switch (atoi(argv[3]))
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
			if (argc < 6) 
			{
				cout << "Falta el argumento de tamaño de bloques\n";
				exit(0);
			}
			else 
			{
				ParametrosConBloques params(argc, argv);
				splinesPorBloques(params);
				break;
			}
        }
		case 3:
		{
			Parametros params(argc, argv);
			eliminarFrames(params);
			break;
		}
        case 4:
        {
            Parametros params(argc, argv);
            Parametros params2(argc, (argv+4));
            ecm(params, params2);
            break;
        }
        case 5:
        {
            Parametros params(argc, argv);
            Parametros params2(argc, (argv+4));
            psnr(params, params2);
            break;
        }
        default:
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
