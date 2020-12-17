#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
using namespace std;

int main() {

    umask(0047);

    if (open("fichero", O_CREAT, 0777) == -1) {

        perror("Error");

        return -1;

    }
    
    return 0;

}