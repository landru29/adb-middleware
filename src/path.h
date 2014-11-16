#ifndef PATH_H
#define PATH_H

/**
 * \brief get the home path
 *
 * \return home path
 */
char* getHomePath();

/**
 * \brief Build a log path
 *
 * \return log path
 */
char* getLogPath();

/**
 * \brief Build an out path
 *
 * \param filename filename of the file to create
 * \return full path
 */
char* getOutFilePath(char* filename);

/**
 * \brief get the path of the ini file
 *
 * \return ini path
 */
char* getIniPath();

/**
 * \brief get the path of the real ADB program
 *
 * \return adb path
 */
char* getAdbPath();

#endif