#include <sys/socket.h>
#include <sys/stat.h>
#include <pwd.h>
#include <unistd.h>

#include <cstring>
#include <cerrno>
#include <iostream>
#include <fstream>
#include <vector>
#include <dirent.h>
#include <chrono>

#include "server.h"

using namespace std;

void server::EchoServer::handleRequest(int clientSocket) {
    uint8 buffer[MAXBUF];
    int bytes = -1;
    for(;;) { //Eingehende Nachrichten lesen
        memset(buffer, 0, MAXBUF); //Bereich im Arbeitspeicher reservieren mit Größe MAXBUF
        bytes = recv(clientSocket, buffer, MAXBUF, 0); //Lese MAXBUF bytes + speicher wie viele Bytes gelesen wurden in readBytes
        DEBUG("" << bytes << " bytes empfangen");
        if(bytes <= 0) {
            DEBUG("Server: read " << bytes << " bytes -> ERROR: " << errno);
            close(clientSocket);
            break; //Kommunikationsschleife verlassen
        }
        bytes = send(clientSocket, buffer, bytes, 0);
    }
}

void server::SimpleGET::handleRequest(int clientSocket) {
    uint8 buffer[MAXBUF];
    int bytes = -1;
    bool lastLineWasEmpty = false;
    string path = "";

    for(;;) {
        memset(buffer, 0, MAXBUF); //Bereich im Arbeitspeicher reservieren mit Größe MAXBUF
        bytes = recv(clientSocket, buffer, MAXBUF, 0); //Lese MAXBUF bytes + speicher wie viele Bytes gelesen wurden in readBytes
        DEBUG("" << bytes << " bytes empfangen");
        if(bytes <= 0) {
            DEBUG("Server: read " << bytes << " bytes -> ERROR: " << errno);
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
                    DEBUG("INVALID REQUEST: " << req);
                    close(clientSocket);
                    return;
                }
                int protVers = req.find("HTTP/1.1\r\n");
                if(protVers != string::npos) {
                    path = req.substr(4, protVers-4);
                }
                if(req.substr(req.length() - 4) == "\r\n\r\n") {
                    send(clientSocket, path.c_str(), path.length(), 0);
                    close(clientSocket);
                }
            } else {
                //OTHER HEADER
            }
        } else {
            if(lastLineWasEmpty) {
                send(clientSocket, path.c_str(), path.length(), 0);
                close(clientSocket);
                break;
            } else {
                lastLineWasEmpty = true;
            }
        }
        
    }
}

void server::ReplyGET::handleRequest(int clientSocket) {
    uint8 buffer[MAXBUF];
    int bytes = -1;
    bool lastLineWasEmpty = false;
    string path = "";
    for(;;) {
        memset(buffer, 0, MAXBUF); //Bereich im Arbeitspeicher reservieren mit Größe MAXBUF
        bytes = recv(clientSocket, buffer, MAXBUF, 0); //Lese MAXBUF bytes + speicher wie viele Bytes gelesen wurden in readBytes
        DEBUG("" << bytes << " bytes empfangen");
        if(bytes <= 0) {
            DEBUG("Server: read " << bytes << " bytes -> ERROR: " << errno);
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
                    DEBUG("INVALID REQUEST: " << req);
                    close(clientSocket);
                    return;
                }
                int protVers = req.find("HTTP/1.1\r\n");
                if(protVers != string::npos) {
                    path = req.substr(4, protVers-4);
                }
                if(req.substr(req.length() - 4) == "\r\n\r\n") {
                    string response = genHeader("200 OK", path.length(), "text/plain") + path;
                    DEBUG("Response: '" << response << "'");
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

void server::ServeFiles::handleRequest(int clientSocket) {
    uint8 buffer[MAXBUF];
    int bytes = -1;
    bool lastLineWasEmpty = false;
    string path = "";
    for(;;) {
        memset(buffer, 0, MAXBUF); //Bereich im Arbeitspeicher reservieren mit Größe MAXBUF
        bytes = recv(clientSocket, buffer, MAXBUF, 0); //Lese MAXBUF bytes + speicher wie viele Bytes gelesen wurden in readBytes
        DEBUG("" << bytes << " bytes empfangen");
        if(bytes <= 0) {
            DEBUG("Server: read " << bytes << " bytes -> ERROR: " << errno);
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
                    DEBUG("INVALID REQUEST: " << req);
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

                    int fileLength = 0;
                    uint8* fileContent = readFile("www-path" + path, &fileLength);
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


void server::ShowDirectories::handleRequest(int clientSocket) {
    uint8 buffer[MAXBUF];
    int bytes = -1;
    bool lastLineWasEmpty = false;
    string path = "";
    for(;;) {
        memset(buffer, 0, MAXBUF); //Bereich im Arbeitspeicher reservieren mit Größe MAXBUF
        bytes = recv(clientSocket, buffer, MAXBUF, 0); //Lese MAXBUF bytes + speicher wie viele Bytes gelesen wurden in readBytes
        DEBUG("" << bytes << " bytes empfangen");
        if(bytes <= 0) {
            DEBUG("Server: read " << bytes << " bytes -> ERROR: " << errno);
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
                    DEBUG("INVALID REQUEST: " << req);
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

                    int fileLength = 0;

                    path = "www-path" + (path[0] == '/' ? path : "/" + path);
                    if(checkIfDirectory(path)) {
                        DEBUG("Directory");
                        string dirInfo = getDirectoryInfo(path);
                        string response = ReplyGET::genHeader("200 OK", dirInfo.length(), "text/html");
                        send(clientSocket, response.c_str(), response.length(), 0);
                        send(clientSocket, dirInfo.c_str(), dirInfo.length(), 0);
                    } else {
                        uint8* fileContent = ServeFiles::readFile(path, &fileLength);
                        if(fileContent == nullptr) {
                            string response = ReplyGET::genHeader("404 Not Found", 13, "text/plain");
                            send(clientSocket, response.c_str(), response.length(), 0);
                            send(clientSocket, string("404 Not Found").c_str(), 13, 0);
                        } else {
                            string response = ReplyGET::genHeader("200 OK", fileLength, ServeFiles::getMimeType(path));
                            send(clientSocket, response.c_str(), response.length(), 0);
                            send(clientSocket, fileContent, fileLength, 0);
                        }
                        close(clientSocket);
                        delete fileContent;
                    }                    
                }
            } else {
                //OTHER HEADER
            }
        } else {
            if(lastLineWasEmpty) {
                string response = server::ReplyGET::genHeader("200 OK", path.length(), "text/plain") + path;
                send(clientSocket, response.c_str(), response.length(), 0);
                close(clientSocket);
                break;
            } else {
                lastLineWasEmpty = true;
            }
        }
        
    }
}

bool server::ShowDirectories::checkIfDirectory(string path) {
    struct stat statBuf;
    if(stat(path.c_str(), &statBuf) == 0) {
        return ((statBuf.st_mode & S_IFDIR) == S_IFDIR);
    } else {
        return false;
    }
    
}

string server::ShowDirectories::getDirectoryInfo(string path) {
    string rows = "";
    DIR* dir = opendir(path.c_str());
    struct dirent *ent;
    if(dir != NULL) {
        bool first = true;
        while((ent = readdir(dir)) != NULL) {
            string row = string(INDEX_TABLE_ROW);
            struct stat statBuf;
            if(stat((path + "/" + ent->d_name).c_str(), &statBuf) == 0) {
                if(ent->d_name == ".." || ent->d_name == ".") continue;

                char timeBuf[80];
                struct tm ts;
                ts = *localtime(&statBuf.st_atim.tv_sec);
                strftime(timeBuf, sizeof(timeBuf), "%a %Y-%m-%d %H:%M:%S %Z", &ts);
                struct passwd* pw = getpwuid(statBuf.st_uid);
                row.replace(row.find("%PERMISSIONS%"), 13, getPermissionString(statBuf.st_mode));
                row.replace(row.find("%LINKS%"), 7, to_string(statBuf.st_nlink));
                row.replace(row.find("%OWNER%"), 7, pw->pw_name);
                row.replace(row.find("%SIZE%"), 6, to_string(statBuf.st_size));
                row.replace(row.find("%LAST_CHANGE%"), 13, timeBuf);
                row.replace(row.find("%FILE_NAME%"), 11, ent->d_name);
                row.replace(row.find("%FILE_NAME%"), 11, ent->d_name);
                rows += (first ? "\r\n" : "") + row;
                first = false;
            }
        }
    } else {
        return "-";
    }
    string page (INDEX_TABLE);
    page.replace(page.find("%DIR_NAME%"), 10, path.substr(8));
    page.replace(page.find("%ROWS%"), 6, rows);
    closedir(dir);
    return page;
}

string server::ShowDirectories::getPermissionString(mode_t mode) {
    string ret = "";
    if((mode & S_IFDIR) == S_IFDIR) ret += "d";
    else ret += "-";

    //Owner Permissions

    if((mode & S_IRUSR) == S_IRUSR) ret += "r";
    else ret += "-";
    if((mode & S_IWUSR) == S_IWUSR) ret += "w";
    else ret += "-";
    if((mode & S_IXUSR) == S_IXUSR) ret += "x";
    else ret += "-";

    //Group Permissions

    if((mode & S_IRGRP) == S_IRGRP) ret += "r";
    else ret += "-";
    if((mode & S_IWGRP) == S_IWGRP) ret += "w";
    else ret += "-";
    if((mode & S_IXGRP) == S_IXGRP) ret += "x";
    else ret += "-";

    //Guest Permissions

    if((mode & S_IROTH) == S_IROTH) ret += "r";
    else ret += "-";
    if((mode & S_IWOTH) == S_IWOTH) ret += "w";
    else ret += "-";
    if((mode & S_IXOTH) == S_IXOTH) ret += "x";
    else ret += "-";
    return ret;
}