#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
using namespace std;

const int MAX_PATH = 1000;

int main() {

    struct stat info;
    const char* oldPathSym;
    const char* oldPathHard;
    const char* newPathSym;
    const char* newPathHard;
    string pTemp;

    cin >> pTemp;
    
    if (stat(pTemp.c_str(), &info) == -1) {

        perror("Error");

        return -1;

    }

    if ((info.st_mode & S_IFMT) == S_IFREG) {

        oldPathSym = pTemp.c_str();
        newPathSym = (pTemp + ".sym").c_str();

        if (symlink(oldPathSym, newPathSym) == -1) {

            perror("Error");

            return -1;

        }

        oldPathHard = pTemp.c_str();
        newPathHard = (pTemp + ".hard").c_str();

        if (link(oldPathHard, newPathHard) == -1) {

            perror("Error");

            return -1;

        }

    }

    else
        cout << "La ruta corresponde a un fichero no ordinario\n";

    return 0;

}