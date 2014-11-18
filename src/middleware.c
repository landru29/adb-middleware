/**
 * \file middleware.c
 * \brief Middleware management for command interception
 * \author Meichel C.
 * \version 0.1
 * \date november 2014
 *
 * This lib manage middlewares. For instance, add a middleware like this
 *     void foo (int argc, char** argv, int* returnCode) { printf("%d\n", argc); *returnCode = 1;}
 *     MIDDLEWARES* myMid = initMiddlewareTable();
 *     myMid = addMiddleware(myMid, "foo", foo);
 *     executeMiddlewares(myMid, 3, {"foo", "arg1", "arg2"});
 *
 * a middleware with commandName == "*" will be allways executed
 */

#include "middleware.h"

/**
 * \brief get the size of a middleware table.
 *
 * \param middlewareTable Table to count.
 * \return number of elements.
 */
size_t sizeOfMiddlewareTable(MIDDLEWARE* middlewareTable) {
	size_t size;
	for(size=0; middlewareTable[size].command; size++);
	return size;
}

/**
 * \brief Initialize a middleware table.
 *
 * \return new Middleware table.
 */
MIDDLEWARE* initMiddlewareTable() {
	MIDDLEWARE* middlewareTable;
	middlewareTable = (MIDDLEWARE*)malloc(sizeof(MIDDLEWARE));
	middlewareTable->command = (char*)0;
	return middlewareTable;
}

/**
 * \brief Release memory
 *
 * \param middlewareTable Middleware table to release.
 */
void closeMiddlewareTable(MIDDLEWARE* middlewareTable) {
	free(middlewareTable);
}

/**
 * \brief resize a middleware table.
 *
 * \param middlewareTable Table to resize.
 * \param size            new size
 * \return resized middleware table.
 */
MIDDLEWARE* resizeMiddlewareTable(MIDDLEWARE* middlewareTable, size_t size) {
	MIDDLEWARE* newTable = (MIDDLEWARE*)realloc(middlewareTable, (size+1) * sizeof(MIDDLEWARE));
	newTable[size].command=0;
	return newTable;
} 

/**
 * \brief Add a new middleware in a table.
 *
 * \param middlewareTable Table to fill.
 * \param commandName     command to intercept
 * \param callback        function to invoke
 * \return resized middleware table.
 */
MIDDLEWARE* addMiddleware(MIDDLEWARE* middlewareTable, char* commandName, void* callback) {
	MIDDLEWARE* newTable;
	size_t size;
	if (!middlewareTable) {
		middlewareTable = initMiddlewareTable();
	}
	size = sizeOfMiddlewareTable(middlewareTable);
	newTable = resizeMiddlewareTable(middlewareTable, size+1);
	newTable[size].command = strdup(commandName);
	newTable[size].callback = (middlewareCallback)callback;
	return newTable;
}

/**
 * \brief Show a middleware table.
 *
 * \param middlewareTable Table to display.
 */
void showMiddleWareTable(MIDDLEWARE* middlewareTable) {
	size_t size;
	size_t i;
	size = sizeOfMiddlewareTable(middlewareTable);
	fprintf(stdout, "Number of middlewares: %d\n", size);
	for(i=0; i<size; i++) {
		fprintf(stdout, "%s\n", middlewareTable[i].command);
	}
}

/**
 * \brief execute all middlewares
 *
 * \param middlewareTable Table to execute.
 * \param argc            number of arguments to evaluate
 * \param argv            arguments to evaluate
 */
void executeMiddlewares(MIDDLEWARE* middlewareTable, int argc, char* argv[]) {
	size_t size;
	size_t i;
	int returnCode=1;
	if (argc>0) {
		size = sizeOfMiddlewareTable(middlewareTable);
		for(i=0; i<size; i++) {
			if ((strcmp(middlewareTable[i].command, argv[0]) == 0) || (strcmp(middlewareTable[i].command, "*") == 0)) {
				if (middlewareTable[i].callback) {
					middlewareTable[i].callback(argc, argv, &returnCode); 
					if (!returnCode) {
						return;
					}
				}
			}
		}
	}
}