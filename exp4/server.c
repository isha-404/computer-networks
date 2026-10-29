#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 11000

int main() {
    int sock;
    char buffer[1024];
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    // Create UDP socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    // Set server address
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    bind(sock, (struct sockaddr *)&server, sizeof(server));

    printf("UDP Server waiting...\n");

    while (1) {
        int n = recvfrom(sock, buffer, sizeof(buffer) - 1, 0,
                         (struct sockaddr *)&client, &len);

        buffer[n] = '\0';
        printf("Client: %s", buffer);

        sendto(sock, buffer, n, 0,
               (struct sockaddr *)&client, len);
    }

    close(sock);
    return 0;
}
