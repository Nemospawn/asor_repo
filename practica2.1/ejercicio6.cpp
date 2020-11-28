#include <iostream>
#include <unistd.h>
using namespace std;

int main() {

    cout << "Longitud maxima de los argumentos: " << sysconf(_SC_ARG_MAX) << '\n';
    cout << "Numero maximo de hijos: " << sysconf(_SC_CHILD_MAX) << '\n';
    cout << "Numero maximo de ficheros: " << sysconf(_SC_OPEN_MAX) << '\n';

    return 0;

}