#include "PCH.h"

#include "GeometryLoader.h"
#include "FileSystem.h"
#include "Log.h"
#include "OBJ.h"
#include "VertexElement.h"

using namespace Sand;

std::array<int , 3> ToIndexTriple( const std::string s )
{
	std::vector<std::string> elements;
	std::stringstream ss( s );
	std::string item;

	// ��ss��'/'Ϊ�ָ�����item����ָ���string
	while( std::getline( ss , item , '/' ) )
	{
		elements.push_back( item );
	}

	assert( elements.size() >= 1 && elements.size() <= 3 );

	std::array<int , 3> triple = { 0 , 0 , 0 };

	for( int i = 0; i < elements.size(); i++ )
	{
		triple[i] = atoi( elements[i].c_str() ) - 1;
	}

	return triple;
}

GeometryPtr GeometryLoader::LoadOBJ( std::wstring filename )
{
	// �����ļ�����·��
	FileSystem fs;
	filename = fs.GetModelFolder() + filename;

	// ���ļ�
	std::ifstream fin( filename , std::ios::in );
	if( !fin.is_open() )
	{
		Log::Get().Write( L"open obj file failed!" );
		return nullptr;
	}

	// ���ڱ��涥��λ������
	std::vector<Vector3f> Positions;
	// ���ڱ��涥�㷨������
	std::vector<Vector3f> Normals;
	// ���ڱ��涥����������
	std::vector<Vector2f> Texcoords;

	// ���ڱ�����
	std::vector<OBJFace> Faces;

	// һ��һ�еĶ�ȡ����
	std::string line;

	while( std::getline( fin , line ) )
	{
		std::stringstream lineStream( line );
		std::string token;
		std::vector<std::string> tokenList;

		// ��ȡ�ַ���
		while( lineStream >> token )
		{
			tokenList.push_back( token );
		}

		if( tokenList.size() != 0 )
		{
			// ��������
			if( tokenList[0] == "v" )
			{
				Positions.emplace_back( Vector3f(	static_cast< float >( atof( tokenList[1].c_str() ) ) ,
													static_cast< float >( atof( tokenList[2].c_str() ) ) ,
													static_cast< float >( atof( tokenList[3].c_str() ) ) ) );
			}
			// ����
			else if( tokenList[0] == "vn" )
			{
				Normals.emplace_back( Vector3f( static_cast< float >( atof( tokenList[1].c_str() ) ) ,
												static_cast< float >( atof( tokenList[2].c_str() ) ) ,
												static_cast< float >( atof( tokenList[3].c_str() ) ) ) );
			}
			else if( tokenList[0] == "vt" )
			{
				Texcoords.emplace_back( Vector2f(	static_cast< float >( atof( tokenList[1].c_str() ) ) ,
													static_cast< float >( atof( tokenList[2].c_str() ) ) ) );
			}
			else if( tokenList[0] == "f" )
			{
				OBJFace face;

				for( int i = 0; i < 3; i++ )
				{
					// ʹ��'/'��Ϊ�ָ�������������ȡ����
					auto triple = ToIndexTriple( tokenList[i + 1] );

					face.PositionIndices[i] = triple[0];
					face.CoordinateIndices[i] = triple[1];
					face.NormalIndices[i] = triple[2];
				}

				Faces.emplace_back( face );
			}
		}
	}

	fin.close();


	GeometryPtr MeshPtr = GeometryPtr( new Geometry );

	VertexElement* PosVertexElement = new VertexElement( 3 , Faces.size() * 3 );
	PosVertexElement->m_SemanticName = VertexElement::PositionSemantic;
	PosVertexElement->m_uiSemanticIndex = 0;
	PosVertexElement->m_Format = DXGI_FORMAT_R32G32B32_FLOAT;
	PosVertexElement->m_uiInputSlot = 0;
	PosVertexElement->m_uiAlignedByteOffset = 0;
	PosVertexElement->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	PosVertexElement->m_uiInstanceDataStepRate = 0;

	VertexElement* TexVertexElement = new VertexElement( 2 , Faces.size() * 3 );
	TexVertexElement->m_SemanticName = VertexElement::TexCoordSemantic;
	TexVertexElement->m_uiSemanticIndex = 0;
	TexVertexElement->m_Format = DXGI_FORMAT_R32G32_FLOAT;
	TexVertexElement->m_uiInputSlot = 0;
	TexVertexElement->m_uiAlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	TexVertexElement->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	TexVertexElement->m_uiInstanceDataStepRate = 0;

	VertexElement* NormalVertexElement = new VertexElement( 3 , Faces.size() * 3 );
	NormalVertexElement->m_SemanticName = VertexElement::NormalSemantic;
	NormalVertexElement->m_uiSemanticIndex = 0;
	NormalVertexElement->m_Format = DXGI_FORMAT_R32G32B32_FLOAT;
	NormalVertexElement->m_uiInputSlot = 0;
	NormalVertexElement->m_uiAlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	NormalVertexElement->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	NormalVertexElement->m_uiInstanceDataStepRate = 0;

	// ��ȡ����ָ��
	Vector3f* Pos = ( Vector3f* )( ( *PosVertexElement )[0] );
	Vector2f* Tex = ( Vector2f* )( ( *TexVertexElement )[0] );
	Vector3f* Normal = ( Vector3f* )( ( *NormalVertexElement )[0] );

	for( int i = 0; i < Faces.size(); i++ )
	{
		// ����ÿ����
		int index_1 = 3 * i + 0;
		int index_2 = 3 * i + 1;
		int index_3 = 3 * i + 2;

		// ---------------------��һ������------------------------
		Pos[3 * i + 0].x = Positions[Faces[i].PositionIndices[0]].x;
		Pos[3 * i + 0].y = Positions[Faces[i].PositionIndices[0]].y;
		Pos[3 * i + 0].z = Positions[Faces[i].PositionIndices[0]].z;

		Tex[3 * i + 0].x = Texcoords[Faces[i].CoordinateIndices[0]].x;
		Tex[3 * i + 0].y = Texcoords[Faces[i].CoordinateIndices[0]].y;

		Normal[3 * i + 0].x = Normals[Faces[i].NormalIndices[0]].x;
		Normal[3 * i + 0].y = Normals[Faces[i].NormalIndices[0]].y;

		// ---------------------�ڶ�������------------------------------
		Pos[3 * i + 1].x = Positions[Faces[i].PositionIndices[1]].x;
		Pos[3 * i + 1].y = Positions[Faces[i].PositionIndices[1]].y;
		Pos[3 * i + 1].z = Positions[Faces[i].PositionIndices[1]].z;

		Tex[3 * i + 1].x = Texcoords[Faces[i].CoordinateIndices[1]].x;
		Tex[3 * i + 1].y = Texcoords[Faces[i].CoordinateIndices[1]].y;

		Normal[3 * i + 1].x = Normals[Faces[i].NormalIndices[1]].x;
		Normal[3 * i + 1].y = Normals[Faces[i].NormalIndices[1]].y;

		// ---------------------����������------------------------------
		Pos[3 * i + 2].x = Positions[Faces[i].PositionIndices[2]].x;
		Pos[3 * i + 2].y = Positions[Faces[i].PositionIndices[2]].y;
		Pos[3 * i + 2].z = Positions[Faces[i].PositionIndices[2]].z;

		Tex[3 * i + 2].x = Texcoords[Faces[i].CoordinateIndices[2]].x;
		Tex[3 * i + 2].y = Texcoords[Faces[i].CoordinateIndices[2]].y;

		Normal[3 * i + 2].x = Normals[Faces[i].NormalIndices[2]].x;
		Normal[3 * i + 2].y = Normals[Faces[i].NormalIndices[2]].y;

		// ����������
		MeshPtr->AddFace( index_1 , index_2 , index_3 );
	}

	MeshPtr->AddElement( PosVertexElement );
	MeshPtr->AddElement( TexVertexElement );
	MeshPtr->AddElement( NormalVertexElement );

	return MeshPtr;
}

Vector2f GeometryLoader::ToVector2f( const std::vector<std::string>& tokens )
{
	assert( tokens.size() >= 3 );

	return Vector2f( static_cast< float >( atof( tokens[1].c_str() ) ) ,
					 static_cast< float >( atof( tokens[2].c_str() ) ) );
}

Vector3f GeometryLoader::ToVector3f( const std::vector<std::string>& tokens )
{
	assert( tokens.size() >= 4 );

	return Vector3f( static_cast< float >( atof( tokens[1].c_str() ) ) ,
					 static_cast< float >( atof( tokens[2].c_str() ) ) ,
					 static_cast< float >( atof( tokens[3].c_str() ) ) );
}