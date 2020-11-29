#include <iostream>
#include <string.h>
#include <unistd.h>
using namespace std;

int main() {

    for (int i = 0; i <= 255; ++i)
        cout << "Error: " << strerror(i) << '\n';

    return 1;

}
