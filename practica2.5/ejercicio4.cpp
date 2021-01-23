#include <iostream>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
using namespace std;

const int SIZE = 1000;

int main() {

    struct sockaddr_storage addr;
    struct addrinfo hints, *servaddr;
    struct tm *tinfo;
    socklen_t addrlen = sizeof(addr);
    time_t t;
    fd_set readset;
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

    while (1) {

        FD_ZERO(&readset);
        FD_SET(sd, &readset);
        FD_SET(0, &readset);

        select(sd + 0 + 1, &readset, NULL, NULL, NULL);

        if (FD_ISSET(sd, &readset)) {

            n = recvfrom(sd, cm, SIZE, 0, (struct sockaddr *)&addr, &addrlen);

            getnameinfo((struct sockaddr *)&addr, addrlen, host, NI_MAXHOST, 
                serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);

            cout << n << " bytes de " << host << ":" << serv << '\n';

        }

        else {

            n = read(0, cm, SIZE);

            cout << n << " bytes de entrada estandar\n";

        }

        cm[n] = '\0';

        if (strcmp(cm, "q\n") == 0)
            break;

        else {

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

                if (FD_ISSET(sd, &readset))
                    sendto(sd, tbuff, m, 0, (struct sockaddr *)&addr, addrlen);

                else
                    cout << tbuff << '\n';

            }

            else {

                if (strcmp(cm, "d\n") == 0) {

                    m = strftime(dbuff, SIZE, "%d-%m-%Y", tinfo);

                    if (FD_ISSET(sd, &readset))
                        sendto(sd, dbuff, m, 0, (struct sockaddr *)&addr, addrlen);

                    else
                        cout << dbuff << '\n';

                }

                else {

                    if (strcmp(cm, "q\n") != 0)
                        cout << "Comando no soportado " << cm;

                }

            }

        }

    }

    sendto(sd, "", 0, 0, (struct sockaddr *)&addr, addrlen);

    cout << "Saliendo...\n";

    close(sd);

    return 0;

}