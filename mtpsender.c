#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "mtppacket.h"

int main(int argc, char** argv) {

    FILE* inputFile;
    FILE* logFile;
    
    if (argc < 5 || argc > 6) {
        fprintf(stderr, "There needs to be 5 to 6 parameters! Follow the format below:\n\
        ./mtpsender <receiver-IP> <receiver-port> <window-size>	<input-file> <sender-logfile>\n\
        If <sender-logfile> isn't provided, a file called mtpsender_logs.txt will be created in\
         the firectory this file is in.\n");
        
        return 0;
    }
    else {
        inputFile = fopen(argv[4], "r");
        logFile = fopen((argc == 6) ? argv[5] : "mtpsender_logs.txt", "w");
        fprintf(stderr, "%s%s", ((!inputFile) ? "Something wrong happened with the input file!\n" : ""), ((!logFile) ? "Something wrong happened with the log file!\n" : ""));

        if (!inputFile || !logFile) {
            closeImportantFiles(inputFile, logFile);
            return 0;
        }
    }

    //open up a UDP client socket
    int senderSocket;
    if ((senderSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        fprintf(stderr, "Socket couldn't be created!\n");
        return 0;
    }

    //sender needs to read the file
    //creates and sends DATA packets (type = 1) to a receiver
    //receives ACK packets from receiver

    closeImportantFiles(inputFile, logFile);
    return 1;
}

void closeImportantFiles(FILE* inputFile, FILE* logFile) {
    fclose(inputFile);
    fclose(logFile);
}

// do checksub checking in here
int isCorrupt() {
    return 0;
}
