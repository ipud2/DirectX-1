#ifndef FILE_OUT_STREAM_H
#define FILE_OUT_STREAM_H

#include "IVFileStream.h"
#include <fstream>

namespace Sand
{
	class Vector2f;
	class Vector3f;
	class Vector4f;

	class FileOutStream : public IVFileStream
	{
	public:
		FileOutStream( const char* filename );

		bool StartChunk( uint32 chunkName );
		void EndChunk();

		void WriteInt( const int value );
		void WriteFloat( const float value );
		void WriteString( const char* str );
		void WriteVector( const Vector2f& v );
		void WriteVector( const Vector3f& v );
		void WriteVector( const Vector4f& v );
		void Write( const char* ptr , int SizeInBytes );

		void Close();

	protected:
		std::ofstream ofs;
	};
}
#endif