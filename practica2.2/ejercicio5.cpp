#include <stdio.h>
#include <fcntl.h>
using namespace std;

int main() {

    if (open("fichero", O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH | S_IXOTH) == -1) {

        perror("Error");

        return -1;

    }

    return 0;

}
