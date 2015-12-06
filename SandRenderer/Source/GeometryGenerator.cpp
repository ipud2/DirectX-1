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
		Log::Get().Write( L"试图在一个null geometry对象中生成全屏块" );
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

	pPos[0] = Vector4f( -1.0f , 1.0f , 0.0f , 1.0f );	// 左上角
	pPos[1] = Vector4f( -1.0f , -1.0f , 0.0f , 1.0f );	// 左下角
	pPos[2] = Vector4f(1.0f , 1.0f , 0.0f , 1.0f);		// 右上角
	pPos[3] = Vector4f( 1.0f , -1.0f , 0.0f , 1.0f );	// 右下角

	pTex[0] = Vector2f( 0.0f , 0.0f );
	pTex[1] = Vector2f( 0.0f , 1.0f );
	pTex[2] = Vector2f( 1.0f , 0.0f );
	pTex[3] = Vector2f( 1.0f , 1.0f );

	pGeometry->AddElement( pClipSpacePosition );
	pGeometry->AddElement( pTexCoords );

	// 添加索引
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


	// 生成索引
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
	创建坐标轴
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

	// 颜色
	Vector4f XBase = Vector4f( 1.0f , 0.0f , 0.0f , 1.0f );
	Vector4f XEnd = Vector4f( 1.0f , 0.0f , 0.0f , 1.0f );
	Vector4f YBase = Vector4f( 0.0f , 1.0f , 0.0f , 1.0f );
	Vector4f YEnd = Vector4f( 0.0f , 1.0f , 0.0f , 1.0f );
	Vector4f ZBase = Vector4f( 0.0f , 0.0f , 1.0f , 1.0f );
	Vector4f ZEnd = Vector4f( 0.0f , 0.0f , 1.0f , 1.0f );

	// ---------------X轴-----------------
	// 先在x = 0处创建一个非常小的正方形的四个角
	// 然后在x轴上length处创建一个点
	// 然后每两个角和该点连接组成一个三角形，最终形成由粗变细的轴的形状
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


	// ----------------------Y轴----------------------
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


	// -------------------Z轴----------------------
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

	//将球从上到下横切成stackCount片
	//每个切面都是一个圆
	//然后我们将这个圆分为sliceCount份
	//然后求出每个点的坐标
	//通过球形坐标进行求解
	//使用球坐标需要知道半径，与竖直轴的正轴的夹角
	//在底面的投影与x的夹角

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
				可以通过由割线无限逼近切线，并且结合极限，来进行推导曲面上的一点的切线向量
				可参见：http://netedu.xauat.edu.cn/jpkc/netedu/jpkc/gdsx/homepage/5jxsd/51/513/5308/530806.htm
				因此：Position对于theta的偏导数作为切线坐标
			*/
			pTangent[CurrentVertex] = Vector3f(-Radius * sinf(phi) * sinf(theta) , 0.0f , Radius * sinf(phi) * cosf(theta));
			pTangent[CurrentVertex].Normalize();		// 归一化

			// 法线即为圆心指向该点的向量，因此刚好等于点的位置坐标的值
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

	// 添加顶点
	pGeometry->AddElement( pPosition );
	pGeometry->AddElement( pNormals );
	pGeometry->AddElement( pTangents );
	pGeometry->AddElement( pTexCoords );


	// ---------------添加索引------------------

	//将最顶上那个圆环的相邻的两个点与最高的顶点相连组成三角形
	for( UINT i = 1; i <= SliceCount; i++ )
	{
		//注意方向，由于i+1的点距离x轴正轴偏离的角度比第i个点偏离的角度更大，因此按照顺时针的原则应该是0，i+1，i
		pGeometry->AddFace( 0 , i + 1 , i );
	}

	//处理内部的环，不包括最后一个环，因为最后一个环上的点是和最底部的顶点组成三角形
	unsigned int baseIndex = 1;
	unsigned int ringVertexCount = SliceCount + 1;

	for( unsigned int i = 0; i < StackCount - 2; i++ )
	{
		for( unsigned int j = 0; j < SliceCount; j++ )
		{
			// 将在当前环的索引值为j,j+1的两个点和上一个环中索引值想同的两个点
			// 相连，组成两个三角形，由于最高点的索引值为0，所以从第一个环开始
			// 第i个环的起始索引值为（i - 1）*(sliceCount + 1)，
			// 注意是第i个环，所以后面才是i-1，循环的时候从0开始，
			// 所以计算的时候不需要减一
			pGeometry->AddFace( baseIndex + i * ringVertexCount + j , baseIndex + i * ringVertexCount + j + 1 , baseIndex + ( i + 1 ) * ringVertexCount + j );

			pGeometry->AddFace( baseIndex + ( i + 1 ) * ringVertexCount + j , baseIndex + i * ringVertexCount + j + 1 , baseIndex + ( i + 1 ) * ringVertexCount + j + 1 );
		}
	}

	// 最后一个环
	unsigned int SouthPoleIndex = ( unsigned int )CurrentVertex;

	// 在最后一个环中第一个顶点的索引偏移值
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

	// 添加顶点
	pGeometry->AddElement( pPosition );


	// ---------------添加索引------------------

	//将最顶上那个圆环的相邻的两个点与最高的顶点相连组成三角形
	for ( UINT i = 1; i <= SliceCount; i++ )
	{
		//注意方向，由于i+1的点距离x轴正轴偏离的角度比第i个点偏离的角度更大，因此按照顺时针的原则应该是0，i+1，i
		pGeometry->AddFace( 0 , i + 1 , i );
	}

	//处理内部的环，不包括最后一个环，因为最后一个环上的点是和最底部的顶点组成三角形
	unsigned int baseIndex = 1;
	unsigned int ringVertexCount = SliceCount + 1;

	for ( unsigned int i = 0; i < StackCount - 2; i++ )
	{
		for ( unsigned int j = 0; j < SliceCount; j++ )
		{
			// 将在当前环的索引值为j,j+1的两个点和上一个环中索引值想同的两个点
			// 相连，组成两个三角形，由于最高点的索引值为0，所以从第一个环开始
			// 第i个环的起始索引值为（i - 1）*(sliceCount + 1)，
			// 注意是第i个环，所以后面才是i-1，循环的时候从0开始，
			// 所以计算的时候不需要减一
			pGeometry->AddFace( baseIndex + i * ringVertexCount + j , baseIndex + i * ringVertexCount + j + 1 , baseIndex + ( i + 1 ) * ringVertexCount + j );

			pGeometry->AddFace( baseIndex + ( i + 1 ) * ringVertexCount + j , baseIndex + i * ringVertexCount + j + 1 , baseIndex + ( i + 1 ) * ringVertexCount + j + 1 );
		}
	}

	// 最后一个环
	unsigned int SouthPoleIndex = ( unsigned int )CurrentVertex;

	// 在最后一个环中第一个顶点的索引偏移值
	baseIndex = SouthPoleIndex - ringVertexCount;

	for ( unsigned int i = 0; i < SliceCount; i++ )
	{
		pGeometry->AddFace( SouthPoleIndex , baseIndex + i , baseIndex + i + 1 );
	}
}