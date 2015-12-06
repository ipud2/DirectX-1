#include "PCH.h"
#include "GeometryGenerator.h"
#include "Log.h"
#include "Vector4f.h"

using namespace Sand;

GeometryGenerator::GeometryGenerator()
{


}

void GeometryGenerator::GeneratorFullScreenQuad( GeometryPtr pGeometry )
{
	if( pGeometry == nullptr )
	{
		Log::Get().Write( L"��ͼ��һ��null geometry����������ȫ����" );
		return;
	}

	VertexElement* pClipSpacePosition = new VertexElement( 4 , 4 );
	pClipSpacePosition->m_SemanticName = "POSITION";
	pClipSpacePosition->m_uiSemanticIndex = 0;
	pClipSpacePosition->m_Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	pClipSpacePosition->m_uiInputSlot = 0;
	pClipSpacePosition->m_uiAlignedByteOffset = 0;
	pClipSpacePosition->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	pClipSpacePosition->m_uiInstanceDataStepRate = 0;

	VertexElement* pTexCoords = new VertexElement( 2 , 4 );
	pTexCoords->m_SemanticName = "TEXCOORDS";
	pTexCoords->m_uiSemanticIndex = 0;
	pTexCoords->m_Format = DXGI_FORMAT_R32G32_FLOAT;
	pTexCoords->m_uiInputSlot = 0;
	pTexCoords->m_uiAlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	pTexCoords->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	pTexCoords->m_uiInstanceDataStepRate = 0;

	Vector4f* pPos = pClipSpacePosition->Get4fTupleDataPtr( 0 );
	Vector2f* pTex = pTexCoords->Get2fTupleDataPtr( 0 );

	pPos[0] = Vector4f( -1.0f , 1.0f , 0.0f , 1.0f );	// ���Ͻ�
	pPos[1] = Vector4f( -1.0f , -1.0f , 0.0f , 1.0f );	// ���½�
	pPos[2] = Vector4f(1.0f , 1.0f , 0.0f , 1.0f);		// ���Ͻ�
	pPos[3] = Vector4f( 1.0f , -1.0f , 0.0f , 1.0f );	// ���½�

	pTex[0] = Vector2f( 0.0f , 0.0f );
	pTex[1] = Vector2f( 0.0f , 1.0f );
	pTex[2] = Vector2f( 1.0f , 0.0f );
	pTex[3] = Vector2f( 1.0f , 1.0f );

	pGeometry->AddElement( pClipSpacePosition );
	pGeometry->AddElement( pTexCoords );

	// �������
	pGeometry->AddFace( 0 , 2 , 1 );

	pGeometry->AddFace( 1 , 2 , 3 );
}

void GeometryGenerator::GeneratorTexturedPlane( GeometryPtr pGeometry , int SizeX , int SizeY )
{
	if( pGeometry == nullptr )
	{
		return;
	}

	VertexElement* pPosition = new VertexElement( 3 , SizeX * SizeY );
	pPosition->m_SemanticName = "POSITION";
	pPosition->m_uiSemanticIndex = 0;
	pPosition->m_Format = DXGI_FORMAT_R32G32B32_FLOAT;
	pPosition->m_uiInputSlot = 0;
	pPosition->m_uiAlignedByteOffset = 0;
	pPosition->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	pPosition->m_uiInstanceDataStepRate = 0;

	VertexElement* pTexCoords = new VertexElement( 2 , SizeX * SizeY );
	pTexCoords->m_SemanticName = "TEXCOORDS";
	pTexCoords->m_uiSemanticIndex = 0;
	pTexCoords->m_Format = DXGI_FORMAT_R32G32_FLOAT;
	pTexCoords->m_uiInputSlot = 0;
	pTexCoords->m_uiAlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	pTexCoords->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	pTexCoords->m_uiInstanceDataStepRate = 0;

	Vector3f* pPos = pPosition->Get3fTupleDataPtr( 0 );
	Vector2f* pTex = pTexCoords->Get2fTupleDataPtr( 0 );

	for( int y = 0; y < SizeY; y++ )
	{
		for( int x = 0; x < SizeX; x++ )
		{
			pPos[y * SizeX + x] = Vector3f( ( float )x , 0.0f , ( float )y );
			pTex[y * SizeX + x] = Vector2f( ( float )x , ( float )y );
		}
	}


	// ��������
	for( int j = 0; j < SizeY - 1; j++ )
	{
		for( int i = 0; i < SizeX - 1; i++ )
		{
			pGeometry->AddFace( j * SizeX + i , j * SizeX + i + 1 , ( j + 1 ) * SizeX + i );

			pGeometry->AddFace( ( j + 1 ) * SizeX + i , j * SizeX + i + 1 , ( j + 1 ) * SizeX + i + 1 );
		}
	}

	pGeometry->AddElement( pPosition );
	pGeometry->AddElement( pTexCoords );
}

/*
	����������
*/
void GeometryGenerator::GeneratorAxisGeometry( GeometryPtr pGeometry )
{
	if( pGeometry == nullptr )
	{
		return;
	}

	VertexElement* pPosition = new VertexElement( 3 , 5 * 3 );
	pPosition->m_SemanticName = "POSITION";
	pPosition->m_uiSemanticIndex = 0;
	pPosition->m_Format = DXGI_FORMAT_R32G32B32_FLOAT;
	pPosition->m_uiInputSlot = 0;
	pPosition->m_uiAlignedByteOffset = 0;
	pPosition->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	pPosition->m_uiInstanceDataStepRate = 0;

	VertexElement* pColors = new VertexElement( 4 , 5 * 3 );
	pColors->m_SemanticName = "COLOR";
	pColors->m_uiSemanticIndex = 0;
	pColors->m_Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	pColors->m_uiAlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	pColors->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	pColors->m_uiInstanceDataStepRate = 0;

	Vector3f* pPos = pPosition->Get3fTupleDataPtr( 0 );
	Vector4f* pColor = pColors->Get4fTupleDataPtr( 0 );

	float fThickness = 0.05f;
	float fLength = 3.0f;

	// ��ɫ
	Vector4f XBase = Vector4f( 1.0f , 0.0f , 0.0f , 1.0f );
	Vector4f XEnd = Vector4f( 1.0f , 0.0f , 0.0f , 1.0f );
	Vector4f YBase = Vector4f( 0.0f , 1.0f , 0.0f , 1.0f );
	Vector4f YEnd = Vector4f( 0.0f , 1.0f , 0.0f , 1.0f );
	Vector4f ZBase = Vector4f( 0.0f , 0.0f , 1.0f , 1.0f );
	Vector4f ZEnd = Vector4f( 0.0f , 0.0f , 1.0f , 1.0f );

	// ---------------X��-----------------
	// ����x = 0������һ���ǳ�С�������ε��ĸ���
	// Ȼ����x����length������һ����
	// Ȼ��ÿ�����Ǻ͸õ��������һ�������Σ������γ��ɴֱ�ϸ�������״
	pPos[0] = Vector3f( 0.0f , fThickness , fThickness );
	pColor[0] = XBase;

	pPos[1] = Vector3f( 0.0f , -fThickness , fThickness );
	pColor[1] = XBase;

	pPos[2] = Vector3f( 0.0f , -fThickness , -fThickness );
	pColor[2] = XBase;

	pPos[3] = Vector3f( 0.0f , fThickness , -fThickness );
	pColor[3] = XBase;

	pPos[4] = Vector3f( fLength , 0.0f , 0.0f );
	pColor[4] = XEnd;


	// ----------------------Y��----------------------
	pPos[5] = Vector3f( fThickness , 0.0f , fThickness );
	pColor[5] = YBase;

	pPos[6] = Vector3f( -fThickness , 0.0f , fThickness );
	pColor[6] = YBase;

	pPos[7] = Vector3f( -fThickness , 0.0f , -fThickness );
	pColor[7] = YBase;

	pPos[8] = Vector3f( fThickness , 0.0f , -fThickness );
	pColor[8] = YBase;

	pPos[9] = Vector3f( 0.0f , fLength , 0.0f );
	pColor[9] = YEnd;


	// -------------------Z��----------------------
	pPos[10] = Vector3f( fThickness , fThickness , 0.0f );
	pColor[10] = ZBase;

	pPos[11] = Vector3f( -fThickness , fThickness , 0.0f );
	pColor[11] = ZBase;

	pPos[12] = Vector3f( -fThickness , -fThickness , 0.0f );
	pColor[12] = ZBase;

	pPos[13] = Vector3f( fThickness , -fThickness , 0.0f );
	pColor[13] = ZBase;

	pPos[14] = Vector3f( 0.0f , 0.0f , fLength );
	pColor[14] = ZEnd;

	pGeometry->AddElement( pPosition );
	pGeometry->AddElement( pColors );

	pGeometry->AddFace( 0 , 1 , 4 );
	pGeometry->AddFace( 1 , 2 , 4 );
	pGeometry->AddFace( 2 , 3 , 4 );
	pGeometry->AddFace( 3 , 0 , 4 );

	pGeometry->AddFace( 5 , 6 , 9 );
	pGeometry->AddFace( 6 , 7 , 9 );
	pGeometry->AddFace( 7 , 8 , 9 );
	pGeometry->AddFace( 8 , 5 , 9 );

	pGeometry->AddFace( 10 , 11 , 14 );
	pGeometry->AddFace( 11 , 12 , 14 );
	pGeometry->AddFace( 12 , 13 , 14 );
	pGeometry->AddFace( 13 , 10 , 14 );
}

void GeometryGenerator::GeneratorSphere( GeometryPtr pGeometry , unsigned int SliceCount , unsigned int StackCount , float Radius )
{
	if( pGeometry == nullptr )
	{
		return;
	}

	float phiStep = 3.1415926f / StackCount;
	float thetaStep = 2.0f * 3.1415926f / SliceCount;

	//������ϵ��º��г�stackCountƬ
	//ÿ�����涼��һ��Բ
	//Ȼ�����ǽ����Բ��ΪsliceCount��
	//Ȼ�����ÿ���������
	//ͨ����������������
	//ʹ����������Ҫ֪���뾶������ֱ�������ļн�
	//�ڵ����ͶӰ��x�ļн�

	unsigned int NumVertexs = ( StackCount - 1 ) * ( SliceCount + 1 ) + 2;

	VertexElement* pPosition = new VertexElement( 3 , NumVertexs );
	pPosition->m_SemanticName = "POSITION";
	pPosition->m_uiSemanticIndex = 0;
	pPosition->m_Format = DXGI_FORMAT_R32G32B32_FLOAT;
	pPosition->m_uiInputSlot = 0;
	pPosition->m_uiAlignedByteOffset = 0;
	pPosition->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	pPosition->m_uiInstanceDataStepRate = 0;

	VertexElement* pNormals = new VertexElement( 3 , NumVertexs );
	pNormals->m_SemanticName = "NORMAL";
	pNormals->m_uiSemanticIndex = 0;
	pNormals->m_Format = DXGI_FORMAT_R32G32B32_FLOAT;
	pNormals->m_uiInputSlot = 0;
	pNormals->m_uiAlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	pNormals->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	pNormals->m_uiInstanceDataStepRate = 0;

	VertexElement* pTangents = new VertexElement( 3 , NumVertexs );
	pTangents->m_SemanticName = "TANGENT";
	pTangents->m_uiSemanticIndex = 0;
	pTangents->m_Format = DXGI_FORMAT_R32G32B32_FLOAT;
	pTangents->m_uiInputSlot = 0;
	pTangents->m_uiAlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	pTangents->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	pTangents->m_uiInstanceDataStepRate = 0;

	VertexElement* pTexCoords = new VertexElement( 2 , NumVertexs );
	pTexCoords->m_SemanticName = "TEXCOORD";
	pTexCoords->m_uiSemanticIndex = 0;
	pTexCoords->m_Format = DXGI_FORMAT_R32G32_FLOAT;
	pTexCoords->m_uiInputSlot = 0;
	pTexCoords->m_uiAlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	pTexCoords->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	pTexCoords->m_uiInstanceDataStepRate = 0;

	Vector3f* pVertex = pPosition->Get3fTupleDataPtr( 0 );
	Vector3f* pNormal = pNormals->Get3fTupleDataPtr( 0 );
	Vector3f* pTangent = pTangents->Get3fTupleDataPtr( 0 );
	Vector2f* pTex = pTexCoords->Get2fTupleDataPtr( 0 );


	pVertex[0] = Vector3f( 0.0f , Radius , 0.0f );
	pNormal[0] = Vector3f( 0.0f , 1.0f , 0.0f );
	pTangent[0] = Vector3f( 1.0f , 0.0f , 0.0f );
	pTex[0] = Vector2f( 0.0f , 0.0f );

	int CurrentVertex = 1;
	for( UINT i = 0; i <= StackCount - 1; ++i )
	{
		float phi = i * phiStep;

		for( UINT j = 0; j <= SliceCount; j++ )
		{
			float theta = j * thetaStep;

			pVertex[CurrentVertex] = Vector3f( Radius * sinf( phi ) * cosf( theta ) , Radius * cosf( phi ) , Radius * sinf( phi ) * sinf( theta ) );

			/*
				����ͨ���ɸ������ޱƽ����ߣ����ҽ�ϼ��ޣ��������Ƶ������ϵ�һ�����������
				�ɲμ���http://netedu.xauat.edu.cn/jpkc/netedu/jpkc/gdsx/homepage/5jxsd/51/513/5308/530806.htm
				��ˣ�Position����theta��ƫ������Ϊ��������
			*/
			pTangent[CurrentVertex] = Vector3f(-Radius * sinf(phi) * sinf(theta) , 0.0f , Radius * sinf(phi) * cosf(theta));
			pTangent[CurrentVertex].Normalize();		// ��һ��

			// ���߼�ΪԲ��ָ��õ����������˸պõ��ڵ��λ�������ֵ
			pNormal[CurrentVertex] = Vector3f( Radius * sinf( phi ) * cosf( theta ) , Radius * cosf( phi ) , Radius * sinf( phi ) * sinf( theta ) );
			pNormal[CurrentVertex].Normalize();

			pTex[CurrentVertex] = Vector2f( theta / ( 2 * 3.1415926f ) , phi / 3.1415926f );

			CurrentVertex++;
		}
	}

	pVertex[CurrentVertex] = Vector3f( 0.0f , -Radius , 0.0f );
	pTangent[CurrentVertex] = Vector3f( -1.0f , 0.0f , 0.0f );
	pNormal[CurrentVertex] = Vector3f( 0.0f , -1.0f , 0.0f );
	pTex[CurrentVertex] = Vector2f( 0.0f , 1.0f );

	// ��Ӷ���
	pGeometry->AddElement( pPosition );
	pGeometry->AddElement( pNormals );
	pGeometry->AddElement( pTangents );
	pGeometry->AddElement( pTexCoords );


	// ---------------�������------------------

	//������Ǹ�Բ�������ڵ�����������ߵĶ����������������
	for( UINT i = 1; i <= SliceCount; i++ )
	{
		//ע�ⷽ������i+1�ĵ����x������ƫ��ĽǶȱȵ�i����ƫ��ĽǶȸ�����˰���˳ʱ���ԭ��Ӧ����0��i+1��i
		pGeometry->AddFace( 0 , i + 1 , i );
	}

	//�����ڲ��Ļ������������һ��������Ϊ���һ�����ϵĵ��Ǻ���ײ��Ķ������������
	unsigned int baseIndex = 1;
	unsigned int ringVertexCount = SliceCount + 1;

	for( unsigned int i = 0; i < StackCount - 2; i++ )
	{
		for( unsigned int j = 0; j < SliceCount; j++ )
		{
			// ���ڵ�ǰ��������ֵΪj,j+1�����������һ����������ֵ��ͬ��������
			// ������������������Σ�������ߵ������ֵΪ0�����Դӵ�һ������ʼ
			// ��i��������ʼ����ֵΪ��i - 1��*(sliceCount + 1)��
			// ע���ǵ�i���������Ժ������i-1��ѭ����ʱ���0��ʼ��
			// ���Լ����ʱ����Ҫ��һ
			pGeometry->AddFace( baseIndex + i * ringVertexCount + j , baseIndex + i * ringVertexCount + j + 1 , baseIndex + ( i + 1 ) * ringVertexCount + j );

			pGeometry->AddFace( baseIndex + ( i + 1 ) * ringVertexCount + j , baseIndex + i * ringVertexCount + j + 1 , baseIndex + ( i + 1 ) * ringVertexCount + j + 1 );
		}
	}

	// ���һ����
	unsigned int SouthPoleIndex = ( unsigned int )CurrentVertex;

	// �����һ�����е�һ�����������ƫ��ֵ
	baseIndex = SouthPoleIndex - ringVertexCount;

	for( unsigned int i = 0; i < SliceCount; i++ )
	{
		pGeometry->AddFace( SouthPoleIndex , baseIndex + i , baseIndex + i + 1 );
	}
}

void GeometryGenerator::GeneratorSkyBox( GeometryPtr pGeometry , unsigned int SliceCount , unsigned int StackCount , float Radius )
{
	if ( pGeometry == nullptr )
	{
		return;
	}

	float phiStep = 3.1415926f / StackCount;
	float thetaStep = 2.0f * 3.1415926f / SliceCount;

	unsigned int NumVertexs = ( StackCount - 1 ) * ( SliceCount + 1 ) + 2;

	VertexElement* pPosition = new VertexElement( 3 , NumVertexs );
	pPosition->m_SemanticName = "POSITION";
	pPosition->m_uiSemanticIndex = 0;
	pPosition->m_Format = DXGI_FORMAT_R32G32B32_FLOAT;
	pPosition->m_uiInputSlot = 0;
	pPosition->m_uiAlignedByteOffset = 0;
	pPosition->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	pPosition->m_uiInstanceDataStepRate = 0;

	Vector3f* pVertex = ( Vector3f* )( ( *pPosition )[0] );/*pPosition->Get3fTupleDataPtr( 0 )*/;

	pVertex[0] = Vector3f( 0.0f , Radius , 0.0f );

	int CurrentVertex = 1;
	for ( UINT i = 1; i <= StackCount - 1; ++i )
	{
		float phi = i * phiStep;

		for ( UINT j = 0; j <= SliceCount; j++ )
		{
			float theta = j * thetaStep;

			pVertex[CurrentVertex++] = Vector3f( Radius * sinf( phi ) * cosf( theta ) , Radius * cosf( phi ) , Radius * sinf( phi ) * sinf( theta ) );
		}
	}

	pVertex[CurrentVertex] = Vector3f( 0.0f , -Radius , 0.0f );

	// ��Ӷ���
	pGeometry->AddElement( pPosition );


	// ---------------�������------------------

	//������Ǹ�Բ�������ڵ�����������ߵĶ����������������
	for ( UINT i = 1; i <= SliceCount; i++ )
	{
		//ע�ⷽ������i+1�ĵ����x������ƫ��ĽǶȱȵ�i����ƫ��ĽǶȸ�����˰���˳ʱ���ԭ��Ӧ����0��i+1��i
		pGeometry->AddFace( 0 , i + 1 , i );
	}

	//�����ڲ��Ļ������������һ��������Ϊ���һ�����ϵĵ��Ǻ���ײ��Ķ������������
	unsigned int baseIndex = 1;
	unsigned int ringVertexCount = SliceCount + 1;

	for ( unsigned int i = 0; i < StackCount - 2; i++ )
	{
		for ( unsigned int j = 0; j < SliceCount; j++ )
		{
			// ���ڵ�ǰ��������ֵΪj,j+1�����������һ����������ֵ��ͬ��������
			// ������������������Σ�������ߵ������ֵΪ0�����Դӵ�һ������ʼ
			// ��i��������ʼ����ֵΪ��i - 1��*(sliceCount + 1)��
			// ע���ǵ�i���������Ժ������i-1��ѭ����ʱ���0��ʼ��
			// ���Լ����ʱ����Ҫ��һ
			pGeometry->AddFace( baseIndex + i * ringVertexCount + j , baseIndex + i * ringVertexCount + j + 1 , baseIndex + ( i + 1 ) * ringVertexCount + j );

			pGeometry->AddFace( baseIndex + ( i + 1 ) * ringVertexCount + j , baseIndex + i * ringVertexCount + j + 1 , baseIndex + ( i + 1 ) * ringVertexCount + j + 1 );
		}
	}

	// ���һ����
	unsigned int SouthPoleIndex = ( unsigned int )CurrentVertex;

	// �����һ�����е�һ�����������ƫ��ֵ
	baseIndex = SouthPoleIndex - ringVertexCount;

	for ( unsigned int i = 0; i < SliceCount; i++ )
	{
		pGeometry->AddFace( SouthPoleIndex , baseIndex + i , baseIndex + i + 1 );
	}
}