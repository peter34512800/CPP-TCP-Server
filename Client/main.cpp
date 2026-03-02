#include <iostream>
#include <string>
#include <cstring>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#endif

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        std::cout << "Usage " << argv[0] << "<hostname> <port number> " << std::endl;
    }

#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

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
#ifdef _WIN32
    closesocket(clientSocket);
    WSACleanup();
#else
    close(clientSocket);
#endif

    return 0;
}