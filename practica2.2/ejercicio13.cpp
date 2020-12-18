// El orden de las redirecciones influye. En los casos dados en el enunciado, “ls > dirlist 2>&1”
// ambos flujos, el de salida estándar y el de salida estándar de error, apuntan al fichero 
// "dirlist", mientras que en el segundo caso, la salida estándar apunta al fichero, pero la
// salida estándar de error sigue apuntando a la consola.

#include <iostream>
#include <string>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
using namespace std;

int main() {

    string pTemp;
    int newFd;

    cin >> pTemp;

    if ((newFd = open(pTemp.c_str(), O_CREAT | O_WRONLY, 0777)) < 0) {

        perror("Error");

        return -1;

    }

    dup2(newFd, 1);
    dup2(newFd, 2);

    for (int i = 1; i <= 5; ++i) {

        cout << "Linea " << i << '\n';
        cerr << "Error " << i << '\n';

    }
    

    return 0;

}