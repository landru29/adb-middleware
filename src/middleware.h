#ifndef MIDDLEWARE_H
#define MIDDLEWARE_H

#ifndef CALLBACK
#if defined(_MSC_VER)
#define CALLBACK __cdecl
#elif defined(__GNUC__) && defined(__i386) && !defined(__INTEL_COMPILER)
#define CALLBACK __attribute__((cdecl))
#else
#define CALLBACK
#endif
#endif  /* not defined CALLBACK */

#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef void (CALLBACK *middlewareCallback) (int argc, char** argv, int* returnCode);

typedef struct middleware {
    char* command;
    middlewareCallback callback;
} MIDDLEWARE;

/**
 * \brief Initialize a middleware table.
 *
 * \return new Middleware table.
 */
MIDDLEWARE* initMiddlewareTable();

/**
 * \brief Release memory
 *
 * \param middlewareTable Middleware table to release.
 */
void closeMiddlewareTable(MIDDLEWARE* middlewareTable);

/**
 * \brief Add a new middleware in a table.
 *
 * \param middlewareTable Table to fill.
 * \param commandName     command to intercept
 * \param callback        function to invoke
 * \return resized middleware table.
 */
MIDDLEWARE* addMiddleware(MIDDLEWARE* middlewareTable, char* commandName, void* callback);

/**
 * \brief Show a middleware table.
 *
 * \param middlewareTable Table to display.
 */
void showMiddleWareTable(MIDDLEWARE* middlewareTable);

/**
 * \brief execute all middlewares
 *
 * \param middlewareTable Table to execute.
 * \param argc            number of arguments to evaluate
 * \param argv            arguments to evaluate
 */
void executeMiddlewares(MIDDLEWARE* middlewareTable, int argc, char* argv[]);

#endif