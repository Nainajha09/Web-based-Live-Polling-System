#ifdef _WIN32
    #define _WIN32_WINNT 0x0600  // Ensure Windows 7+ compatibility
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")  // Link Windows Sockets library
#else
    #include <arpa/inet.h>
    #include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define BUFFER_SIZE 1024

#ifdef _WIN32
int inet_pton(int af, const char *src, void *dst) {
    struct sockaddr_in sa;
    int result = WSAStringToAddressA((LPSTR)src, af, NULL, (struct sockaddr*)&sa, (int[]){sizeof(sa)});
    if (result != 0) return -1;
    memcpy(dst, &sa.sin_addr, sizeof(sa.sin_addr));
    return 1;
}
#endif

int main() {
    #ifdef _WIN32
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            perror("WSAStartup failed");
            exit(EXIT_FAILURE);
        }
    #endif

    int sock;
    struct sockaddr_in server_addr;
    char vote[BUFFER_SIZE];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    printf("Enter your vote (A, B, or C): ");
    fgets(vote, BUFFER_SIZE, stdin);
    vote[strcspn(vote, "\n")] = 0;

    send(sock, vote, strlen(vote), 0);
    printf("Vote sent!\n");

    #ifdef _WIN32
        closesocket(sock);
        WSACleanup();
    #else
        close(sock);
    #endif

    return 0;
}
