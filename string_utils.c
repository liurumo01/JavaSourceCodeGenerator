#include "string_utils.h"

int string_end_with(char *str, char *suffix)
{
	while (strlen(str) > strlen(suffix))
	{
		str++;
	}
	return strcmp(str, suffix) == 0;
}

char *string_underline_to_camel_case(char *src, char *dest)
{
	int new_word;
	char *p;

	p = dest;
	new_word = 1;
	while (*src)
	{
		if (*src == '_')
		{
			new_word = 1;
			src++;
		}
		if (new_word)
		{
			*p++ = toupper(*src);
			new_word = 0;
		}
		else
		{
			*p++ = *src;
		}
		src++;
	}
	*p = '\0';

	return dest;
}

char *string_first_char_to_upper_case(char *str, char *buffer)
{
	strcpy(buffer, str);
	*buffer = toupper(*buffer);
	return buffer;
}

char *string_first_char_to_lower_case(char *str, char *buffer)
{
	strcpy(buffer, str);
	*buffer = tolower(*buffer);
	return buffer;
}

char *string_substring(char *str, char *dest, int start, int end)
{
	int length;

	length = end - start;
	memcpy(dest, str + start, length);
	dest[length] = '\0';
	return dest;
}

int string_replace(char *src, char *dest, char *target, char *replacement)
{
	int i, j, count;
	for (i = 0, j = 0, count = 0; i < strlen(src); i++)
	{
		if (strncmp(src + i, target, strlen(target)) == 0)
		{
			strncpy(dest + j, replacement, strlen(replacement));
			j += strlen(replacement);
			i += strlen(target) - 1;
			count++;
		}
		else
		{
			dest[j++] = src[i];
		}
	}
	dest[j] = '\0';
	return count;
}
