#include <iostream>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/wait.h>
using namespace std;

const int SIZE = 1000;

int main() {

    string in;
    char out[SIZE], buff[SIZE];
    int p_h[2], h_p[2], cont = 1;
    pid_t pid;

    if (pipe(p_h) == -1 || pipe(h_p) == -1) {

        perror("pipe");

        return -1;

    }

    fd_set setfd;
    FD_ZERO(&setfd);
    FD_SET(h_p[0], &setfd);

    pid = fork();

    switch(pid) {

        case -1:
        perror("fork");
        return -1;

        case 0:

        close(p_h[1]);
        close(h_p[0]);

        while (cont < 10) {

            read(p_h[0], &out, sizeof(out));
            write(1, &out, strlen(out));
            write(1, "\n", 1);

            sleep(1);

            write(h_p[1], "1", 1);

            ++cont;

        }

        write(h_p[1], "q", 1);

        break;

        default:

        close(p_h[0]);
        close(h_p[1]);

        getline(cin, in);

        while (strcmp(buff, "q") != 0) {

            write(p_h[1], in.c_str(), sizeof(in.c_str()));

            select(sizeof(p_h) + sizeof(h_p) + 1, &setfd, NULL, NULL, NULL);

            read(h_p[0], &buff, sizeof(buff));

        }

        wait(NULL);
        
        break;

    }

    return 0;

}