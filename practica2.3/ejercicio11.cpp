#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
using namespace std;

int main() {

    sigset_t signals, pendientes;

    sigemptyset(&signals);
    sigaddset(&signals, SIGINT);
    sigaddset(&signals, SIGTSTP);

    if (sigprocmask(SIG_BLOCK, &signals, NULL) == -1) {

        perror("Error");

        return -1;

    }

    setenv("SLEEP_SECS", "10", 1);

    char* var = getenv("SLEEP_SECS");

    sleep(atoi(var));

    sigpending(&pendientes);

    if (sigismember(&pendientes, SIGINT))
        cout << "El proceso recibio la señal SIGINT\n";

    if (sigismember(&pendientes, SIGTSTP)) {

        cout << "El proceso recibio la señal SIGTSTP\n";
        cout << "Desbloqueando señal\n";

        sigdelset(&signals, SIGINT);

        if (sigprocmask(SIG_UNBLOCK, &signals, NULL) == -1) {

            perror("Error");

            return -1;

        }

        cout << "Proceso reanudado\n";

    }

    cout << "Finalizando\n";

    return 0;

}