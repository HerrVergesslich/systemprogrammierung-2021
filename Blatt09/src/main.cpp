#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <syslog.h>
#include <signal.h>
#include <fcntl.h>
#include <iostream>
#include <csignal>
#include <cstring>
#include <cerrno>

#include "server.h"

using namespace std;

void startDaemon(int port, string workingDir){
    pid_t p1 = fork();
    openlog("Temperatur-Daemon", LOG_PID, LOG_USER | LOG_INFO);
    int priority = LOG_USER | LOG_INFO;
    
    switch(p1) {
        case -1:{
            exit(EXIT_FAILURE);    
            break;
        }
        case (pid_t)0:{
            signal(SIGINT, SIG_IGN);
            signal(SIGTERM, SIG_IGN);
            signal(SIGWINCH, SIG_IGN);
            signal(SIGHUP, SIG_IGN);
            setsid();
            pid_t p2 = fork();
            switch(p2) {
                  case -1:{
                    syslog(LOG_USER | LOG_ERR, "Failed starting deamon");
                    exit(EXIT_FAILURE);
                    break;
                }
                case (pid_t)0:{
                    syslog(priority, "Deamon started successfully.");
                    umask(0); //DateiModus-Maske/Berechtigungs-Maske zurücksetzen
                    chdir("/daemon"); //neues Arbeitsverzeichnis erstellen und wechseln
                    for(int i = 0;i < sysconf(_SC_OPEN_MAX);i++){close(i);}//Schließen aller geerbten Filedeskriptoren
                    
                    //Umlenken der Standard-Input-Output-Kanäle (0,1,2)
                    open("/dev/null", O_RDWR);
                    dup2(STDIN_FILENO, STDOUT_FILENO);
                    dup2(STDIN_FILENO, STDERR_FILENO);

                    startServer(8080, workingDir);
                }
                default:{
                    exit(EXIT_SUCCESS);
                }
            }    
        }
        default:{
            exit(EXIT_SUCCESS);
        }
    
    }
}

void mySignalHandler(int sig) {
    if(sig == SIGHUP) {
        syslog(LOG_USER | LOG_INFO, "Received SIGHUP: AD: '%s' AC: %d", "/wpfuibdf", 1234); 
    } else if(sig == SIGTERM) {
        syslog(LOG_USER | LOG_INFO, "Received SIGTERM. Exiting...");
        exit(EXIT_SUCCESS);
    } else {
        syslog(LOG_USER | LOG_INFO, "Received other signal: %d", sig);
    }
}

int main(int argc, char* argv[]) {
    int port = -1;
    string www_path;

    if(argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <www-path> <port> [daemon]" << std::endl;
        return EXIT_FAILURE;
    }
    www_path = argv[1];

    if(argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <www-path> <port> [daemon]" << std::endl;
        return EXIT_FAILURE; 
    }
    port = atoi(argv[2]);

    if(argc >= 4) {
        startDaemon(port, www_path);
    } else {
        startServer(port, www_path);
    }
    return 0;
}