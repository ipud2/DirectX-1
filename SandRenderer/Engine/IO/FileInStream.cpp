#include "PCH.h"
#include "FileInStream.h"

using namespace Sand;

FileInStream::FileInStream( const char* filename )
	: IVFileStream( filename )
{
	ifs.open( filename , std::ios::in | std::ios::binary );
}

bool FileInStream::Read( char* ptr , int sizeInByte )
{
	if(ifs.read( ( char* )ptr , sizeInByte ))
	{
		return true;
	}

	return false;
}

bool FileInStream::ReadInt( int& value )
{
	if ( ifs.read( ( char* )( &value ) , sizeof( int ) ) )
	{
		return true;
	}

	return false;
}

bool FileInStream::ReadFloat( float& value )
{
	if ( ifs.read( ( char* )( &value ) , sizeof( float ) ) )
	{
		return true;
	}

	return false;
}

bool FileInStream::ReadString( char* str )
{
	int size = 0;
	if ( !ReadInt( size ) )
	{
		return false;
	}

	if ( !ifs.read( str , size ) )
	{
		return false;
	}

	return true;
}

void FileInStream::Close()
{
	ifs.close();
}

bool FileInStream::OpenChunk( uint32& chunkName )
{
	int ChunkID;
	if ( ReadInt( ChunkID ) )
	{
		chunkName = ChunkID;
		return true;
	}
	return false;
}

bool FileInStream::CloseChunk()
{
	return true;
}