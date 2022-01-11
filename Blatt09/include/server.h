#ifndef SERVER_H
#define SERVER_H

#define MAXBUF 1024

typedef char uint8;

#define HTTP_HEADER "HTTP/1.1 %RESPONSE_CODE%\r\nConnection: close\r\nContent-Length: %CONTENT_LENGTH%\r\nContent-Language: de\r\nContent-Type: %CONTENT_TYPE%\r\n\r\n"
#define INDEX_TABLE_ROW "<tr><td>%PERMISSIONS%</td><td>%LINKS%</td><td>%OWNER%</td><td>%SIZE%</td><td>%LAST_CHANGE%</td><td><a href=\"./%FILE_NAME%\">%FILE_NAME%</a></td></tr>"
#define INDEX_TABLE "<!DOCTYPE html>\r\n<html>\r\n<header>\r\n<title>TEST</title>\r\n<meta charset=\"utf-8\">\r\n</header>\r\n<body>\r\n<h2>Index of %DIR_NAME%</h2>\r\n<hr>\r\n<table>\r\n<thead>\r\n<tr>\r\n<th>Berechtigung</th>\r\n<th>Link Count</th>\r\n<th>Besitzer</th>\r\n<th>Größe (byte)</th>\r\n<th>Letze Änderung</th>\r\n<th>Dateiname</th>\r\n</tr>\r\n</thead>\r\n<tbody>\r\n<tr><td>-</td><td>-</td><td>-</td><td>-</td><td>-</td><td><a href=\"../\">../</a></td></tr>\r\n%ROWS%\r\n</tbody>\r\n</table>\r\n</body>\r\n</html>"

#define LOG(x) syslog(LOG_USER | LOG_INFO, string(x).c_str())

using namespace std;

void startServer(int port, std::string workingDir);

namespace server {
    
    static long counter = 0;

    class EchoServer {
        public:
            static void handleRequest(int clientSocket);
    };

    class SimpleGET {
        public:
            static void handleRequest(int clientSocket);
    };

    class ReplyGET {
        public:
            static void handleRequest(int clientSocket);
            static std::string genHeader(std::string status, int length, std::string type);
    };

    class ServeFiles {
        public:
            static void handleRequest(int clientSocket, string workingDir);
            static uint8* readFile(std::string path, int* length);
            static std::string getMimeType(std::string path);
    };

    class ShowDirectories {
        public:
            static void handleRequest(int clientSocket, string workingDir);
            static std::string getDirectoryInfo(std::string path);
            static bool checkIfDirectory(std::string path);
            static std::string getPermissionString(mode_t mode);
    };

}

#endif