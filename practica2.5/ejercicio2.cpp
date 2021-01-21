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
    struct addrinfo hints, *servaddr, *rp;
    struct tm *tinfo;
    socklen_t addrlen = sizeof(addr);
    time_t t;
    int info, sd, n, m;
    string hostname, puerto;
    char cm[SIZE], host[NI_MAXHOST], serv[NI_MAXSERV], tbuff[SIZE], dbuff[SIZE];

    cin >> hostname >> puerto;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_flags = AI_PASSIVE;
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

    if (bind(sd, (struct sockaddr *)servaddr->ai_addr, servaddr->ai_addrlen) == -1) {

        perror("Bind");

        return -1;

    }

    do {

        n = recvfrom(sd, cm, SIZE, 0, (struct sockaddr *)&addr, &addrlen);

        cm[n] = '\0';

        getnameinfo((struct sockaddr *) &addr, addrlen, host, NI_MAXHOST,
            serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);

        cout << n << " bytes de " << host << ":" << serv << '\n';
    
        if (time(&t) == -1) {

            perror("Error");

            return -1;

        }
    
        tinfo = localtime(&t);

        if (tinfo == NULL) {

            cout << "An error has occurred\n";

            return -1;

        }

        if (strcmp(cm, "t\n") == 0) {

            m = strftime(tbuff, SIZE, "%H:%M:%S %p", tinfo);

            sendto(sd, tbuff, m, 0, (struct sockaddr *)&addr, addrlen);

        }

        else {

            if (strcmp(cm, "d\n") == 0) {

                m = strftime(dbuff, SIZE, "%d-%m-%Y", tinfo);

                sendto(sd, dbuff, m, 0, (struct sockaddr *)&addr, addrlen);

            }

            else {

                if (strcmp(cm, "q\n") != 0)
                    cout << "Comando no soportado " << cm;

            }

        }

    }

    while (strcmp(cm, "q\n") != 0);

    cout << "Saliendo...\n";

    close(sd);

    return 0;

}