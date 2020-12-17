// La diferencia entre st_mtime y st_ctime es que st_mtime se refiere a la última modificación
// del contenido de un fichero, mientras que st_ctime se refiere a la última modificación del
// estado del fichero, como por ejemplo, la información del i_nodo.

#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
using namespace std;

int main() {

    struct stat info;

    if (stat("fichero", &info) == -1) {

        perror("Error");

        return -1;

    }

    cout << "Numero major: " << major(info.st_dev) << '\n';
    cout << "Numero minor: " << minor(info.st_dev) << '\n';
    cout << "Numero de i-nodo: " << info.st_ino << '\n';
    cout << "Tipo de fichero: ";

    switch (info.st_mode & S_IFMT) {

        case S_IFDIR:
        cout << "Directorio\n";
        break;

        case S_IFLNK:
        cout << "Enlace simbolico\n";
        break;

        case S_IFREG:
        cout << "Fichero ordinario\n";
        break;

        default:
        cout << "Otro\n";
        break;

    }

    return 0;

}