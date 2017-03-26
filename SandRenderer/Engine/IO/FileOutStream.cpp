#include "PCH.h"
#include "FileOutStream.h"
#include "Vector2f.h"
#include "Vector3f.h"
#include "Vector4f.h"

using namespace Sand;

FileOutStream::FileOutStream( const char* filename )
	:IVFileStream( filename )
{
	ofs.open( filename , std::ios::out | std::ios::binary );
}

void FileOutStream::WriteInt( const int value )
{
	ofs.write( ( char* )( &value ) , sizeof( int ) );
}

void FileOutStream::WriteFloat( const float value )
{
	ofs.write( ( char* )( &value ) , sizeof( float ) );
}

void FileOutStream::WriteString( const char* str )
{
	int SizeInBytes = ( int )strlen( str );
	WriteInt( SizeInBytes );
	ofs.write( str , SizeInBytes );
}

void FileOutStream::WriteVector( const Vector2f& v )
{
	WriteFloat( v[0] );
	WriteFloat( v[1] );
}

void FileOutStream::WriteVector( const Vector3f& v )
{
	WriteFloat( v[0] );
	WriteFloat( v[1] );
	WriteFloat( v[2] );
}

void FileOutStream::WriteVector( const Vector4f& v )
{
	WriteFloat( v[0] );
	WriteFloat( v[1] );
	WriteFloat( v[2] );
	WriteFloat( v[3] );
}

void FileOutStream::Write( const char* ptr , int SizeInBytes )
{
	ofs.write( ptr , SizeInBytes );
}

void FileOutStream::Close()
{
	ofs.close();
}

bool FileOutStream::StartChunk( uint32 chunkName )
{
	if ( ofs.write( ( char* )&chunkName , sizeof( uint32 ) ) )
	{
		return true;
	}
	
	return false;
}

void FileOutStream::EndChunk()
{

}