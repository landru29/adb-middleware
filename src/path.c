#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "path.h"
#include "constants.h"

char* logPath = 0;
char* homePath=0;

/**
 * \brief Check if a path exists
 *
 * \param pathname pathname to check
 * \return 1 if path exists
 */
int path_exist(char *pathname)
{
  struct stat buffer;   
  return (stat(pathname, &buffer) == 0);
}

/**
 * \brief get the home path
 *
 * \return home path
 */
char* getHomePath() {
    char* pPath;
    char* pDrive;
    if (homePath) {
        free(homePath);
    }
    pPath = getenv ("HOMEPATH");
    pDrive = getenv ("HOMEDRIVE");
    homePath = (char*)malloc(strlen(pPath) + 1 + strlen(pDrive));
    sprintf(homePath, "%s%s", pDrive, pPath);
    return homePath;
}

/**
 * \brief Build a log path
 *
 * \return log path
 */
char* getLogPath() {
    char* pPath;
    if (logPath) {
        free(logPath);
    }
    pPath = getHomePath();
    logPath = (char*)malloc(strlen(pPath) + 2 + strlen(ADB_LOG_FILE));
    sprintf(logPath, "%s\\%s", pPath, ADB_LOG_FILE);
    return logPath;
}

/**
 * \brief Build an out path
 *
 * \param filename filename of the file to create
 * \return full path
 */
char* getOutFilePath(char* filename) {
    char* pPath;
    char* outFolder;
    pPath = getHomePath();
    outFolder = (char*)malloc(strlen(pPath) + 3 + strlen(filename) + strlen(FILE_FOLDER));
    sprintf(outFolder, "%s\\%s", pPath, FILE_FOLDER);
    if (!path_exist(outFolder)) {
    	mkdir(outFolder);
    }
    sprintf(outFolder, "%s\\%s\\%s", pPath, FILE_FOLDER, filename);
    return outFolder;
}

/**
 * \brief get the path of the ini file
 *
 * \return ini path
 */
char* getIniPath() {
    char* pPath;
    char* iniFile;
    pPath = getHomePath();
    iniFile = (char*)malloc(strlen(pPath) + 2 + strlen(INIPATH));
    sprintf(iniFile, "%s\\%s", pPath, INIPATH);
    return iniFile;
}

/**
 * \brief get the path of the real ADB program
 *
 * \return adb path
 */
char* getAdbPath() {
    char* pPath;
    char* iniFile;
    char adbPath[1000] = "";
    FILE* pIni;
    int i;

    iniFile = getIniPath();
 
    // Read the content of the ini file
    pIni = fopen (iniFile, "r");
    if (pIni != NULL) {
        fread (adbPath, 1 , 1000, pIni);
        fclose(pIni);
        // remove non printable characters
        for(i=0; ((i<1000) && (adbPath[i])); i++) {
            if (adbPath[i]<32) {
                adbPath[i]=0;
            }
        }
        adbPath[999]=0;
    }
    return strdup(adbPath);
}