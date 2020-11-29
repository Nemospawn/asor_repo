#include <iostream>
#include <stdio.h>
#include <time.h>
using namespace std;

const int SIZE = 1000;

int main() {

    time_t t;
    struct tm *info;
   
    if (time(&t) == -1) {

        perror("Error");

        return -1;

    }
   
    info = localtime(&t);

    if (info == NULL) {

        cout << "An error has occurred\n";

        return -1;

    }

    char fecha[SIZE];
   
    setlocale(LC_ALL, "es_ES");

    strftime(fecha, SIZE, "%A, %d de %B de %Y, %H:%M", info);

    cout << fecha << '\n';
   
    return 0;

}