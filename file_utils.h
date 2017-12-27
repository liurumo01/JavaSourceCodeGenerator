#include <stdio.h>

#include <sys/stat.h>
#include <sys/types.h>

#include "common.h"

#ifndef _FILE_UTILS_H_
#define _FILE_UTILS_H_

int mkdirs(char *path);
int read_file(char *filename, char **content);
int write_file(char *filename, char *content, int length);

#endif
