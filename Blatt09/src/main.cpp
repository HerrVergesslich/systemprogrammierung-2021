#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <string.h>
#include <cerrno>
#include <iostream>
#include <stdlib.h>

#include "server.h"
#include "daemon.h"

using namespace std;

int PORT = -1;

int main(int argc, char** argv) {
    if(argc > 1) {
        PORT = atoi(argv[1]);
    } else {
        PORT = 8080;
    }
    DEBUG("ARGC: " << argc << " ARGV[2] '" << argv[2] << "'");
    if(argc > 2 && argv[2] == "startDaemon") {
        DEBUG("Daemon");
    }
        startDaemon();

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    int y = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &y, sizeof(int));

    sockaddr_in name;
    memset(&name, 0, sizeof(name)); //Bereich im Arbeitspeicher reservieren mit der Größe von einer sockaddr_in
    name.sin_family = AF_INET;
    name.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    name.sin_port = htons(PORT);

    bind(serverSocket, (const struct sockaddr * ) &name, sizeof(name));
    DEBUG("Server starts on " << inet_ntoa(name.sin_addr) << ":" << PORT);

    listen(serverSocket, 5); //Maximale Anzahl an gleichzeitigen Verbindungen in der Warteschlange

    int clientSocket;
    uint8 buffer[MAXBUF];
    int bytes = -1;
    for(;;) {
        DEBUG("Warte auf Verbindung...");
        clientSocket = accept(serverSocket, NULL, NULL);

        //server::EchoServer::handleRequest(clientSocket);
        //server::SimpleGET::handleRequest(clientSocket);
        //server::ReplyGET::handleRequest(clientSocket);
        //server::ServeFiles::handleRequest(clientSocket);
        server::ShowDirectories::handleRequest(clientSocket);
    }
    close(serverSocket);
    return 0;
}
