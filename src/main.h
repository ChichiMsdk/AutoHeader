#ifndef MAIN_H
#define MAIN_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // pmode for umask
#include <stdbool.h>
#include <ctype.h>
#include "split.h"

#define KB 1024
#define MB KB * 1000
// this must contain whole char by whole char .. (idk how)!
#define READ_SIZE (sizeof(char) * 100)
#define MAX_PARAM 127 // c standard
#define NAME_LENGTH 256 // arbitrary
#define MAX_FUN 500

// accounts for each space between params, parenthesis and semi-colon
#define ARBITRARY_LENGTH (MAX_PARAM * NAME_LENGTH) + MAX_PARAM + 3

#endif
