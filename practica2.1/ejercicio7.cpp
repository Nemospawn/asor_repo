#include <iostream>
#include <unistd.h>
using namespace std;

int main() {

    cout << "Numero maximo de enlaces: ";
    cout << pathconf("/home/cursoredes/Documents/Practica2.1/ejercicio7", _PC_LINK_MAX) << '\n';
    cout << "Tamaño maximo de la ruta: ";
    cout << pathconf("/home/cursoredes/Documents/Practica2.1/ejercicio7", _PC_PATH_MAX) << '\n';
    cout << "Longitud maxima del nombre del fichero: ";
    cout << pathconf("/home/cursoredes/Documents/Practica2.1/ejercicio7", _PC_NAME_MAX) << '\n';

    return 0;

}