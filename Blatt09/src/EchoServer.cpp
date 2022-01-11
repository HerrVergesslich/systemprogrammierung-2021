#include <sys/socket.h>
#include <unistd.h>
#include <cerrno>

#include <cstring>
#include <iostream>

#include "server.h"

using namespace std;

void server::EchoServer::handleRequest(int clientSocket) {
    uint8 buffer[MAXBUF];
    int bytes = -1;
    for(;;) { //Eingehende Nachrichten lesen
        memset(buffer, 0, MAXBUF); //Bereich im Arbeitspeicher reservieren mit Größe MAXBUF
        bytes = recv(clientSocket, buffer, MAXBUF, 0); //Lese MAXBUF bytes + speicher wie viele Bytes gelesen wurden in readBytes
        if(bytes <= 0) {
            close(clientSocket);
            break; //Kommunikationsschleife verlassen
        }
        bytes = send(clientSocket, buffer, bytes, 0);
    }
}