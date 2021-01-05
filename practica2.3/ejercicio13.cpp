#include <iostream>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
using namespace std;

void sigalrm_handler(int signal){

    unlink("ejercicio13");

}

void sigusr1_handler(int signal){

    return;

}

int main() {

    int sec;
    sigset_t signals;
    struct sigaction sigalrm_act, sigusr1_act;

    cin >> sec;

    sigemptyset(&signals);
    sigdelset(&signals, SIGALRM);
    sigdelset(&signals, SIGUSR1);

    sigalrm_act.sa_handler = sigalrm_handler;
    sigusr1_act.sa_handler = sigusr1_handler;

    sigemptyset(&sigalrm_act.sa_mask);
    sigemptyset(&sigusr1_act.sa_mask);

    sigalrm_act.sa_flags = 0;
    sigusr1_act.sa_flags = 0;

    if (sigaction(SIGALRM, &sigalrm_act, NULL) == -1) {

        perror("Error");

        return -1;

    }

    if (sigaction(SIGUSR1, &sigusr1_act, NULL) == -1) {

        perror("Error");

        return -1;

    }

    alarm(sec);

    sigsuspend(&signals);

    return 0;

}
