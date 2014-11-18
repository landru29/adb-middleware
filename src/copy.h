#ifndef COPY_H
#define COPY_H


/**
 * \brief copy file
 *
 * \param inFile source file
 * \param outfile destination file
 * \return 0 on success
 */
int copyFile(char* inFile, char* outFile);

/**
 * \brief Check if a file exists
 *
 * \param filename filename to check
 * \return 1 if file exists
 */
int file_exist(char *filename);

#endif