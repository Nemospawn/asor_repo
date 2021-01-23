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
    string hostname, puerto, msg;
    char buff[SIZE];

    cin >> hostname >> puerto;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

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

    if (connect(sd, (struct sockaddr *)servaddr->ai_addr, servaddr->ai_addrlen) == -1) {

        perror("Connect");

        return -1;

    }

    while (1) {

        cin >> msg;

        if (msg == "Q")
            break;

        send(sd, msg.c_str(), msg.length(), 0);

        n = recv(sd, buff, SIZE, 0);

        buff[n] = '\0';

        cout << buff << '\n';

    }

    close(sd);

    return 0;

}