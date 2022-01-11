#include <sys/socket.h>
#include <unistd.h>
#include <cerrno>
#include <vector>

#include <cstring>
#include <iostream>

#include "server.h"

using namespace std;

void server::ReplyGET::handleRequest(int clientSocket) {
    uint8 buffer[MAXBUF];
    int bytes = -1;
    bool lastLineWasEmpty = false;
    string path = "";
    for(;;) {
        memset(buffer, 0, MAXBUF); //Bereich im Arbeitspeicher reservieren mit Größe MAXBUF
        bytes = recv(clientSocket, buffer, MAXBUF, 0); //Lese MAXBUF bytes + speicher wie viele Bytes gelesen wurden in readBytes
        if(bytes <= 0) {
            close(clientSocket);
            break; //Kommunikationsschleife verlassen
        }
        string req = string("") + buffer;
        if(req.substr(0, 2) != "\r\n") {
            lastLineWasEmpty = false;
            if(req.substr(0, 4) == "GET ") {
                int indexEnd = 0;
                for(int i = 0; i < req.length(); i ++) {
                    if(req[i] == ' ') {
                        indexEnd = ++i;
                    }
                }
                if(indexEnd == req.length()) {
                    close(clientSocket);
                    return;
                }
                int protVers = req.find("HTTP/1.1\r\n");
                if(protVers != string::npos) {
                    path = req.substr(4, protVers-4);
                }
                if(req.substr(req.length() - 4) == "\r\n\r\n") {
                    server::counter ++;
                    string response = genHeader("200 OK", path.length(), "text/plain") + path;
                    send(clientSocket, response.c_str(), response.length(), 0);
                    close(clientSocket);
                }
            } else {
                //OTHER HEADER
            }
        } else {
            if(lastLineWasEmpty) {
                string response = genHeader("200 OK", path.length(), "text/plain") + path;
                send(clientSocket, response.c_str(), response.length(), 0);
                close(clientSocket);
                break;
            } else {
                lastLineWasEmpty = true;
            }
        }
        
    }
}

string server::ReplyGET::genHeader(string status, int length, string type) {
    string header = HTTP_HEADER;
    header.replace(header.find("%RESPONSE_CODE%"), string("%RESPONSE_CODE%").length(), status);
    header.replace(header.find("%CONTENT_LENGTH%"), string("%CONTENT_LENGTH%").length(), to_string(length));
    header.replace(header.find("%CONTENT_TYPE%"), string("%CONTENT_TYPE%").length(), "" + type);
    return header;
} 