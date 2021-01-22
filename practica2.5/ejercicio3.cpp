#include <iostream>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
using namespace std;

const int SIZE = 1000;

int main() {

    struct addrinfo hints, *servaddr;
    int info, sd, n;
    string hostname, puerto, cm;
    char buff[SIZE];

    cin >> hostname >> puerto >> cm;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;

    info = getaddrinfo(hostname.c_str(), puerto.c_str(), &hints, &servaddr);
    
    if (info != 0) {

        cout << "Error getaddrinfo(): " << gai_strerror(info) << '\n';

        return -1;

    }

    sd = socket(servaddr->ai_family, servaddr->ai_socktype, 0);

    if (sd == -1) {

        perror("Socket");

        return -1;

    }

    cm += '\n';

    sendto(sd, cm.c_str(), cm.length(), 0, (struct sockaddr *)servaddr->ai_addr, servaddr->ai_addrlen);

    n = recvfrom(sd, buff, SIZE, 0, (struct sockaddr *)servaddr->ai_addr, &servaddr->ai_addrlen);

    buff[n] = '\0';

    cout << buff << '\n';

    close(sd);

    return 0;

}
