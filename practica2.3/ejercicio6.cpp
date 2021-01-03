// Cuando el proceso padre termina antes que el hijo, el PPID del proceso hijo pasa
// a ser 1, correspondiente a 'systemd'. Cuando es el proceso hijo quien termina antes,
// dicho proceso pasa a un estado 'zombie'.

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
using namespace std;

const int SIZE = 1000;

int main() {

    pid_t pid;

    pid = fork();

    switch (pid) {

        case -1:
        perror("fork");
        return -1;

        case 0:
        
        if (setsid() < 0) {

            perror("Sesion");

            return -1;

        }

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

        if (chdir("/tmp") == -1) {

            perror("Error");

            return -1;

        }

        if (getcwd(buff, sizeof(buff)) == NULL) {

            perror("Error");

            return -1;

        }

        cout << "Directorio de trabajo actual: " << buff << '\n';
        
        break;

        default:
        cout << "Padre " << getpid() << " (hijo: " << pid << ")\n";
        break;

    }

    return 0;

}