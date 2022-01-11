#include <sys/socket.h>
#include <unistd.h>
#include <cerrno>
#include <vector>
#include <syslog.h>

#include <cstring>
#include <iostream>
#include <fstream>

#include "server.h"

using namespace std;

void server::ServeFiles::handleRequest(int clientSocket, string workingDir) {
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
        std::vector<string> reqv;
        if(req.substr(0, 2) != "\r\n") {
            lastLineWasEmpty = false;
            reqv.clear();
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
                    path = req.substr(4, protVers-5);
                }
                if(req.substr(req.length() - 4) == "\r\n\r\n") {
                    if(path.find("../") != string::npos) {
                        path.replace(path.find("../"), 3, "/");
                    }
                    server::counter ++;
                    int fileLength = 0;
                    uint8* fileContent = readFile(workingDir + path, &fileLength);       
                    LOG("Requested file: " + workingDir + path);
                    if(fileContent == nullptr) {
                        string response = ReplyGET::genHeader("404 Not Found", 13, "text/plain");
                        send(clientSocket, response.c_str(), response.length(), 0);
                        send(clientSocket, string("404 Not Found").c_str(), 13, 0);
                    } else {
                        string response = ReplyGET::genHeader("200 OK", fileLength, getMimeType(path));
                        send(clientSocket, response.c_str(), response.length(), 0);
                        send(clientSocket, fileContent, fileLength, 0);
                    }
                    close(clientSocket);
                    delete fileContent;
                }
            } else {
                //OTHER HEADER
            }
        } else {
            if(lastLineWasEmpty) {
                string response = ReplyGET::genHeader("200 OK", path.length(), "text/plain") + path;
                send(clientSocket, response.c_str(), response.length(), 0);
                close(clientSocket);
                break;
            } else {
                lastLineWasEmpty = true;
            }
        }
        
    }
}

uint8* server::ServeFiles::readFile(string path, int* fileLength) {
    std::ifstream is (path, std::ifstream::binary);
    if(is) {
        is.seekg(0, is.end); //Jump to end in stream
        int length = is.tellg(); //Get current position in stream
        is.seekg(0, is.beg); //Jump to beginning in stream
        uint8* buffer = new uint8[length];
        is.read(buffer, length);
        is.close();
        *fileLength = length;
        return buffer;
    } else {
        return nullptr;
    }
}

string server::ServeFiles::getMimeType(string path) {
    string fextension = "";
    for(int i = path.length() - 1; i >= 0; i --) {
        if(path[i] == '.') {
            fextension = path.substr(++i);
            break;
        }
    }
    if(fextension == "html") return "text/html";
    if(fextension == "txt" || fextension == "c" || fextension == "h" || fextension == "c++" || fextension == "cpp") return "text/plain";
    if(fextension == "pdf") return "application/pdf";
    if(fextension == "png") return "image/png";
    if(fextension == "jpg" || fextension == "jpeg") return "image/jpeg";
    if(fextension == "css") return "text/css";
    return "application/octet-stream";
}