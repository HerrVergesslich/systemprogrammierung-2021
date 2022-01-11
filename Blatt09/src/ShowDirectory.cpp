#include <sys/socket.h>
#include <sys/stat.h>
#include <syslog.h>
#include <dirent.h>
#include <pwd.h>
#include <unistd.h>
#include <cerrno>
#include <vector>

#include <cstring>
#include <iostream>
#include <fstream>

#include "server.h"

void server::ShowDirectories::handleRequest(int clientSocket, string workingDir) {
    uint8 buffer[MAXBUF];
    int bytes = -1;
    bool lastLineWasEmpty = false;
    string path = "";
    for(;;) {
        memset(buffer, 0, MAXBUF);
        bytes = recv(clientSocket, buffer, MAXBUF, 0);
        if(bytes <= 0) {
            close(clientSocket);
            break;
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
                    path = workingDir + (path[0] == '/' ? path : "/" + path);
                    LOG("Requested file: " + path);
                    if(checkIfDirectory(path)) {
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