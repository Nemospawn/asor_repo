#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
using namespace std;

const int SIZE = 1000;

int main() {

    int info;
    string hostname;
    struct addrinfo hints, *result, *rp;
    char host[SIZE];

    cin >> hostname;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;

    info = getaddrinfo(hostname.c_str(), NULL, &hints, &result);
    
    if (info != 0) {

        cout << "Error getaddrinfo(): " << gai_strerror(info) << '\n';

        return -1;

    }

    for (rp = result; rp != NULL; rp = rp->ai_next) {

        getnameinfo(rp->ai_addr, rp->ai_addrlen, host, sizeof(host), NULL, 0, NI_NUMERICHOST);

        cout << host << "    " << rp->ai_family << "    " << rp->ai_socktype << '\n';

    }

    freeaddrinfo(result);

    return 0;

}
