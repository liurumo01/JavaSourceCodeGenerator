#include <string.h>
#include <ctype.h>

#ifndef _STRING_UTILS_H_
#define _STRING_UTILS_H_

int string_end_with(char *str, char *suffix);
char *string_underline_to_camel_case(char *src, char *dest);
char *string_first_char_to_upper_case(char *str, char *buffer);
char *string_first_char_to_lower_case(char *str, char *buffer);
char *string_substring(char *str, char *dest, int start, int end);
int string_replace(char *src, char *dest, char *target, char *replacement);

#endif
