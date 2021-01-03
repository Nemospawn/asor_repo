// La version que tiene implementada la funcion execvp no imprime la última cadena,
// puesto que, al terminar la ejecución del programa que toma como argumento, la función
// no retorna nada y el programa principal termina de ejecutarse después de execvp.

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

const int SIZE = 1000;

int main() {

    // VERSION CON SYSTEM
    char prog[SIZE];

    cin >> prog;

    system(prog);

    // VERSION CON EXECVP
    /*string prog;

    cin >> prog;

    if (execvp(prog.c_str(), NULL) == -1) {

        perror("Error");

        return -1;

    }*/

    cout << "El comando termino de ejecutarse\n";

    return 0;

}