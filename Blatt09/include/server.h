#ifndef SERVER_H
#define SERVER_H

#define DEBUG(x) std::cout << "DEBUG: " << x << std::endl
#define PANIC(msg) {perror(msg); abort();}
#define MAXBUF 1024

typedef char uint8;

#define HTTP_HEADER "HTTP/1.1 %RESPONSE_CODE%\r\nConnection: close\r\nContent-Length: %CONTENT_LENGTH%\r\nContent-Language: de\r\nContent-Type: %CONTENT_TYPE%\r\n\r\n"
#define INDEX_TABLE_ROW "<tr><td>%PERMISSIONS%</td><td>%LINKS%</td><td>%OWNER%</td><td>%SIZE%</td><td>%LAST_CHANGE%</td><td><a href=\"./%FILE_NAME%\">%FILE_NAME%</a></td></tr>"
#define INDEX_TABLE "<html>\
    <header>\
        <title>TEST</title>\
        <meta charset=\"utf-8\">\
    </header>\
    <body>\
        <h2>Index of %DIR_NAME%</h2>\
        <hr>\
        <table>\
            <thead>\
                <tr>\
                    <th>Berechtigung</th>\
                    <th>Link Count</th>\
                    <th>Besitzer</th>\
                    <th>Größe (byte)</th>\
                    <th>Letze Änderung</th>\
                    <th>Dateiname</th>\
                </tr>\
            </thead>\
            <tbody>\
                %ROWS%\
            </tbody>\
        </table>\
    </body>\
</html>"

namespace server {
    
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
            static void handleRequest(int clientSocket);
            static uint8* readFile(std::string path, int* length);
            static std::string getMimeType(std::string path);
    };

    class ShowDirectories {
        public:
            static void handleRequest(int clientSocket);
            static std::string getDirectoryInfo(std::string path);
            static bool checkIfDirectory(std::string path);
            static std::string getPermissionString(mode_t mode);
    };

}

#endif