#include <iostream>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
using namespace std;

int main() {

    string in;
    int fd;

    getline(cin, in);

    if ((fd = open("pipe", O_WRONLY)) == -1) {

        perror("Error");

        return -1;

    }

    write(fd, in.c_str(), strlen(in.c_str()));
    write(fd, "\n", 1);

    return 0;

}