#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "123.123.123.87"  // Change to the server's IP address
#define SERVER_PORT 4444
#define SEQUENCE "\x13\x37"
#define SEQUENCE_LENGTH 2
#define WRONG_SEQUENCE "\x00\x00"
#define WRONG_SEQUENCE_LENGTH 2

// Function that sends the correct sequence
void send_correct_sequence(int sock) {
    if (send(sock, SEQUENCE, SEQUENCE_LENGTH, 0) == -1) {
        perror("send failed");
        close(sock);
        exit(EXIT_FAILURE);
    }
}

// Function that sends the wrong sequence
void send_wrong_sequence(int sock) {
    if (send(sock, WRONG_SEQUENCE, WRONG_SEQUENCE_LENGTH, 0) == -1) {
        perror("send failed");
        close(sock);
        exit(EXIT_FAILURE);
    }
}

// Function to create and connect the client socket
int create_client_socket(const char *server_ip, int port) {
    int sock;
    struct sockaddr_in server_addr;

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up the server address struct
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
        perror("Invalid address or address not supported");
        close(sock);
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    return sock;
}

// Function to receive data from the server
void receive_data(int sock) {
    char buffer[1024];
    ssize_t bytes_received;

    // Receive data from the server
    bytes_received = recv(sock, buffer, sizeof(buffer), 0);
    if (bytes_received == -1) {
        perror("recv failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    if (bytes_received > 0) {
        printf("Received data:\n");
        fwrite(buffer, 1, bytes_received, stdout);
        printf("\n");
    } else {
        printf("No data received or connection closed.\n");
    }
}

int main() {
    int sock;
    
    // Create client socket and connect to the server
    sock = create_client_socket(SERVER_IP, SERVER_PORT);

    // Test sending the correct sequence
    send_correct_sequence(sock);
    receive_data(sock);
    
    // Test sending the wrong sequence
    send_wrong_sequence(sock);
    receive_data(sock);

    send_wrong_sequence(sock);
    receive_data(sock);
    
    // Close the socket
    close(sock);

    return 0;
}

