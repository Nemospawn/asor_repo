#include <iostream>
#include <stdio.h>
#include <sys/utsname.h>
using namespace std;

int main() {

    struct utsname buffer;

    if (uname(&buffer) == -1) {

        perror("Error");

        return -1;

    }

    int opt;

    cout << "Choose an option:\n";
    cout << "1 - Show system name\n";
    cout << "2 - Show node name\n";
    cout << "3 - Show release\n";
    cout << "4 - Show version\n";
    cout << "5 - Show machine\n";
    cout << "6 - Show domain name\n";
    cout << "Option: ";
    cin >> opt;

    switch(opt) {

        case 1:
        cout << "System name: " << buffer.sysname << '\n';
        break;

        case 2:
        cout << "Node name: " << buffer.nodename << '\n';
        break;

        case 3:
        cout << "Release: " << buffer.release << '\n';
        break;

        case 4:
        cout << "Version: " << buffer.version << '\n';
        break;

        case 5:
        cout << "Machine: " << buffer.machine << '\n';
        break;

        case 6:
        cout << "Domain name: " << buffer.domainname << '\n';
        break;

        default:
        cout << "Error: incorrect option\n";
        break;

    }
    
    return 0;

}