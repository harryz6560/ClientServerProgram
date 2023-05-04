#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>

#define MAX_LINE_LENGTH 100
bool notified = false;
char command[MAX_LINE_LENGTH];

void *processCommands(){
	// now get the commands until the process stops
    	while(!notified){
	    printf("User command: ");
	    fgets(command, MAX_LINE_LENGTH, stdin);
	    command[strcspn(command, "\n")] = 0; // remove newline

	    if (strcmp(command, "quit") == 0) {
	        printf("Exiting...\n");
	        exit(0);
	    } else if (strlen(command) > 0) {
	        FILE *cmdOutput = popen(command, "r");
	        if (cmdOutput) {
	            char cmdLine[MAX_LINE_LENGTH];
	            while (fgets(cmdLine, MAX_LINE_LENGTH, cmdOutput)) {
	                printf("%s", cmdLine);
	            }
	            pclose(cmdOutput);
	        } else {
	            printf("Command failed to execute.\n");
	        }
	   }
	}
	return NULL;
}

int main(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s nLine inputFile delay\n", argv[0]);
        return 1;
    }

    int nLine = atoi(argv[1]);
    char *inFile = argv[2];
    int delayTime = atoi(argv[3]);

    FILE *fp = fopen(inFile, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file %s\n", inFile);
        return 1;
    }

    pthread_t process_tid;

    printf("a2p1 starts: (nLine= %d, inFile='%s', delay= %d)\n", nLine, inFile, delayTime);

    char line[MAX_LINE_LENGTH];
    int lineCount = 0;

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        if (lineCount % nLine == 0 && lineCount != 0) {;
            printf("*** Entering a delay period of %d msec\n", delayTime);
            pthread_create(&process_tid, NULL, processCommands, NULL);
            // put to sleep
    	    usleep(delayTime * 1000);
	    
    	    notified = true;
           
   	   pthread_cancel(process_tid);
   	   notified = false; 
           // the thread stops and we print it
           printf("\n*** Delay period ended\n\n"); 
           	
	   // thew ne proccess
           printf("[%04d]: %s", lineCount + 1, line);
        } else {
            printf("[%04d]: %s", lineCount + 1, line);
        }
        
        lineCount++;
    }

    fclose(fp);
    printf("Exiting...\n");
    return 0;
}
