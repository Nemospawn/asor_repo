#include <iostream>
#include <stdio.h>
#include <sys/time.h>
using namespace std;

int main() {

    struct timeval t;
    suseconds_t ini, fin;

    if (gettimeofday(&t, NULL) == -1) {

        perror("Error");

        return -1;

    }

    ini = t.tv_usec;

    for (int i = 1; i <= 1e6; ++i);

    if (gettimeofday(&t, NULL) == -1) {

        perror("Error");

        return -1;

    }

    fin = t.tv_usec;

    cout << "El bucle tarda " << (fin - ini) << " microsegundos en completarse" << '\n';

    return 0;

}