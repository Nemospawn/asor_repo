#include <iostream>
#include <string.h>
#include <errno.h>
#include <unistd.h>
using namespace std;

int main() {

    if (setuid(2) == -1) {

        cout << "Numero de error: ";
        cout << errno;
        cout << '\n';
        cout << "Error: ";
        cout << strerror(errno);
        cout << '\n';

        return -1;

    }

    return 1;

}