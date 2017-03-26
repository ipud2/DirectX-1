#ifndef IV_FILE_STREAM_H
#define IV_FILE_STREAM_H

#include <windows.h>

namespace Sand
{
	class IVFileStream
	{
	public:
		IVFileStream( const char* str )
		{
			strcpy_s( szFilename , MAX_PATH , str );
		}

	public:
		char* szFilename;
	};
}
#endif