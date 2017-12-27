#include "file_utils.h"

int mkdirs(char *path)
{
	char *p, *q;
	char buffer[1024];

	memset(buffer, 0x00, 1024);
	p = path;
	while (*p)
	{
		q = p + 1;
		while (*q && *(q - 1) != '/')
		{
			q++;
		}
		strncat(buffer, p, q - p);
		mkdir(buffer, S_IRWXU);
		p = q;
	}

	return 0;
}

int read_file(char *filename, char **content)
{
	FILE *fp;
	int length, nret;

	fp = fopen(filename, "rb");
	if (fp == NULL)
	{
		return ERROR_OPEN_FILE_FAILED;
	}

	fseek(fp, 0, SEEK_END);
	length = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	*content = malloc(length + 1);
	if (*content == NULL)
	{
		return ERROR_OPEN_FILE_FAILED;
	}
	memset(*content, 0x00, length + 1);

	nret = fread(*content, length + 1, 1, fp);
	if (nret != 1)
	{
		return ERROR_READ_FILE_FAILED;
	}

	return length;
}

int write_file(char *filename, char *content, int length)
{
	FILE *fp;
	int nret;

	fp = fopen(filename, "wb");
	if (fp == NULL)
	{
		return ERROR_OPEN_FILE_FAILED;
	}

	nret = fwrite(content, length, 1, fp);
	if (nret != length)
	{
		return ERROR_WRITE_FILE_FAILED;
	}
	fclose(fp);

	return 0;
}
