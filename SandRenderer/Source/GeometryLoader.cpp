#include "PCH.h"

#include "GeometryLoader.h"
#include "FileSystem.h"
#include "Log.h"
#include "OBJ.h"
#include "MS3D.h"
#include "VertexElement.h"

using namespace Sand;

std::array<int , 3> ToIndexTriple( const std::string s )
{
	std::vector<std::string> elements;
	std::stringstream ss( s );
	std::string item;

	// 将ss以'/'为分隔符，item保存分割后的string
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

GeometryPtr GeometryLoader::LoadOBJ( std::wstring& filename )
{
	// 构造文件绝对路径
	FileSystem fs;
	filename = fs.GetModelFolder() + filename;

	// 打开文件
	std::ifstream fin( filename , std::ios::in );
	if( !fin.is_open() )
	{
		Log::Get().Write( L"open obj file failed!" );
		return nullptr;
	}

	// 用于保存顶点位置数据
	std::vector<Vector3f> Positions;
	// 用于保存顶点法线数据
	std::vector<Vector3f> Normals;
	// 用于保存顶点纹理数据
	std::vector<Vector2f> Texcoords;

	// 用于保存面
	std::vector<OBJFace> Faces;

	// 一行一行的读取数据
	std::string line;

	while( std::getline( fin , line ) )
	{
		std::stringstream lineStream( line );
		std::string token;
		std::vector<std::string> tokenList;

		// 提取字符串
		while( lineStream >> token )
		{
			tokenList.push_back( token );
		}

		if( tokenList.size() != 0 )
		{
			// 顶点数据
			if( tokenList[0] == "v" )
			{
				Positions.emplace_back( Vector3f(	static_cast< float >( atof( tokenList[1].c_str() ) ) ,
													static_cast< float >( atof( tokenList[2].c_str() ) ) ,
													static_cast< float >( atof( tokenList[3].c_str() ) ) ) );
			}
			// 法线
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
					// 使用'/'作为分隔符，将数据提取出来
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

	if ( Positions.size() != 0 )
	{
		Vector3f* Pos = ( Vector3f* )( ( *PosVertexElement )[0] );

		for ( int i = 0; i < Faces.size(); i++ )
		{
			// 遍历每个面
			int index_1 = 3 * i + 0;
			int index_2 = 3 * i + 1;
			int index_3 = 3 * i + 2;

			// ---------------------第一个顶点------------------------
			Pos[index_1].x = Positions[Faces[i].PositionIndices[0]].x;
			Pos[index_1].y = Positions[Faces[i].PositionIndices[0]].y;
			Pos[index_1].z = Positions[Faces[i].PositionIndices[0]].z;

			// ---------------------第二个顶点------------------------------
			Pos[index_2].x = Positions[Faces[i].PositionIndices[1]].x;
			Pos[index_2].y = Positions[Faces[i].PositionIndices[1]].y;
			Pos[index_2].z = Positions[Faces[i].PositionIndices[1]].z;

			// ---------------------第三个顶点------------------------------
			Pos[index_3].x = Positions[Faces[i].PositionIndices[2]].x;
			Pos[index_3].y = Positions[Faces[i].PositionIndices[2]].y;
			Pos[index_3].z = Positions[Faces[i].PositionIndices[2]].z;
		}
	}

	MeshPtr->AddElement( PosVertexElement );


	VertexElement* TexVertexElement = TexVertexElement = new VertexElement( 2 , Faces.size() * 3 );
	TexVertexElement->m_SemanticName = VertexElement::TexCoordSemantic;
	TexVertexElement->m_uiSemanticIndex = 0;
	TexVertexElement->m_Format = DXGI_FORMAT_R32G32_FLOAT;
	TexVertexElement->m_uiInputSlot = 0;
	TexVertexElement->m_uiAlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	TexVertexElement->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	TexVertexElement->m_uiInstanceDataStepRate = 0;

	if ( Texcoords.size() != 0 )
	{
		Vector2f* Tex = ( Vector2f* )( ( *TexVertexElement )[0] );

		for ( int i = 0; i < Faces.size(); i++ )
		{
			// 遍历每个面
			int index_1 = 3 * i + 0;
			int index_2 = 3 * i + 1;
			int index_3 = 3 * i + 2;

			// ---------------------第一个顶点------------------------
			Tex[index_1].x = Texcoords[Faces[i].CoordinateIndices[0]].x;
			Tex[index_1].y = Texcoords[Faces[i].CoordinateIndices[0]].y;

			// ---------------------第二个顶点------------------------------
			Tex[index_2].x = Texcoords[Faces[i].CoordinateIndices[1]].x;
			Tex[index_2].y = Texcoords[Faces[i].CoordinateIndices[1]].y;

			// ---------------------第三个顶点------------------------------
			Tex[index_3].x = Texcoords[Faces[i].CoordinateIndices[2]].x;
			Tex[index_3].y = Texcoords[Faces[i].CoordinateIndices[2]].y;
		}
	}
	MeshPtr->AddElement( TexVertexElement );


	VertexElement* NormalVertexElement = new VertexElement( 3 , Faces.size() * 3 );
	NormalVertexElement->m_SemanticName = VertexElement::NormalSemantic;
	NormalVertexElement->m_uiSemanticIndex = 0;
	NormalVertexElement->m_Format = DXGI_FORMAT_R32G32B32_FLOAT;
	NormalVertexElement->m_uiInputSlot = 0;
	NormalVertexElement->m_uiAlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	NormalVertexElement->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	NormalVertexElement->m_uiInstanceDataStepRate = 0;

	if ( Normals.size() != 0 )
	{
		Vector3f* Normal = ( Vector3f* )( ( *NormalVertexElement )[0] );

		for ( int i = 0; i < Faces.size(); i++ )
		{
			// 遍历每个面
			int index_1 = 3 * i + 0;
			int index_2 = 3 * i + 1;
			int index_3 = 3 * i + 2;

			// ---------------------第一个顶点------------------------
			Normal[index_1].x = Normals[Faces[i].NormalIndices[0]].x;
			Normal[index_1].y = Normals[Faces[i].NormalIndices[0]].y;
			Normal[index_1].z = Normals[Faces[i].NormalIndices[0]].z;

			// ---------------------第二个顶点------------------------------
			Normal[index_2].x = Normals[Faces[i].NormalIndices[1]].x;
			Normal[index_2].y = Normals[Faces[i].NormalIndices[1]].y;
			Normal[index_2].z = Normals[Faces[i].NormalIndices[1]].z;

			// ---------------------第三个顶点------------------------------
			Normal[index_3].x = Normals[Faces[i].NormalIndices[2]].x;
			Normal[index_3].y = Normals[Faces[i].NormalIndices[2]].y;
			Normal[index_3].z = Normals[Faces[i].NormalIndices[2]].z;
			
			Normal[index_1].Normalize();
			Normal[index_2].Normalize();
			Normal[index_3].Normalize();
		}	
	}
	MeshPtr->AddElement( NormalVertexElement );


	for( int i = 0; i < Faces.size(); i++ )
	{
		// 添加面的索引
		MeshPtr->AddFace( 3 * i + 0 , 3 * i + 1 , 3 * i + 2 );
	}

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

GeometryPtr GeometryLoader::LoadOBJWithTexture( std::wstring& filename )
{
	// 构造文件绝对路径
	FileSystem fs;
	filename = fs.GetModelFolder() + filename;

	// 打开文件
	std::ifstream fin( filename , std::ios::in );
	if ( !fin.is_open() )
	{
		Log::Get().Write( L"open obj file failed!" );
		return nullptr;
	}

	// 用于保存顶点位置数据
	std::vector<Vector3f> Positions;
	// 用于保存顶点法线数据
	std::vector<Vector3f> Normals;
	// 用于保存顶点纹理数据
	std::vector<Vector2f> Texcoords;

	std::vector<OBJObject> Objects;

	std::vector<std::string> MaterialLibs;

	// 一行一行的读取数据
	std::string line;

	while ( std::getline( fin , line ) )
	{
		std::stringstream lineStream( line );
		std::string token;
		std::vector<std::string> tokenList;

		// 提取字符串
		while ( lineStream >> token )
		{
			tokenList.push_back( token );
		}

		if ( tokenList.size() != 0 )
		{
			// 顶点数据
			if ( tokenList[0] == "v" )
			{
				Positions.emplace_back( Vector3f( static_cast< float >( atof( tokenList[1].c_str() ) ) ,
					static_cast< float >( atof( tokenList[2].c_str() ) ) ,
					static_cast< float >( atof( tokenList[3].c_str() ) ) ) );
			}
			// 法线
			else if ( tokenList[0] == "vn" )
			{
				Normals.emplace_back( Vector3f( static_cast< float >( atof( tokenList[1].c_str() ) ) ,
					static_cast< float >( atof( tokenList[2].c_str() ) ) ,
					static_cast< float >( atof( tokenList[3].c_str() ) ) ) );
			}
			else if ( tokenList[0] == "vt" )
			{
				Texcoords.emplace_back( Vector2f( static_cast< float >( atof( tokenList[1].c_str() ) ) ,
					static_cast< float >( atof( tokenList[2].c_str() ) ) ) );
			}
			else if ( tokenList[0] == "f" )
			{
				OBJFace face;

				for ( int i = 0; i < 3; i++ )
				{
					// 使用'/'作为分隔符，将数据提取出来
					auto triple = ToIndexTriple( tokenList[i + 1] );

					face.PositionIndices[i] = triple[0];
					face.CoordinateIndices[i] = triple[1];
					face.NormalIndices[i] = triple[2];
				}

				if ( Objects.size() == 0 )
				{
					Objects.push_back( OBJObject() );
					Objects.back().SubObjects.push_back( OBJSubObject() );
				}

				assert( Objects.back().SubObjects.size() > 0 );
				Objects.back().SubObjects.back().Faces.emplace_back( face );
			}
			else if ( tokenList[0] == "o" )
			{
				if ( Objects.size() == 1 && Objects.back().SubObjects.back().Faces.size() == 0 )
				{
					// 该object为默认的object
					Objects.back().name = tokenList[1];
				}
				else
				{
					Objects.push_back( OBJObject() );
					Objects.back().name = tokenList[1];
				}
			}
			else if ( tokenList[0] == "mtllib" )
			{
				MaterialLibs.push_back( line.substr( 7 ) );
			}
			else if ( tokenList[0] == "usemtl" )
			{
				if ( Objects.size() == 0 )
				{
					Objects.push_back( OBJObject() );
				}
				
				// 添加一个SubObject
				Objects.back().SubObjects.push_back( OBJSubObject() );
				Objects.back().SubObjects.back().MaterialName = line.substr( 7 );
			}
		}
	}

	fin.close();


	// -------------------------------------解析MTL----------------------------------------------
	std::map<std::string , ResourceProxyPtr> mtlLibs;
	for ( std::vector<std::string>::iterator iter = MaterialLibs.begin(); iter != MaterialLibs.end(); iter++ )
	{
		std::wstring MTLFilename = fs.GetModelFolder() + SandString::ToUnicode( *iter );
		std::ifstream fin( MTLFilename , std::ios::in );
		if ( !fin.is_open() )
		{
			Log::Get().Write( L"open obj file failed!" );
			return nullptr;
		}

		// 一行一行的读取数据
		std::string line;

		std::string MaterialName;

		while ( std::getline( fin , line ) )
		{
			std::stringstream lineStream( line );
			std::string token;
			std::vector<std::string> tokenList;

			// 提取字符串
			while ( lineStream >> token )
			{
				tokenList.push_back( token );
			}

			if ( tokenList.size() != 0 )
			{
				if ( tokenList[0] == "newmtl" )
				{
					MaterialName = tokenList[1];
				}
				else if ( tokenList[0] == "Ka" )
				{

				}
				else if ( tokenList[0] == "Kd" )
				{

				}
				else if ( tokenList[0] == "Ks" )
				{

				}
				else if ( tokenList[0] == "Tr" )
				{

				}
				else if ( tokenList[0] == "illum" )
				{

				}
				else if ( tokenList[0] == "Ns" )
				{

				}
				else if ( tokenList[0] == "map_Kd" )
				{
					mtlLibs[MaterialName] = Renderer::Get()->LoadTexture( SandString::ToUnicode( tokenList[1] ) );
				}
			}
		}

		fin.close();
	}

	GeometryPtr MeshPtr = GeometryPtr( new Geometry );

	ResourceProxyPtr DiffuseMap;
	int Offset = 0;
	int Count = 0;
	for ( int i = 0; i < Objects.size(); i++ )
	{
		for ( int j = 0; j < Objects[i].SubObjects.size(); j++ )
		{
			Offset += Count;

			Count = Objects[i].SubObjects[j].Faces.size() * 3;

			if ( Objects[i].SubObjects[j].MaterialName != "" )
			{
				DiffuseMap = mtlLibs[Objects[i].SubObjects[j].MaterialName];
			}
			else
			{
				DiffuseMap = ResourceProxyPtr( new ResourceProxy );
			}

			MeshPtr->AddInputResource( Offset , Count , DiffuseMap );
		}
	}

	// 顶点总数(按照三角形重排后的顶点总数)
	int TotalVertexCount = Offset + Count;

	VertexElement* PosVertexElement = new VertexElement( 3 , TotalVertexCount );
	PosVertexElement->m_SemanticName = VertexElement::PositionSemantic;
	PosVertexElement->m_uiSemanticIndex = 0;
	PosVertexElement->m_Format = DXGI_FORMAT_R32G32B32_FLOAT;
	PosVertexElement->m_uiInputSlot = 0;
	PosVertexElement->m_uiAlignedByteOffset = 0;
	PosVertexElement->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	PosVertexElement->m_uiInstanceDataStepRate = 0;

	if ( Positions.size() != 0 )
	{
		Vector3f* Pos = ( Vector3f* )( ( *PosVertexElement )[0] );

		int FaceCount = 0;
		for ( int i = 0; i < Objects.size(); i++ )
		{
			for ( int j = 0; j < Objects[i].SubObjects.size(); j++ )
			{
				for ( int k = 0; k < Objects[i].SubObjects[j].Faces.size(); k++ )
				{
					int index_1 = FaceCount * 3 + 3 * k + 0;
					int index_2 = index_1 + 1;
					int index_3 = index_2 + 1;

					int PosIndex_1 = Objects[i].SubObjects[j].Faces[k].PositionIndices[0];
					int PosIndex_2 = Objects[i].SubObjects[j].Faces[k].PositionIndices[1];
					int PosIndex_3 = Objects[i].SubObjects[j].Faces[k].PositionIndices[2];

					// ---------------------第一个顶点------------------------
					Pos[index_1].x = Positions[PosIndex_1].x;
					Pos[index_1].y = Positions[PosIndex_1].y;
					Pos[index_1].z = Positions[PosIndex_1].z;

					// ---------------------第二个顶点------------------------------
					Pos[index_2].x = Positions[PosIndex_2].x;
					Pos[index_2].y = Positions[PosIndex_2].y;
					Pos[index_2].z = Positions[PosIndex_2].z;

					// ---------------------第三个顶点------------------------------
					Pos[index_3].x = Positions[PosIndex_3].x;
					Pos[index_3].y = Positions[PosIndex_3].y;
					Pos[index_3].z = Positions[PosIndex_3].z;
				}

				FaceCount += Objects[i].SubObjects[j].Faces.size();
			}
		}
	}

	MeshPtr->AddElement( PosVertexElement );


	VertexElement* TexVertexElement = TexVertexElement = new VertexElement( 2 , TotalVertexCount );
	TexVertexElement->m_SemanticName = VertexElement::TexCoordSemantic;
	TexVertexElement->m_uiSemanticIndex = 0;
	TexVertexElement->m_Format = DXGI_FORMAT_R32G32_FLOAT;
	TexVertexElement->m_uiInputSlot = 0;
	TexVertexElement->m_uiAlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	TexVertexElement->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	TexVertexElement->m_uiInstanceDataStepRate = 0;

	if ( Texcoords.size() != 0 )
	{
		Vector2f* Tex = ( Vector2f* )( ( *TexVertexElement )[0] );

		int FaceCount = 0;
		for ( int i = 0; i < Objects.size(); i++ )
		{
			for ( int j = 0; j < Objects[i].SubObjects.size(); j++ )
			{
				for ( int k = 0; k < Objects[i].SubObjects[j].Faces.size(); k++ )
				{
					int index_1 = FaceCount * 3 + 3 * k + 0;
					int index_2 = index_1 + 1;
					int index_3 = index_2 + 1;

					int TexIndex_1 = Objects[i].SubObjects[j].Faces[k].CoordinateIndices[0];
					int TexIndex_2 = Objects[i].SubObjects[j].Faces[k].CoordinateIndices[1];
					int TexIndex_3 = Objects[i].SubObjects[j].Faces[k].CoordinateIndices[2];

					// ---------------------第一个顶点------------------------
					Tex[index_1].x = Texcoords[TexIndex_1].x;
					Tex[index_1].y = Texcoords[TexIndex_1].y;

					// ---------------------第二个顶点------------------------------
					Tex[index_2].x = Texcoords[TexIndex_2].x;
					Tex[index_2].y = Texcoords[TexIndex_2].y;

					// ---------------------第三个顶点------------------------------
					Tex[index_3].x = Texcoords[TexIndex_3].x;
					Tex[index_3].y = Texcoords[TexIndex_3].y;
				}

				FaceCount += Objects[i].SubObjects[j].Faces.size();
			}
		}
	}
	MeshPtr->AddElement( TexVertexElement );


	VertexElement* NormalVertexElement = new VertexElement( 3 , TotalVertexCount );
	NormalVertexElement->m_SemanticName = VertexElement::NormalSemantic;
	NormalVertexElement->m_uiSemanticIndex = 0;
	NormalVertexElement->m_Format = DXGI_FORMAT_R32G32B32_FLOAT;
	NormalVertexElement->m_uiInputSlot = 0;
	NormalVertexElement->m_uiAlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	NormalVertexElement->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	NormalVertexElement->m_uiInstanceDataStepRate = 0;

	if ( Normals.size() != 0 )
	{
		Vector3f* Normal = ( Vector3f* )( ( *NormalVertexElement )[0] );

		int FaceCount = 0;
		for ( int i = 0; i < Objects.size(); i++ )
		{
			for ( int j = 0; j < Objects[i].SubObjects.size(); j++ )
			{
				for ( int k = 0; k < Objects[i].SubObjects[j].Faces.size(); k++ )
				{
					int index_1 = FaceCount * 3 + 3 * k + 0;
					int index_2 = index_1 + 1;
					int index_3 = index_2 + 1;

					int NormalIndex_1 = Objects[i].SubObjects[j].Faces[k].NormalIndices[0];
					int NormalIndex_2 = Objects[i].SubObjects[j].Faces[k].NormalIndices[1];
					int NormalIndex_3 = Objects[i].SubObjects[j].Faces[k].NormalIndices[2];

					// ---------------------第一个顶点------------------------
					Normal[index_1].x = Normals[NormalIndex_1].x;
					Normal[index_1].y = Normals[NormalIndex_1].y;
					Normal[index_1].z = Normals[NormalIndex_1].z;

					// ---------------------第二个顶点------------------------------
					Normal[index_2].x = Normals[NormalIndex_2].x;
					Normal[index_2].y = Normals[NormalIndex_2].y;
					Normal[index_2].z = Normals[NormalIndex_2].z;

					// ---------------------第三个顶点------------------------------
					Normal[index_3].x = Normals[NormalIndex_3].x;
					Normal[index_3].y = Normals[NormalIndex_3].y;
					Normal[index_3].z = Normals[NormalIndex_3].z;

					Normal[index_1].Normalize();
					Normal[index_2].Normalize();
					Normal[index_3].Normalize();
				}

				FaceCount += Objects[i].SubObjects[j].Faces.size();
			}
		}
	}
	MeshPtr->AddElement( NormalVertexElement );


	// -------------------------------------------------------索引-----------------------------------------------------------
	int FaceCount = 0;
	for ( int i = 0; i < Objects.size(); i++ )
	{
		for ( int j = 0; j < Objects[i].SubObjects.size(); j++ )
		{
			for ( int k = 0; k < Objects[i].SubObjects[j].Faces.size(); k++ )
			{
				// 添加面的索引
				MeshPtr->AddFace( FaceCount * 3 + 3 * k + 0 , FaceCount * 3 + 3 * k + 1 , FaceCount * 3 + 3 * k + 2 );
			}

			FaceCount += Objects[i].SubObjects[j].Faces.size();
		}
	}

	return MeshPtr;
}

GeometryPtr GeometryLoader::LoadMS3D( std::wstring filename )
{
	FileSystem fs;
	filename = fs.GetModelFolder() + filename;

	unsigned short VertexCount = 0;
	unsigned short TriangleCount = 0;
	unsigned short GroupCount = 0;
	unsigned short MaterialCount = 0;

	MS3DVertex* pMS3DVertices = nullptr;
	MS3DTriangle* pMS3DTriangles = nullptr;
	MS3DGroup* pMS3DGroups = nullptr;
	MS3DMaterial* pMS3DMaterials = nullptr;

	std::ifstream fin;
	MS3DHeader Header;

	fin.open( filename.c_str() , std::ios::binary );
	
	// 读取Header数据
	fin.read( ( char* )( &( Header.ID ) ) , sizeof( Header.ID ) );
	fin.read( ( char* )( &( Header.Version ) ) , sizeof( Header.Version ) );
	if( Header.Version != 3 && Header.Version != 4 )
	{
		return nullptr;
	}

	// 加载顶点数据
	fin.read( ( char* )( &VertexCount ) , sizeof( unsigned short ) );
	pMS3DVertices = new MS3DVertex[VertexCount];
	for( int i = 0; i < VertexCount; i++ )
	{
		fin.read( ( char* )( &( pMS3DVertices[i].Flags ) ) , sizeof( unsigned char ) );
		fin.read( ( char* )( &( pMS3DVertices[i].Vertex[0] ) ) , sizeof( float ) );
		fin.read( ( char* )( &( pMS3DVertices[i].Vertex[1] ) ) , sizeof( float ) );
		fin.read( ( char* )( &( pMS3DVertices[i].Vertex[2] ) ) , sizeof( float ) );
		fin.read( ( char* )( &( pMS3DVertices[i].BoneID ) ) , sizeof( char ) );
		fin.read( ( char* )( &( pMS3DVertices[i].ReferenceCount ) ) , sizeof( unsigned char ) );
	}


	// 加载所有的三角形索引
	fin.read( ( char* )( &TriangleCount ) , sizeof( unsigned short ) );
	pMS3DTriangles = new MS3DTriangle[TriangleCount];
	for( int i = 0; i < TriangleCount; i++ )
	{
		fin.read( ( char* )( &( pMS3DTriangles[i].Flags ) ) , sizeof( unsigned short ) );
		fin.read( ( char* )( &( pMS3DTriangles[i].VertexIndices[0] ) ) , sizeof( unsigned short ) );
		fin.read( ( char* )( &( pMS3DTriangles[i].VertexIndices[1] ) ) , sizeof( unsigned short ) );
		fin.read( ( char* )( &( pMS3DTriangles[i].VertexIndices[2] ) ) , sizeof( unsigned short ) );
		fin.read( ( char* )( &( pMS3DTriangles[i].VertexNormals[0] ) ) , 3 * sizeof( float ) );
		fin.read( ( char* )( &( pMS3DTriangles[i].VertexNormals[1] ) ) , 3 * sizeof( float ) );
		fin.read( ( char* )( &( pMS3DTriangles[i].VertexNormals[2] ) ) , 3 * sizeof( float ) );
		fin.read( ( char* )( &( pMS3DTriangles[i].S ) ) , 3 * sizeof( float ) );
		fin.read( ( char* )( &( pMS3DTriangles[i].T ) ) , 3 * sizeof( float ) );
		fin.read( ( char* )( &( pMS3DTriangles[i].SmoothingGroup ) ) , sizeof( unsigned char ) );
		fin.read( ( char* )( &( pMS3DTriangles[i].GroupIndex ) ) , sizeof( unsigned char ) );
	}

	// 加载所有的Group信息
	fin.read( ( char* )( &GroupCount ) , sizeof( unsigned short ) );
	pMS3DGroups = new MS3DGroup[GroupCount];
	for( int i = 0; i < GroupCount; i++ )
	{
		fin.read( ( char* )( &( pMS3DGroups[i].Flags ) ) , sizeof( unsigned char ) );
		fin.read( ( char* )( &( pMS3DGroups[i].Name ) ) , sizeof( char[32] ) );
		fin.read( ( char* )( &( pMS3DGroups[i].NumTriangles ) ) , sizeof( unsigned short ) );

		unsigned short TriCount = pMS3DGroups[i].NumTriangles;
		pMS3DGroups[i].TriangleIndices = new unsigned short[TriCount];
		fin.read( ( char* )( pMS3DGroups[i].TriangleIndices ) , sizeof( unsigned short ) * TriCount );
		fin.read( ( char* )( &( pMS3DGroups[i].MaterialIndex ) ) , sizeof( char ) );
	}

	// 加载所有的材质信息
	fin.read( ( char* )( &MaterialCount ) , sizeof( unsigned short ) );
	pMS3DMaterials = new MS3DMaterial[MaterialCount];
	for( int i = 0; i < MaterialCount; i++ )
	{
		fin.read( ( char* )( &( pMS3DMaterials[i].Name ) ) , sizeof( char[32] ) );
		fin.read( ( char* )( &( pMS3DMaterials[i].Ambient ) ) , 4 * sizeof( float ) );
		fin.read( ( char* )( &( pMS3DMaterials[i].Diffuse ) ) , 4 * sizeof( float ) );
		fin.read( ( char* )( &( pMS3DMaterials[i].Specular ) ) , 4 * sizeof( float ) );
		fin.read( ( char* )( &( pMS3DMaterials[i].Emissive ) ) , 4 * sizeof( float ) );
		fin.read( ( char* )( &( pMS3DMaterials[i].Shininess ) ) , sizeof( float ) );
		fin.read( ( char* )( &( pMS3DMaterials[i].Transparency ) ) , sizeof( float ) );
		fin.read( ( char* )( &( pMS3DMaterials[i].Mode ) ) , sizeof( char ) );
		fin.read( ( char* )( &( pMS3DMaterials[i].Texture ) ) , sizeof( char[128] ) );
		fin.read( ( char* )( &( pMS3DMaterials[i].AlphaMap ) ) , sizeof( char[128] ) );
	}

	fin.close();

	VertexElement* pPosition = new VertexElement( 3 , TriangleCount * 3 );
	pPosition->m_SemanticName = VertexElement::PositionSemantic;
	pPosition->m_uiSemanticIndex = 0;
	pPosition->m_Format = DXGI_FORMAT_R32G32B32_FLOAT;
	pPosition->m_uiInputSlot = 0;
	pPosition->m_uiAlignedByteOffset = 0;
	pPosition->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	pPosition->m_uiInstanceDataStepRate = 0;

	VertexElement* pTexcoords = new VertexElement( 2 , TriangleCount * 3 );
	pTexcoords->m_SemanticName = VertexElement::TexCoordSemantic;
	pTexcoords->m_uiSemanticIndex = 0;
	pTexcoords->m_Format = DXGI_FORMAT_R32G32_FLOAT;
	pTexcoords->m_uiInputSlot = 0;
	pTexcoords->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	pTexcoords->m_uiAlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	pTexcoords->m_uiInstanceDataStepRate = 0;

	VertexElement* pNormals = new VertexElement( 3 , TriangleCount * 3 );
	pNormals->m_SemanticName = VertexElement::NormalSemantic;
	pNormals->m_uiSemanticIndex = 0;
	pNormals->m_Format = DXGI_FORMAT_R32G32B32_FLOAT;
	pNormals->m_uiInputSlot = 0;
	pNormals->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	pNormals->m_uiAlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	pNormals->m_uiInstanceDataStepRate = 0;

	Vector3f* pPos = ( Vector3f* )( ( *pPosition )[0] );
	Vector3f* pNormal = ( Vector3f* )( ( *pNormals )[0] );
	Vector2f* pTex = ( Vector2f* )( ( *pTexcoords )[0] );

	GeometryPtr MeshPtr = GeometryPtr( new Geometry );

	for( int i = 0; i < TriangleCount; i++ )
	{
		// --------------------三角形的第一个顶点----------------------
		pPos[3 * i + 0].x = pMS3DVertices[pMS3DTriangles[i].VertexIndices[0]].Vertex[0];
		pPos[3 * i + 0].y = pMS3DVertices[pMS3DTriangles[i].VertexIndices[0]].Vertex[1];
		pPos[3 * i + 0].z = -pMS3DVertices[pMS3DTriangles[i].VertexIndices[0]].Vertex[2];

		pTex[3 * i + 0].x = pMS3DTriangles[i].S[0];
		pTex[3 * i + 0].y = pMS3DTriangles[i].T[0];

		pNormal[3 * i + 0].x = pMS3DTriangles[i].VertexNormals[0][0];
		pNormal[3 * i + 0].y = pMS3DTriangles[i].VertexNormals[0][1];
		pNormal[3 * i + 0].z = -pMS3DTriangles[i].VertexNormals[0][2];

		// ------------------三角形的第二个顶点--------------------------------
		pPos[3 * i + 1].x = pMS3DVertices[pMS3DTriangles[i].VertexIndices[1]].Vertex[0];
		pPos[3 * i + 1].y = pMS3DVertices[pMS3DTriangles[i].VertexIndices[1]].Vertex[1];
		pPos[3 * i + 1].z = -pMS3DVertices[pMS3DTriangles[i].VertexIndices[1]].Vertex[2];

		pTex[3 * i + 1].x = pMS3DTriangles[i].S[1];
		pTex[3 * i + 1].y = pMS3DTriangles[i].T[1];

		pNormal[3 * i + 1].x = pMS3DTriangles[i].VertexNormals[1][0];
		pNormal[3 * i + 1].y = pMS3DTriangles[i].VertexNormals[1][1];
		pNormal[3 * i + 1].z = -pMS3DTriangles[i].VertexNormals[1][2];

		// ------------------三角形的第三个顶点----------------------------------
		pPos[3 * i + 2].x = pMS3DVertices[pMS3DTriangles[i].VertexIndices[2]].Vertex[0];
		pPos[3 * i + 2].y = pMS3DVertices[pMS3DTriangles[i].VertexIndices[2]].Vertex[1];
		pPos[3 * i + 2].z = -pMS3DVertices[pMS3DTriangles[i].VertexIndices[2]].Vertex[2];

		pTex[3 * i + 2].x = pMS3DTriangles[i].S[2];
		pTex[3 * i + 2].y = pMS3DTriangles[i].T[2];

		pNormal[3 * i + 2].x = pMS3DTriangles[i].VertexNormals[2][0];
		pNormal[3 * i + 2].y = pMS3DTriangles[i].VertexNormals[2][1];
		pNormal[3 * i + 2].z = -pMS3DTriangles[i].VertexNormals[2][2];

		MeshPtr->AddFace( 3 * i + 0 , 3 * i + 2 , 3 * i + 1 );
	}

	// normalize
	for( int i = 0; i < TriangleCount * 3; i++ )
	{
		pNormal[i].Normalize();
	}

	MeshPtr->AddElement( pPosition );
	MeshPtr->AddElement( pTexcoords );
	MeshPtr->AddElement( pNormals );

	if( pMS3DMaterials != nullptr )
	{
		delete[] pMS3DMaterials;
		pMS3DMaterials = nullptr;
	}

	if( pMS3DGroups != nullptr )
	{
		for( int i = 0; i < GroupCount; i++ )
		{
			if( pMS3DGroups[i].TriangleIndices != nullptr )
			{
				delete[] pMS3DGroups[i].TriangleIndices;
				pMS3DGroups[i].TriangleIndices = nullptr;
			}
		}

		delete[] pMS3DGroups;

		pMS3DGroups = nullptr;
	}

	if( pMS3DTriangles != nullptr )
	{
		delete[] pMS3DTriangles;
		pMS3DTriangles = nullptr;
	}

	if( pMS3DVertices != nullptr )
	{
		delete[] pMS3DVertices;
		pMS3DVertices = nullptr;
	}

	return MeshPtr;
}