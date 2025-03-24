#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
    typedef int socklen_t;  // Fix for Windows
#else
    #include <arpa/inet.h>
    #include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int votes[3] = {0, 0, 0};

void update_web_interface() {
    char command[BUFFER_SIZE];
    snprintf(command, sizeof(command), 
             "curl -X POST -H \"Content-Type: application/json\" -d \"{\\\"A\\\": %d, \\\"B\\\": %d, \\\"C\\\": %d}\" http://127.0.0.1:5000/update_votes",
             votes[0], votes[1], votes[2]);
    system(command);
}

int main() {
    #ifdef _WIN32
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);
    #endif

    int server_fd, new_socket;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
        if (new_socket < 0) {
            perror("Accept failed");
            continue;
        }

        memset(buffer, 0, BUFFER_SIZE);
        recv(new_socket, buffer, BUFFER_SIZE, 0);
        printf("Received vote: %s\n", buffer);

        if (strcmp(buffer, "A") == 0) votes[0]++;
        else if (strcmp(buffer, "B") == 0) votes[1]++;
        else if (strcmp(buffer, "C") == 0) votes[2]++;

        update_web_interface();

        #ifdef _WIN32
            closesocket(new_socket);
        #else
            close(new_socket);
        #endif
    }

    #ifdef _WIN32
        WSACleanup();
    #endif

    return 0;
}
