#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <syslog.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void startDaemon(){
        
    pid_t p1 = fork();
    openlog("SERVER-DAEMON",LOG_PID,LOG_USER);
    setlogmask(LOG_INFO);
    int priority = LOG_USER | LOG_INFO;
    
    switch(p1) {
        case -1:{
            syslog(priority,"failed forking");
            exit(EXIT_FAILURE);    
            break;
        }
        case (pid_t)0:{
            syslog(priority,"first fork succeeded with id: "+p1);
            setsid();
            pid_t p2 = fork();
            switch(p2) {
                  case -1:{
                    syslog(priority,"failed forking");
                    exit(EXIT_FAILURE);
                    break;
                }
                case (pid_t)0:{
                    syslog(priority,"second fork succeeded with id: " + p2);
                    umask(0); //DateiModus-Maske/Berechtigungs-Maske zurücksetzen
                    chdir("/daemon"); //neues Arbeitsverzeichnis erstellen und wechseln
                    for(int i = 0;i < sysconf(_SC_OPEN_MAX);i++){close(i);}//Schließen aller geerbten Filedeskriptoren
                    
                    //Umlenken der Standard-Input-Output-Kanäle (0,1,2)
                    open("/dev/null", O_RDWR);
                    dup2(STDIN_FILENO, STDOUT_FILENO);
                    dup2(STDIN_FILENO, STDERR_FILENO);

                    //Rücksprung in main()
                }
                default:{
                    syslog(priority,"closed second parent process with id: "+p2);
                    exit(EXIT_SUCCESS);
                }
            }    
        }
        default:{
            syslog(priority,"closed first parent process with id: "+p1);
            exit(EXIT_SUCCESS);
        }
    
    }
}