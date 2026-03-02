#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include <string>
#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        std::cout << "Usage " << argv[0] << "<hostname> <port number> " << std::endl;
    }
    int port = atoi(argv[2]);

    // TODO: socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    struct hostent *server = gethostbyname(argv[1]);
    if (server == NULL)
    {
        perror("No such host");
        return 1;
    }

    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // TODO: connect
    int connectVal = connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    if (connectVal < 0)
    {
        perror("Connection failed");
        return 1;
    }

    // TODO: send/recv
    std::string message = "Hello server!";
    int bytesSend = send(clientSocket, message.c_str(), message.length(), 0);
    if (bytesSend < 0)
    {
        perror("Could not send");
        return 1;
    }

    // TODO: close
    close(clientSocket);

    return 0;
}