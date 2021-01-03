#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;

const int SIZE = 1000;

int main() {

    pid_t pid;
    string prog;
    int stdin, stdout, stderr;

    cin >> prog;
    
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

        if ((stdin = open("/dev/null", O_CREAT | O_WRONLY, 0777)) < 0 || (stdout = open("/tmp/daemon.out", O_CREAT | O_WRONLY, 0777)) < 0 
            || (stderr = open("/tmp/daemon.err", O_CREAT | O_WRONLY, 0777)) < 0) {

            perror("Error");

            return -1;

        }

        dup2(stdin, 0);
        dup2(stdout, 1);
        dup2(stderr, 2);

        sleep(5);

        if (execvp(prog.c_str(), NULL) == -1) {

            perror("Error");

            return -1;

        }
        
        break;

        default:
        break;

    }

    return 0;

}