#include <iostream>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
using namespace std;

const int SIZE = 256;

int main() {

    int pipe1, pipe2;
    fd_set readset;
    char buff[SIZE];

    while(1) {

        memset(buff, 0, SIZE);

        if ((pipe1 = open("pipe1", O_RDONLY | O_NONBLOCK)) == -1) {

            perror("Open pipe1");

            return -1;

        }

        if ((pipe2 = open("pipe2", O_RDONLY | O_NONBLOCK)) == -1) {

            perror("Open pipe2");

            return -1;

        }

        FD_ZERO(&readset);
        FD_SET(pipe1, &readset);
        FD_SET(pipe2, &readset);

        select(pipe1 + pipe2 + 1, &readset, NULL, NULL, NULL);

        if (FD_ISSET(pipe1, &readset)) {

            write(1, "Datos leidos del pipe1: ", 24);
            read(pipe1, &buff, sizeof(buff));
            write(1, &buff, strlen(buff));

            close(pipe1);

        }

        else {

            write(1, "Datos leidos del pipe2: ", 24);
            read(pipe2, &buff, sizeof(buff));
            write(1, &buff, strlen(buff));

            close(pipe2);

        }

    }

    return 0;

}