#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
using namespace std;

const int SIZE = 1000;

int main() {

    string pTemp;
    char path[256];
    DIR *dir;
    struct dirent *d_info;
    struct stat f_info, l_info;
    char* buf;
    float tam = 0;

    cin >> pTemp;

    dir = opendir(pTemp.c_str());

    if (dir == NULL) {

        perror("Error");

        return -1;

    }

    while ((d_info = readdir(dir)) != NULL) {
        
        if (strcmp(d_info->d_name, ".") && strcmp(d_info->d_name, "..")) {

            strcpy(path, pTemp.c_str());
            strcat(path, "/");
            strcat(path, d_info->d_name);

            if (stat(path, &f_info) == -1) {

                perror("Error");

                return -1;

            }

            if (lstat(path, &l_info) == -1) {

                perror("Error");

                return -1;

            }

            if (S_ISLNK(l_info.st_mode)) {

                buf = (char*)malloc(l_info.st_size + 1);
                readlink(path, buf, l_info.st_size + 1);
                cout << d_info->d_name << " -> " << buf << '\n';
                tam += f_info.st_size;

            }

            else {

                switch (f_info.st_mode & S_IFMT) {

                    case S_IFREG:

                    if (((f_info.st_mode & S_IEXEC) == 0)) {

                        cout << d_info->d_name << '\n';
                        tam += f_info.st_size;

                    }

                    break;

                    case S_IFDIR:
                    cout << d_info->d_name << '/' << '\n';
                    break;

                    default:
                    cout << "Otro\n";
                    break;

                }

                if (((f_info.st_mode & S_IEXEC) != 0) && ((f_info.st_mode & S_IFMT) != S_IFLNK) && ((f_info.st_mode & S_IFMT) != S_IFDIR)) {
                    cout << d_info->d_name << '*' << '\n';
                    tam += f_info.st_size;
                }

            }

        }
    
    }

    cout << "Tamaño total de los ficheros: " << tam / 1000 << "kB\n";

    closedir(dir);

    return 0;

}