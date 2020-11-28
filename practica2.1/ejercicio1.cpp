#include <stdio.h>
#include <unistd.h>
using namespace std;

int main() {

    if (setuid(2) == -1) {

        perror("Error");

        return -1;

    }

    return 1;

}
