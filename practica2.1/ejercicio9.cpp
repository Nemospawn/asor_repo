#include <iostream>
#include <unistd.h>
using namespace std;

int main() {

    cout << "UID real: " << getuid() << '\n';
    cout << "UID efectivo: " << geteuid() << '\n';

    return 0;

}

// Para comprobar si el fichero tiene activado el setuid o no bastaría con
// usar el comando ls -l ejercicio9.cpp y comprobar si hay una letra 's'
// en el output:
//-rwSrw-r-- 1 cursoredes cursoredes 190 Nov 28 20:43 ejercicio9.cpp