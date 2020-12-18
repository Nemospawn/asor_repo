#include <iostream>
#include <string>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
using namespace std;

int main() {

    string pTemp;
    int newFd;

    cin >> pTemp;

    if ((newFd = open(pTemp.c_str(), O_CREAT | O_WRONLY, 0777)) < 0) {

        perror("Error");

        return -1;

    }

    dup2(newFd, 1);

    for (int i = 1; i <= 5; ++i)
        cout << "Linea " << i << '\n';
    
    return 0;

}
