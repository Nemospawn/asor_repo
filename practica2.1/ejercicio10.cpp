#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
using namespace std;

int main() {

    struct passwd *info = getpwuid(getuid());

    if (info == NULL) {

        perror("Error");

        return -1;

    }

    cout << "UID real: " << getuid() << '\n';
    cout << "UID efectivo: " << geteuid() << '\n';
    cout << "Nombre de usuario: " << info->pw_name << '\n';
    cout << "Directorio home: " << info->pw_dir << '\n';
    cout << "Descripcion de usuario: " << info->pw_gecos << '\n';

    return 0;

}