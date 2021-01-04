#include <iostream>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
using namespace std;

int main() {

    int sec;
    sigset_t signals;
    pid_t pid;

    cin >> sec;

    pid = fork();

    switch (pid) {

        case -1:
        perror("fork");
        return -1;

        case 0:
        sigemptyset(&signals);
        sigsuspend(&signals);
        kill(getppid(), SIGTERM);
        break;

        default:
        sleep(sec);
        unlink("ejercicio13");
        kill(pid, SIGTERM);
        break;

    }

    return 0;

}