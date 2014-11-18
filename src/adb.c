#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <time.h>
#include "middleware.h"
#include "path.h"
#include "copy.h"
#include "constants.h"



MIDDLEWARE* middlewares;


/**
 * \brief write data in the logfile
 *
 * \param message Message to log 
 */
void writeLog(char* message) {
    FILE * pFile;
    time_t current_time;
    char* c_time_string;
    if (message) {
        pFile = fopen (getLogPath(),"a");
        if (pFile!=NULL)
        {
            current_time = time(NULL);
            c_time_string = ctime(&current_time);
            c_time_string[strlen(c_time_string)-1] = 0;
            fprintf (pFile, "%s : %s\n", c_time_string, message);
            fclose (pFile);
        }
    }
}

/**
 * \brief Build the command to launch
 *
 * \param argc number of arguments to evaluate (from main function)
 * \param argv arguments to evaluate (from main function)
 * \return command
 */
char* buildCommand(int argc,char** argv) {
    size_t size=0;
    int i;
    char* buffer=0;
    char* realAdbPath;

    realAdbPath = getAdbPath();
    if (!file_exist(realAdbPath)) {
        writeLog("Cannot find adb path:");
        writeLog(realAdbPath);
    } else {
       // Initialize the command buffer with the command name
        buffer = (char*) malloc(strlen(realAdbPath)+4);
        sprintf(buffer, "\"\"%s\"", realAdbPath);
        size = strlen(buffer) + 1;

        // Loop on the arguments to append to the command buffer
        for(i=0; i<argc; i++) {
            size += strlen(argv[i]) + 3;
            buffer = (char*) realloc(buffer, size + 1);
            sprintf(buffer, "%s \"%s\"", buffer, argv[i]);
        }
        buffer[strlen(buffer)+1] = 0;
        buffer[strlen(buffer)] = '\"';
    }
    return buffer;
}

/**
 * \brief Callback for push command
 *
 * \param argc number of arguments to evaluate
 * \param argv arguments to evaluate
 */
void pushCallback(int argc, char** argv, int* returnCode) {
    char* outFile;
    char* inFile;
    int i;

    if (argc>1) {
        // build in and out file
        inFile = argv[1];
        for(i=strlen(inFile)-1; i>=0; i--) {
            if ((inFile[i] == '\\') || (inFile[i] == '/') || (i==0)) {
                outFile = getOutFilePath(&inFile[(inFile[i] == '\\') || (inFile[i] == '/') ? i+1 : i]);
                i=0;
            }
        }
        
        //copy file
        writeLog("Copying file to");
        writeLog(outFile);
        if (copyFile(inFile, outFile)) {
            writeLog("Error while copying file");
            writeLog(inFile);
        }
        
    }
    *returnCode = 1;
}

/**
 * \brief Callback for shell command
 *
 * \param argc number of arguments to evaluate
 * \param argv arguments to evaluate
 */
void openShell(int argc, char** argv, int* returnCode) {
    if (argc > 1) {
        *returnCode = 1;
        return;
    }
    *returnCode = 0;
    // create a child process
    // listen to stdin and send it to the process
    // if 'exit' kill the child process and return

}

/**
 * \brief Callback for all commands
 *
 * \param argc number of arguments to evaluate
 * \param argv arguments to evaluate
 */
void logAndExecuteCommand(int argc, char** argv, int* returnCode) {
    char* command;
    char* stdoutData;
    FILE* output;
    char buffer[65536] = {0};


    // build the command
    command = buildCommand(argc, argv);

    // Log the command
    writeLog(command);

    // Execute the command
    if ((command) && (strlen(command) > 0)) {
        output = popen(command, "r");
        fread(buffer, 1 , BLOCK_COPY_SIZE, output);
        writeLog("########## ADB STD OUT ##########");
        writeLog(buffer);
        writeLog("#################################");
        printf("%s", buffer);
        pclose(output);
        //system(command);    
    } else {
        writeLog("No path is defined for adb; please create file :");
        writeLog(getIniPath());
        writeLog("and add a line with the full path of ADB");
    }

    // Release the memory
    free(command);
    *returnCode = 1;
}


/**
 * Main program
 */
int main(int argc,char** argv){
    int status = 0;
    char* command;

    // Initialize middleware table
    middlewares = initMiddlewareTable();

    // adding a middleware
    middlewares = addMiddleware(middlewares, "shell", openShell);
    middlewares = addMiddleware(middlewares, "push", pushCallback);
    middlewares = addMiddleware(middlewares, "*", logAndExecuteCommand);

    //processing middlewares
    executeMiddlewares(middlewares, argc-1, &argv[1]);

    //release memory
    closeMiddlewareTable(middlewares);

    // Return exit codes
    exit(0);
    return 0;
}
