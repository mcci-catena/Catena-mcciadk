/*

Module:  mcciadklib_formatversion.c

Function:
	Home for McciAdkLib_FormatVersion()

Copyright notice:
	See accompanying LICENSE file

Author:
	Terry Moore, MCCI Corporation	April 2021

*/

#include "mcciadk_baselib.h"

/****************************************************************************\
|
|	Manifest constants & typedefs.
|
\****************************************************************************/


/****************************************************************************\
|
|	Read-only data.
|
\****************************************************************************/


/****************************************************************************\
|
|	Variables.
|
\****************************************************************************/



/*

Name:	McciAdkLib_FormatVersion()

Function:
	Convert an MCCIADK_VERSION_CALC() value to a Semantic Version string.

Definition:
	size_t
	McciAdkLib_FormatVersion(
		char *pBuffer,
		size_t nBuffer,
		size_t iBuffer,
		uint32_t version
		);

Description:
	The string for `version` is formatted starting at pBuffer + iBuffer.
	If the local (pre-release) field of `version` is zero, the string
	is `x.y.z`, where `x` is the major version, `y` the minor version,
	and `z` the patch version. Otherwise the string is `x.y.z-preP`,
	where `P` is the local field. All values are decimal, so the
	longest string is `###.###.###-pre###`; with the trailing '\0',
	that needs MCCIADKLIB_FORMAT_VERSION_BUFFER_SIZE (19) bytes.

	The routine never writes outside pBuffer[0..nBuffer-1], and
	leaves the buffer nul-terminated if it changes it.

	If pBuffer is NULL or iBuffer >= nBuffer, the buffer is not
	changed. If iBuffer == nBuffer - 1, only the trailing '\0' is
	written. Otherwise characters are written starting at
	pBuffer[iBuffer], until all have been written or the buffer
	is full.

Returns:
	The number of characters written, excluding the trailing '\0'.

Notes:
	Ported from the MCCI XDK's McciXdkLib_FormatVersion(). Correctness
	depends on McciAdkLib_Snprintf(), which returns 0..(nBuffer -
	iBuffer - 1) and always nul-terminates.

*/

size_t
McciAdkLib_FormatVersion(
	char *pBuffer,
	size_t nBuffer,
	size_t iBuffer,
	uint32_t version
	)
	{
	size_t nc;
	unsigned uPreRelease;

	MCCIADK_C_ASSERT(MCCIADKLIB_FORMAT_VERSION_BUFFER_SIZE == sizeof("###.###.###-pre###"));

	if (pBuffer == NULL || iBuffer >= nBuffer)
		return 0;

	if (iBuffer == nBuffer - 1)
		{
		pBuffer[iBuffer] = '\0';
		return 0;
		}

	nc = McciAdkLib_Snprintf(
		pBuffer, nBuffer, iBuffer,
		"%u.%u.%u",
		(unsigned) MCCIADK_VERSION_GET_MAJOR(version),
		(unsigned) MCCIADK_VERSION_GET_MINOR(version),
		(unsigned) MCCIADK_VERSION_GET_PATCH(version)
		);

	uPreRelease = (unsigned) MCCIADK_VERSION_GET_PRERELEASE(version);
	if (uPreRelease != 0)
		{
		nc += McciAdkLib_Snprintf(
			pBuffer, nBuffer, iBuffer + nc,
			"-pre%u",
			uPreRelease
			);
		}

	return nc;
	}

/**** end of mcciadklib_formatversion.c ****/
