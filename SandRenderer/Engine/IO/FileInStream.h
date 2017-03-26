#ifndef FILE_IN_STREAM_H
#define FILE_IN_STREAM_H

#include "IVFileStream.h"
#include <fstream>

namespace Sand
{
	class FileInStream : public IVFileStream
	{
	public:
		FileInStream( const char* szFilename );

		bool OpenChunk( uint32& chunkName );
		bool CloseChunk();

		bool ReadInt( int& value );
		bool ReadFloat( float& value );
		bool ReadString( char* str );
		bool Read( char* ptr , int sizeInByte );

		void Close();

	public:
		std::ifstream ifs;
	};
}
#endif