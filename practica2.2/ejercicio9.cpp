// La diferencia entre st_mtime y st_ctime es que st_mtime se refiere a la última modificación
// del contenido de un fichero, mientras que st_ctime se refiere a la última modificación del
// estado del fichero, como por ejemplo, la información del i_nodo.

#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
using namespace std;

int main() {

    struct stat f_info, l_info;

    if (stat("fichero", &f_info) == -1) {

        perror("Error");

        return -1;

    }

    if (lstat("fichero", &l_info) == -1) {

        perror("Error");

        return -1;

    }

    cout << "Numero major: " << major(f_info.st_dev) << '\n';
    cout << "Numero minor: " << minor(f_info.st_dev) << '\n';
    cout << "Numero de i-nodo: " << f_info.st_ino << '\n';
    cout << "Tipo de fichero: ";

    if (S_ISLNK(l_info.st_mode))
        cout << "Enlace simbolico\n";

    else {

        switch (f_info.st_mode & S_IFMT) {

            case S_IFDIR:
            cout << "Directorio\n";
            break;

            case S_IFREG:
            cout << "Fichero ordinario\n";
            break;

            default:
            cout << "Otro\n";
            break;

        }

    }

    return 0;

}
