#include <iostream>
#include <stdio.h>
#include <signal.h>
using namespace std;

volatile int sigint_cont = 0, sigtstp_cont = 0;

void sigint_handler(int signal){

    ++sigint_cont;

}

void sigtstp_handler(int signal) {

    ++sigtstp_cont;

}

int main() {

    struct sigaction sigint_act, sigtstp_act;

    sigint_act.sa_handler = sigint_handler;
    sigtstp_act.sa_handler = sigtstp_handler;

    sigemptyset(&sigint_act.sa_mask);
    sigemptyset(&sigtstp_act.sa_mask);

    sigint_act.sa_flags = 0;
    sigtstp_act.sa_flags = 0;

    if (sigaction(SIGINT, &sigint_act, NULL) == -1) {

        perror("Error");

        return -1;

    }

    if (sigaction(SIGTSTP, &sigtstp_act, NULL) == -1) {

        perror("Error");

        return -1;

    }

    while ((sigint_cont + sigtstp_cont) < 10);

    cout << "Se recibio la señal SIGINT " << sigint_cont << " veces\n";
    cout << "Se recibio la señal SIGTSTP " << sigtstp_cont << " veces\n";

    return 0;

}
