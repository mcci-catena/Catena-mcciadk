/*

Module:  mcciadk_baselib.h

Function:
	The basic ADK library.

Copyright notice:
        See accompanying LICENSE file.

Author:
	Terry Moore, MCCI Corporation	October 2016

*/

#ifndef _MCCIADK_BASELIB_H_		/* prevent multiple includes */
#define _MCCIADK_BASELIB_H_

#ifndef _MCCIADK_ENV_H_
# include <mcciadk_env.h>
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

MCCIADK_BEGIN_DECLS

// convert a buffer of chars to an unsigned long.
size_t
McciAdkLib_BufferToUlong(
	const char *s,
	size_t n,
	unsigned base,
	unsigned long *pulnum,
	bool *pfOverflow
	);

// convert a buffer of chars to a uint32_t.
static inline size_t
McciAdkLib_BufferToUint32(
	const char *s,
	size_t n,
	unsigned base,
	uint32_t *puint32,
	bool *pfOverflow
	)
	{
	if (sizeof(uint32_t) == sizeof(unsigned long))
		{
		// some compilers think that uint32_t is not the same as unsigned long,
		// even if it's the same size. Hence the type-cast to ulong*.
		return McciAdkLib_BufferToUlong(s, n, base, (unsigned long *)puint32, pfOverflow);
		}
	else
		{
		// this code is only used on plagfroms where unsigned long is a different
		// size than uint32_t.
		unsigned long nonce;
		bool fOverflow;
		size_t const result = McciAdkLib_BufferToUlong(s, n, base, &nonce, &fOverflow);

		if (nonce > UINT32_MAX)
			{
			fOverflow = true;
			nonce = UINT32_MAX;
			}
		if (puint32)
			{
			*puint32 = (uint32_t)nonce;
			}
		if (pfOverflow)
			{
			*pfOverflow = fOverflow;
			}

		return result;
		}
	}

// check whether c is a decimal digit
static inline bool
McciAdkLib_CharIsDigit(
	char c
	)
	{
	return ('0' <= c && c <= '9');
	}

// check whether c is lower case 'a'..'z'
static inline bool
McciAdkLib_CharIsLower(
	char c
	)
	{
	return ('a' <= c && c <= 'z');
	}

// check whether c is ANSI printable
static inline bool
McciAdkLib_CharIsPrint(
	char c
	)
	{
	return (0x20 <= c && c <= 0x7e);
	}

// check whether c is upper case 'A'..'Z'
static inline bool
McciAdkLib_CharIsUpper(
	char c
	)
	{
	return ('A' <= c && c <= 'Z');
	}

// check whether c is ' ' or a control character in 0..0x1f
static inline bool
McciAdkLib_CharIsWhite(
	char c
	)
	{
	return ((c & 0xFF) <= 0x20);
	}

// if c is an upper case letter, return the lower-case equivalent;
// otherwise return c unchanged.
static inline char
McciAdkLib_CharToLower(
	char c
	)
	{
	if (McciAdkLib_CharIsUpper(c))
		return c - 'A' + 'a';
	else
		return c;
	}

// copy a string into a buffer, starting at an offset in the buffer.
size_t
McciAdkLib_SafeCopyString(
	char *pBuffer,
	size_t nBuffer,
	size_t iBuffer,
	const char *pString
	);

// compare strings, case-insensitive
int
McciAdkLib_StringCompareCaseInsensitive(
        const char *pLeft,
        const char *pRight
        );

// prepare a canonical "hex dump" line from a buffer.
size_t
McciAdkLib_FormatDumpLine(
	char *pLine,
	size_t nLine,
        size_t iLine,
	uint32_t address,
	const uint8_t *pBuffer,
	size_t nBuffer
	);

// index into a string of null-terminated strings, terminated by a double-null.
const char *
McciAdkLib_MultiSzIndex(
	const char * pmultiszStrings,
	unsigned uIndex
	);

// a portable snprintf() to get away from compiler variations.
size_t
McciAdkLib_Snprintf(
	char *pOutbuf,
	size_t nOutbuf,
	size_t iOutbuf,
	const char *pFmt,
	...
	);

// a portable vsnprintf() to avoid compiler variations.
size_t
McciAdkLib_Vsnprintf(
	char *pOutbuf,
	size_t nOutbuf,
	size_t iOutbuf,
	const char *pFmt,
	va_list ap
	);

MCCIADK_END_DECLS

/**** end of mcciadk_baselib.h ****/
#endif /* _MCCIADK_BASELIB_H_ */
