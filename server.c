
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "correction.h"

#define PORT 8080

int main() {
    load_dictionary("dictionary.txt");

    int server_fd, client_sock;
    struct sockaddr_in addr;
    char buffer[BUFFER_SIZE], corrected[BUFFER_SIZE];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);
    bind(server_fd, (struct sockaddr *)&addr, sizeof(addr));
    listen(server_fd, 1);

    printf("Waiting for client...\n");
    socklen_t addrlen = sizeof(addr);
    client_sock = accept(server_fd, (struct sockaddr *)&addr, &addrlen);
    printf("Client connected.\n");

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        read(client_sock, buffer, BUFFER_SIZE);
        if (strncmp(buffer, "exit", 4) == 0) break;

        printf("Client: %s\n", buffer);

        printf("You: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        correct_message(buffer, corrected);
        send(client_sock, corrected, strlen(corrected), 0);
    }

    close(client_sock);
    close(server_fd);
    return 0;
}
