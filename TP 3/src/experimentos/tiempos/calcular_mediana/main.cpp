#include <iostream>
#include <math.h>
#include <algorithm>
#include <vector>

using namespace std;
using std::sort;

int main (int argc, char **argv) {
	
	vector<int> datos(argc, 0);
	for (int i = 1; i < argc; ++i) {
		datos[i-1] = atoi(argv[i]);
	}

	sort(datos.begin(), datos.end());

	cout << datos[ceil(argc / 2)] << endl;

    return 0;
}