#include <iostream>
#include <stdio.h>
#include <time.h>
using namespace std;

int main() {

    time_t t = time(NULL);

    if (t == ((time_t) -1)) {

        perror("Error");

        return -1;

    }

    cout << "Segundos desde el Epoch: " << t << '\n';

    return 0;

}