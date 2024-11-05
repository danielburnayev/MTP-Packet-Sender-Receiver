#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "mtppacket.h"

#define MAX_ERROR_LENGTH 300

void closeImportantFiles(FILE* inputFile, FILE* logFile);
int endWithErrorMessage(int messageParts, ...);
int isCorrupt();

int main(int argc, char** argv) {

    FILE* inputFile;
    FILE* logFile;
    
    if (argc < 5 || argc > 6) {
        return endWithErrorMessage(1, "There needs to be 5 to 6 parameters! Follow the format below:\n\
./mtpsender <receiver-IP> <receiver-port> <window-size>	<input-file> <sender-logfile>\n\
If <sender-logfile> isn't provided, a file called mtpsender_logs.txt will be created in\
the directory this file is in.\n");
    }
    else {
        inputFile = fopen(argv[4], "r");
        logFile = fopen((argc == 6) ? argv[5] : "mtpsender_logs.txt", "w");

        if (!inputFile || !logFile) {
            closeImportantFiles(inputFile, logFile);
            return endWithErrorMessage(2, 
                        ((!inputFile) ? "Cannot find the input file!\n" : ""), 
                        ((!logFile) ? "Cannot find the log file!\n" : ""));
        }
    }

    //opens up a UDP client socket (NEED TO WORK ON THIS)
    int senderSocket;
    if ((senderSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        return endWithErrorMessage(1, "Socket couldn't be created!\n");
    }

    //sender needs to read the file
    char* theMessage = (char*)malloc(sizeof(char) * (MAX_DATA_LENGTH));
    char* messageBuffer = (char*)malloc(sizeof(char) * (MAX_DATA_LENGTH));
    size_t currMessageLen = strlen(theMessage);
    int limit = MAX_DATA_LENGTH - currMessageLen;

    while (!feof(inputFile)) {
        //in case any /n's end fgets early
        while (currMessageLen < MAX_DATA_LENGTH - 1 && !feof(inputFile)) {
            fgets(messageBuffer, limit, inputFile);
            strcat(theMessage, messageBuffer);
            currMessageLen = strlen(theMessage);
            limit = MAX_DATA_LENGTH - currMessageLen;
        }

        if (ferror(inputFile)) {
            return endWithErrorMessage(1, "Something is wrong with the input file!\n");
        }

        free(theMessage);
        free(messageBuffer);
        messageBuffer = (char*)malloc(sizeof(char) * (MAX_DATA_LENGTH));
        theMessage = (char*)malloc(sizeof(char) * (MAX_DATA_LENGTH));
        currMessageLen = strlen(theMessage);
        limit = MAX_DATA_LENGTH - currMessageLen;
    }
    free(theMessage);
    free(messageBuffer);

    //creates and sends DATA packets (type = 1) to a receiver
    //receives ACK packets from receiver

    //close the files
    closeImportantFiles(inputFile, logFile);
    return 1;
}

void closeImportantFiles(FILE* inputFile, FILE* logFile) {
    fclose(inputFile);
    fclose(logFile);
}

int endWithErrorMessage(int messageParts, ...) {
    va_list messageList;
    va_start(messageList, messageParts);

    char* errorMessage = (char*)malloc(sizeof(char) * (MAX_ERROR_LENGTH + 1));
    int counter;
    for (counter = 0; counter < messageParts; counter++) {
        strcat(errorMessage, va_arg(messageList, const char*));
    }
    
    fprintf(stderr, "%s", errorMessage);
    return 0;
}

// do checksub checking in here
int isCorrupt() {
    return 0;
}