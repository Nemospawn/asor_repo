#include <iostream>
#include <string>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
using namespace std;

const int SIZE = 1000;

int main() {

    string pTemp;
    int newFd;
    time_t t;
    struct tm *info;

    cin >> pTemp;

    if ((newFd = open(pTemp.c_str(), O_CREAT | O_WRONLY, 0777)) < 0) {

        perror("Error");

        return -1;

    }

    int test = lockf(newFd, F_TEST, 0);

    if (test == -1) {

        cout << "Cerrojo bloqueado\n";

        return -1;

    }

    cout << "Cerrojo desbloqueado\n";

    lockf(newFd, F_LOCK, 0);
   
    if (time(&t) == -1) {

        perror("Error");

        return -1;

    }

    info = localtime(&t);

    if (info == NULL) {

        cout << "An error has occurred\n";

        return -1;

    }

    char hora[SIZE];

    strftime(hora, SIZE, "%H:%M", info);

    write(newFd, hora, sizeof(hora));

    sleep(3);

    lockf(newFd, F_ULOCK, 0);

    return 0;

}