#include "PCH.h"
#include "FFbxDataConverter.h"

using namespace Sand;

Vector3f FFbxDataConverter::ConvertPos( FbxVector4 Vector )
{
	Vector3f Out;
	Out[0] = ( float )Vector[0];
	Out[1] = ( float )Vector[1];
	Out[2] = ( float )Vector[2];

	return Out;
}

Vector3f FFbxDataConverter::ConvertDir( FbxVector4 Vector )
{
	Vector3f Out;
	Out[0] = ( float )Vector[0];
	Out[1] = ( float )Vector[1];
	Out[2] = ( float )Vector[2];

	return Out;
}

Vector3f FFbxDataConverter::ConvertScale( FbxDouble4 Vector )
{
	Vector3f Out;
	Out[0] = ( float )Vector[0];
	Out[1] = ( float )Vector[1];
	Out[2] = ( float )Vector[2];

	return Out;
}

Vector3f FFbxDataConverter::ConvertScale( FbxDouble3 Vector )
{
	Vector3f Out;
	Out[0] = ( float )Vector[0];
	Out[1] = ( float )Vector[1];
	Out[2] = ( float )Vector[2];

	return Out;
}

Matrix4f FFbxDataConverter::ConvertMatrix( FbxAMatrix Matrix )
{
	Matrix4f OutMatrix;

	for ( int i = 0; i < 4; i++ )
	{
		for ( int j = 0; j < 4; j++ )
		{
			OutMatrix( i , j ) = ( float )Matrix.Double44()[i][j];
		}
	}

	return OutMatrix;
}