#include <netinet/in.h> //structure for storing address information
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h> //for socket APIs
#include <sys/types.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void load_user_settings() {
    {
        struct stat st = {0};

        if (stat("data", &st) == -1) {
            mkdir("data", 0700);
        }
    }

}

int main(int argc, char const* argv[]) {

    while(1) {

        int sockD = socket(AF_INET, SOCK_STREAM, 0);
        struct sockaddr_in servAddr;
        int fd_client;

        servAddr.sin_family = AF_INET;
        servAddr.sin_port = htons(9001);

        if(inet_pton(AF_INET, "127.0.0.1", &servAddr.sin_addr) <= 0) {
            perror("\nInvalid address/ Address not supported \n");
            return 0;
        }

        char buffer[8192];

        printf("enter message: ");
        fgets(buffer, 8192, stdin);


        fd_client = connect(sockD, (struct sockaddr*)&servAddr, sizeof(servAddr));

        if (fd_client == -1) {
            printf("Error...\n");
            return 0;
        }


        if(strlen(buffer) == 2 & buffer[0] == 'q') {
            puts("exit...");
            close(fd_client);
            exit(0);
        }

        send(sockD, buffer, sizeof(char) * strlen(buffer), 0);
        memset(buffer, 0, 8192);

        recv(sockD, buffer, sizeof(buffer), 0);
        printf("server: %s\n", buffer);
        memset(buffer, 0, 8192);


        // close(fd_client);

    }

    return 0;
}

