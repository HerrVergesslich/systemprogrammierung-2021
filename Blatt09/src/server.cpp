#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <syslog.h>

#include "server.h"

using namespace std;

void startServer(int port, string workingDir) {

    std::cout << getpid() << std::endl;
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    int y = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &y, sizeof(int));

    sockaddr_in name;
    memset(&name, 0, sizeof(name)); //Bereich im Arbeitspeicher reservieren mit der Größe von einer sockaddr_in
    name.sin_family = AF_INET;
    name.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    name.sin_port = htons(port);

    bind(serverSocket, (const struct sockaddr * ) &name, sizeof(name));
    LOG("Server starts on " + string(inet_ntoa(name.sin_addr)) + ":" + to_string(port));

    listen(serverSocket, 5); //Maximale Anzahl an gleichzeitigen Verbindungen in der Warteschlange

    int clientSocket;
    uint8 buffer[MAXBUF];
    int bytes = -1;
    for(;;) {
        clientSocket = accept(serverSocket, NULL, NULL);
        //server::EchoServer::handleRequest(clientSocket);
        //server::SimpleGET::handleRequest(clientSocket);
        //server::ReplyGET::handleRequest(clientSocket);
        //server::ServeFiles::handleRequest(clientSocket);
        server::ShowDirectories::handleRequest(clientSocket, workingDir);
    }
    close(serverSocket);
}