#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "Usage " << argv[0] << " <port number> " << std::endl;
    }
    int port = atoi(argv[1]);

    // TODO: socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket < 0)
    {
        perror("Could not create a server socket");
        return 1;
    }

    // TODO: bind
    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    int bindVal = bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    if (bindVal < 0)
    {
        perror("Could not bind");
        return 1;
    }

    // TODO: listen
    int listenVal = listen(serverSocket, 5);
    if (listenVal < 0)
    {
        perror("Could not listen");
        return 1;
    }

    while (true)
    {

        // TODO: accept
        struct sockaddr_in clientAddress;
        socklen_t clientAddressLen = sizeof(clientAddress);
        int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLen);
        if (clientSocket < 0)
        {
            perror("Could not accept");
            continue;
        }

        std::string clientIP = inet_ntoa(clientAddress.sin_addr);
        int clientPort = ntohs(clientAddress.sin_port);

        std::cout << "Accepted new client @" << clientIP << ":" << clientPort << std::endl;

        // TODO: read/recv
        char buffer[1024] = {0};
        int bytsRecv = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytsRecv < 0)
        {
            perror("Could not reeive");
            return 1;
        }

        if (bytsRecv == 0)
        {
            std::cout << "Client at " << clientIP << ":" << clientPort << " has disconnected" << std::endl;
        }

        std::cout << "Client message: " << buffer << std::endl;

        // TODO: write
        std::string res = "Server received message from client at " + clientIP + ":" + std::to_string(clientPort);
        int bytesSent = send(clientSocket, res.c_str(), res.length(), 0);
        if (bytesSent < 0)
        {
            perror("Could not send");
            return 1;
        }
    }

    // TODO: close
    close(serverSocket);

    return 0;
}