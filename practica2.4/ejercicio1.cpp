#include <iostream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main() {

    string com1, com2, arg1, arg2;
    int fd[2];
    pid_t pid;

    cin >> com1 >> arg1 >> com2 >> arg2;

    if (pipe(fd) == -1) {

        perror("pipe");

        return -1;

    }

    pid = fork();

    switch(pid) {

        case -1:
        perror("fork");
        return -1;

        case 0:

        close(fd[1]);
        close(0);

        dup2(fd[0], 0);
        
        execlp(com2.c_str(), com2.c_str(), arg2.c_str(), NULL);

        break;

        default:

        close(fd[0]);
        close(1);

        dup2(fd[1], 1);

        execlp(com1.c_str(), com1.c_str(), arg1.c_str(), NULL);
        
        wait(NULL);

        break;

    }

    return 0;

}