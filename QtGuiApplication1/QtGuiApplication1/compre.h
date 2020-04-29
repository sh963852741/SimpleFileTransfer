#pragma once
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "zlib.h"
#include<string>
using namespace std;
#pragma comment(lib, "zlib.lib")  
#define _CRT_SECURE_NO_WARNINGS

#if defined(MSDOS) || defined(OS2) || defined(WIN32) || defined(__CYGWIN__)
#  include <fcntl.h>
#  include <io.h>
#  define SET_BINARY_MODE(file) _setmode(_fileno(file), O_BINARY)
#else
#  define SET_BINARY_MODE(file)
#endif

#define CHUNK 16384

int def(string source, string dest, int level);


int inf(string source, string dest);


/* report a zlib or i/o error */
void zerr(int ret);
