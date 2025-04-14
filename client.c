#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "correction.h"

#define PORT 8080

int main() {
    load_dictionary("dictionary.txt");

    int sock;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE], corrected[BUFFER_SIZE];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    while (1) {
        printf("You: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        correct_message(buffer, corrected);
        send(sock, corrected, strlen(corrected), 0);
        if (strncmp(buffer, "exit", 4) == 0) break;

        memset(buffer, 0, BUFFER_SIZE);
        read(sock, buffer, BUFFER_SIZE);
        printf("Server: %s\n", buffer);
    }

    close(sock);
    return 0;
}

