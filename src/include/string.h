#ifndef __hoodwink_string_h__
#define __hoodwink_string_h__

#include "types.h"

static inline int strcmp(const char *s1, const char *s2)
{
	while (*s1) {
		if (*s1 != *s2)
			return *s1 - *s2;

		s1++;
		s2++;
	}

	if (*s2)
		return -1;

	return 0;
}

static inline size_t strlen(const char *str)
{
	size_t len = 0;

	while (*str++)
		len++;

	return len;
}

static inline void *memcpy(void *dest, const void *src, size_t n)
{
	char *dest_ch = dest;
	const char *src_ch = src;

	while (n--)
		*dest_ch++ = *src_ch++;

	return dest;
}

static inline void *memset(void *s, int c, size_t n)
{
	char *dest_ch = s;

	while (n--)
		*dest_ch++ = c;

	return s;
}

#endif /* __hoodwink_string_h__ */
