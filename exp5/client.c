#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 11000

int main() {
    int sock;
    char buffer[1024];
    struct sockaddr_in server;
    socklen_t len = sizeof(server);

    // Create UDP socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    // Set server address
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    while (1) {
        printf("Enter message: ");
        fgets(buffer, sizeof(buffer), stdin);

        sendto(sock, buffer, strlen(buffer), 0,
               (struct sockaddr *)&server, len);

        int n = recvfrom(sock, buffer, sizeof(buffer) - 1, 0,
                         NULL, NULL);

        buffer[n] = '\0';
        printf("Echo from server: %s", buffer);
    }

    close(sock);
    return 0;
}
