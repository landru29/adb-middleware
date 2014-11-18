#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <sys/stat.h>
#include "constants.h"
#include "copy.h"

/**
 * \brief copy file
 *
 * \param inFile source file
 * \param outfile destination file
 * \return 0 on success
 */
int copyFile(char* inFile, char* outFile) {
    int len;
    char* buffer;
    FILE* in;
    FILE* out;
    if (!(in = fopen(inFile, "rb"))) {
        writeLog("Cannot open file");
        writeLog(inFile);
    }
    if (!(out = fopen(outFile, "wb"))) {
        writeLog("Cannot create file");
        writeLog(outFile);
    }
    if ((in) && (out)) {
        buffer = (char*)malloc(BLOCK_COPY_SIZE);
        do {
            len = fread(buffer, 1 , BLOCK_COPY_SIZE, in);
            fwrite(buffer , 1 , len , out);
        } while (len>0);
        free(buffer);
    } else return -1;
    return 0;
}

/**
 * \brief Check if a file exists
 *
 * \param filename filename to check
 * \return 1 if file exists
 */
int file_exist(char *filename)
{
  struct stat buffer;   
  return (stat(filename, &buffer) == 0);
}


