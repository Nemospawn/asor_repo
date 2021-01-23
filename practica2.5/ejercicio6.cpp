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

    struct sockaddr_storage addr;
    struct addrinfo hints, *servaddr;
    socklen_t addrlen = sizeof(addr);
    int info, sd, cl, n;
    string hostname, puerto;
    char msg[SIZE], host[NI_MAXHOST], serv[NI_MAXSERV];

    cin >> hostname >> puerto;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_flags = AI_PASSIVE;
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

    if (bind(sd, (struct sockaddr *)servaddr->ai_addr, servaddr->ai_addrlen) == -1) {

        perror("Bind");

        return -1;

    }

    listen(sd, 1);

    while (1) {

        cl = accept(sd, (struct sockaddr *)&addr, &addrlen);

        getnameinfo((struct sockaddr *)&addr, addrlen, host, NI_MAXHOST,
            serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);

        cout << "Conexión desde " << host << " " << serv << '\n';

        while (n = recv(cl, msg, SIZE, 0)) {
            
            msg[n] = '\0';

            send(cl, msg, n, 0);

        }

        cout << "Conexion terminada\n";

        close(cl);

    }

    return 0;

}