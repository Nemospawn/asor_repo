#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main() {

    string pTemp;
    const char* path;
    ofstream file;

    cin >> pTemp;

    file.open(pTemp.c_str());

    if (!file.is_open()) {

        cout << "No se pudo abrir el fichero\n";

        return -1;

    }

    for (int i = 1; i <= 5; ++i)
        file << "Linea " << i << '\n';

    file.close();

    return 0;

}
