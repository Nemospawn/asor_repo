#include <iostream>
#include <string.h>
#include <errno.h>
#include <unistd.h>
using namespace std;

int main() {

    if (setuid(2) == -1) {

        cout << "Numero de error: " << errno << '\n';
        cout << "Error: " << strerror(errno) << '\n';

        return -1;

    }

    return 1;

}
