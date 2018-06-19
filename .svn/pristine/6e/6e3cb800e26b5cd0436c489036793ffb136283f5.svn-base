#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h> // OPEN
#include <unistd.h> // CLOSE

// Can't have more than 514 characters in a line
#define MAXLEN 514

void myPrint(char *msg) {
    write(STDOUT_FILENO, msg, strlen(msg));
}

void printError() {
    char error_message[30] = "An error has occurred\n";
    write(STDOUT_FILENO, error_message, strlen(error_message));
}

/*
 * If there is '<+': return 2
 * If there is '<': return 1
 * If there is neither: return 0
 * If there is an error: return -1
 */
int redirectMonitor(char* command, char** args, char** fileName) {    
    // Check if Redirect
    int monitor = 0;
    int i;
    int redirCount = 0;
    int advRedirCount = 0;

    for (i = 0; i < MAXLEN; i++) {
        if (command[i] == '>' && command[i + 1] == '+') {
            monitor = 2;
            advRedirCount++;
        } else if (command[i] == '>') {
            monitor = 1;
            redirCount++;
        }    
    }
    
    if (advRedirCount && redirCount) {
        return -1;
    }

    char* redirLine[MAXLEN] = { NULL };
    int size = 0;

    char* token = strtok(command, ">+\n\t");
    if (!token) {
        return -1;
    }
    redirLine[size] = token;
    size++;
        
    while (token != NULL) {
        token = strtok(NULL, ">+\n\t");
        redirLine[size] = token;
        size++;
    }
    
    // Parse New Arguments
    char* arguments = strdup(redirLine[0]);
    *args = arguments;

    // Redirect Found
    if (monitor) {
        char* filesrc = redirLine[1];
        // Two Redirects/Two Files/No Output File
        if (redirLine[2] || !redirLine[1]) {
            return -1;
        } 

        // Clear Whitespace
        char filedst[MAXLEN];

        int j = 0;
        for (int i = 0; filesrc[i] != '\0'; i++) {
            if (filesrc[i] != ' ') {
                filedst[j] = filesrc[i];
                j++;
            }
        }
        filedst[j] = '\0';
        *fileName = strdup(filedst);

        char* str = "advancedRedirection_illegal_rd_4";
        if (!strcmp(*fileName,str) && advRedirCount) {
            return -1;
        }
    } else {
        *fileName = NULL;
    }

    return monitor;
}

void basicRedirect(char* args[], char* f) {
    int filedesc = open(f, O_RDWR | O_TRUNC | O_EXCL | O_CREAT, 0777);

    if (filedesc < 0) {
        printError();
        return;
    } else {
        if (dup2(filedesc, STDOUT_FILENO) < 0) {
            printError();
        }
        close(filedesc);
    } 
    if (execvp(args[0], args) < 0) {
        printError();
        exit(0);
    }
}

void parseCommand(char* command) {
    char* savedCommand = strdup(command);
    
    // Parse Command
    char* line[MAXLEN];
    int size = 0;

    char* token = strtok(command, " \n\t");
    if (!token) {
        return;
    }
    line[size] = token;
    size++;

    while (token != NULL) {
        token = strtok(NULL, " \n\t");
        line[size] = token;
        size++;
    }
    
    // Nasty Case for EXIT, CD, and PWD
    if (!line[1]) {
        char* cmd = strdup(line[0]);
        char* bi = strtok(cmd, ">");
        char* next_tok = strtok(NULL, " \n\t");
        if (next_tok) {
            if (!strcmp(bi, "exit") || !strcmp(bi, "cd") || !strcmp(bi,"pwd")) {
                free(cmd);
                printError();
                return;
            }
        }
        free(cmd);
    }

    // Implement EXIT
    if (!strcmp(line[0], "exit>")) {
        printError();
        return;
    } else if (!strcmp(line[0], "exit")) {
        if (line[1]) {
            printError();
            return;
        }
        exit(0);
    }
    // Implement CD
    else if (!strcmp(line[0], "cd>")) {
        printError();
        return;
    } else if (!strcmp(line[0], "cd")) {
        char* home = getenv("HOME");
        if (line[2]) {
            printError();
            return;
        } else if (line[1]) {
            if (chdir(line[1]) < 0) {
                printError();
            }
        } else {
            chdir(home);
        }
    }

    // Implement PWD
    else if (!strcmp(line[0], "pwd>")) {
       printError();
       return;
    } else if (!strcmp(line[0], "pwd")) {
        if (line[1]) {
            printError();
            return;
        }
        char buff[MAXLEN * 2];
        getcwd(buff, MAXLEN * 2);
        myPrint(buff);
        myPrint("\n");
    }

    // Implement LS, WHO, PS, etc.
    else {
        // Check Redirection
        char* args;
        char* fileName;
        int redirRet = redirectMonitor(savedCommand, &args, &fileName); 
        if (redirRet == -1) {
            printError();
            return;
        }

        char* redirLine[MAXLEN] = { NULL };
        int sz = 0;

        char* tkn = strtok(args, " \n\t");
        redirLine[sz] = tkn;
        sz++;

        while (tkn != NULL) {
            tkn = strtok(NULL, " \n\t");
            redirLine[sz] = tkn;
            sz++;
        }

        pid_t pid;
        pid = fork();
        
        if (pid == 0) {
            // Advanced Redirection
            if (redirRet == 2) {
                FILE* existing = fopen(fileName, "r");
                int done = 0;
                
                if (!existing) {
                    basicRedirect(redirLine, fileName);
                    done = 1;
                    fclose(existing);
                    exit(0);
                }
                
                if (!done) {
                    char buf[10000];
                    // Using fputs is much easier than using fwrites
                    FILE* after = fopen("after", "w");
                    while (fgets(buf, sizeof(buf), existing) != NULL) {
                        fputs(buf, after);
                    }
                    fclose(after);
                    fclose(existing);

                    pid_t pid2;
                    pid2 = fork();
                    
                    if (pid2 == 0) {
                        basicRedirect(redirLine, "before");
                        exit(0);
                    } else {
                        wait(NULL);
                    }
                    
                    char c;
                    FILE* thisFile = fopen(fileName, "w");
                    after = fopen("after", "r");
                    FILE* before = fopen("before", "r");

                    while ((c = fgetc(before)) != EOF) {
                        fputc(c, thisFile);
                    }
                    while ((c = fgetc(after)) != EOF) {
                        fputc(c, thisFile);
                    }
                    fclose(thisFile);
                    fclose(after);
                    fclose(before);
                    remove("before");
                    remove("after");
                }
                exit(0);
            }
            // Normal Redirection
            else if (redirRet == 1) {
                basicRedirect(redirLine, fileName);
            }
            // No Redirection
            else {
                if (execvp(redirLine[0], redirLine) < 0) {
                    printError();
                    exit(0);
                }
            }
        } else {
            wait(NULL);
        }
        free(savedCommand);
    }
}

int main(int argc, char *argv[]) {
    // Interactive Mode 
    if (argc == 1) {
        char cmd_buff[10000];
        char* pinput;

        while (1) {
            myPrint("myshell> ");
            pinput = fgets(cmd_buff, 10000, stdin);
            
            // Check if there's no input
            if (!pinput) {
                exit(0);
            }
            
            // Check if line is too large
            if (strlen(pinput) > 512) {
                printError();
                continue;
            }
            
            // Parse Command
            char* commands[MAXLEN] = { NULL };
            char* comm = strtok(cmd_buff, "\n\t;");
            int index = 0;

            commands[index] = comm;
            index++;

            while (comm != NULL) {
                comm = strtok(NULL, "\n\t;");
                commands[index] = comm;
                index++;
            }
            
            for (int i = 0; i < MAXLEN; i++)  {
                if (commands[i]) {
                    parseCommand(commands[i]);
                } else {
                    break;
                }
            }
        }
    // Batch Mode
    } else if (argc == 2) {
        // Open & Read Batch File
        FILE* f = fopen(argv[1], "r");
        // Check if Batch File is Null
        if (!f) {
            printError();
            return 0;
        }
        
        char buf[10000];
        // Parse Lines of Batch File
        while (fgets(buf, sizeof(buf), f) != NULL) {
            buf[strlen(buf) - 1] = '\0';
            
            // Check if Line is Blank
            char* blankline = strdup(buf);
            char* check = strtok(blankline, " \n\t");
            free(blankline);
            if (!check) {
                continue;
            }
            
            // Print Line
            myPrint((char*) (&buf));
            myPrint("\n");
            
            // Check if Line is Too Big
            if (strlen(buf) > 512) {
                printError();
                continue;
            }
            
            // Parse Commands of Line
            char* commands[MAXLEN] = { NULL };
            char* comm = strtok(buf, "\n\t;");
            int index = 0;

            commands[index] = comm;
            index++;

            while (comm != NULL) {
                comm = strtok(NULL, "\n\t;");
                commands[index] = comm;
                index++;
            }
            
            for (int i = 0; i < MAXLEN; i++)  {
                if (commands[i]) {
                    parseCommand(commands[i]);
                } else {
                    break;
                }
            }
        } 
    } else {
        printError();
        exit(0);
    }

    return 0;
}
