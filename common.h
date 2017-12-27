#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _COMMON_H_
#define _COMMON_H_

#define ERROR_MALLOC_FAILED -1
#define ERROR_OPEN_FILE_FAILED -2
#define ERROR_READ_FILE_FAILED -3
#define ERROR_WRITE_FILE_FAILED -4
#define ERROR_EXECUTE_COMMAND_FAILED -5

#define IMPORT_FLAG_DATE 1

struct field
{
	char type[32];
	char name[256];
};

struct bean
{
	char name[256];
	int import_flag;
	int field_max_count;
	int field_count;
	struct field *fields;
};

struct project_config
{
	char name[256];
	char package[256];
	int beans_count;
	int beans_max_count;
	struct bean *beans;
};

#endif
