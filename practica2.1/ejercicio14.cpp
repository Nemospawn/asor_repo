#include <iostream>
#include <stdio.h>
#include <time.h>
using namespace std;

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
   
    cout << "Año: " << (1900 + info->tm_year) << '\n';
   
    return 0;

}