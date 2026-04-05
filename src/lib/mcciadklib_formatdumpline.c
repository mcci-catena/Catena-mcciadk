/*

Module:  mcciadklib_formatdumpline.c

Function:
	McciAdkLib_FormatDumpLine()

Copyright notice:
        See accompanying LICENSE file.

Author:
	Terry Moore, MCCI Corporation	March 2017

*/

#include "mcciadk_baselib.h"

/*

Name:	McciAdkLib_FormatDumpLine()

Function:
	Format a memory dump fragment.

Definition:
	size_t McciAdkLib_FormatDumpLine(
		char *pLine,
		size_t nLine,
		size_t iLine,
		uint32_t address,
		const uint8_t *pBuffer,
		size_t nBuffer
		);

Description:
	A standard dump line is produced into pLine starting at offset iLine.
	The number of characters written is returned. A '\0' is always
	appended but not included in the length. Writes are restricted to
	the range pLine + [0, nLine-1].

Returns:
	The index of the trailing '\0'.

*/

size_t
McciAdkLib_FormatDumpLine(
	char *pLine,
	size_t nLine,
	size_t iLine,
	uint32_t uAddress,
	const uint8_t *pBuffer,
	size_t nBuffer
	)
	{
	char textrep[17];

	iLine += McciAdkLib_Snprintf(
			pLine, nLine, iLine,
			"%08x ", uAddress
			);

	textrep[sizeof(textrep) - 1] = '\0';

	for (unsigned j = 0; j < 16; ++j)
		{
		if (j < nBuffer)
			{
			uint8_t c;

			c = pBuffer[j];
			iLine += McciAdkLib_Snprintf(
					pLine, nLine, iLine,
					" %02x",
					c
					);

			if (! McciAdkLib_CharIsPrint(c))
				c = '.';

			textrep[j] = c;
			}
		else
			{
			iLine += McciAdkLib_Snprintf(
					pLine, nLine, iLine,
					"   "
					);
			textrep[j] = '\0';
			}

                // put the space between the groups of 8.
		if (j == 7)
			{
			iLine += McciAdkLib_Snprintf(
				pLine, nLine, iLine,
				" "
				);
			}
		}

	iLine += McciAdkLib_Snprintf(
			pLine, nLine, iLine,
			"  %s", textrep
			);

	return iLine;
	}
