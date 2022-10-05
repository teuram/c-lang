#include <netinet/in.h> //structure for storing address information
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h> //for socket APIs
#include <sys/types.h>
#include <string.h>

int servSockD;

int main(int argc, char const* argv[]) {

    servSockD = socket(AF_INET, SOCK_STREAM, 0);

    char* ser = "this message recvested from server";

    char buffer[8192];

    struct sockaddr_in servAddr;

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(9001);
    servAddr.sin_addr.s_addr = INADDR_ANY;

    bind(servSockD, (struct sockaddr*)&servAddr,
    sizeof(servAddr));

    listen(servSockD, 3);

    while(1) {
        int clientSocket = accept(servSockD, NULL, NULL);

        recv(clientSocket, buffer, sizeof(buffer), 0);
        printf("message from client: %s\n", buffer);
        fflush(stdout);
        memset(buffer, 0, sizeof(buffer));

        send(clientSocket, ser, sizeof(char) * strlen(ser), 0);

        close(clientSocket);
    }

    shutdown(servSockD, SHUT_RDWR);

    return 0;
}

