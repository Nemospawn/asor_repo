#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
using namespace std;

const int SIZE = 1000;

int main() {

    struct rlimit limit;
    char buff[SIZE];

    cout << "Identificador del proceso: " << getpid() << '\n';
    cout << "Identificador del proceso padre: " << getppid() << '\n';
    cout << "Identificador del grupo de procesos: " << getpgid(0) << '\n';
    cout << "Identificador de sesión: " << getsid(0) << '\n';

    if (getrlimit(RLIMIT_NOFILE, &limit) == -1) {

        perror("Error");

        return -1;

    }

    cout << "Numero maximo de ficheros que puede abrir el proceso: " << limit.rlim_max << '\n';

    if (getcwd(buff, sizeof(buff)) == NULL) {

        perror("Error");

        return -1;

    }

    cout << "Directorio de trabajo actual: " << buff << '\n';

    return 0;

}