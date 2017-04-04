#include <Engine/PCH.h>
#include "FFbxShape.h"

/*
	ShapeChannel : 有一个对应的AnimCurve , AnimCurve的value是deform value
				   对应着从Base Shape到Target Shape的deform percent
*/
void Sand::ParseShape( FbxGeometry* pGeometry )
{
	int iBlendShapeCount = pGeometry->GetDeformerCount(FbxDeformer::eBlendShape);

	for ( int iBlendShapeIndex = 0; iBlendShapeIndex < iBlendShapeCount; iBlendShapeIndex++ )
	{
		FbxBlendShape* pBlendShape = ( FbxBlendShape* )pGeometry->GetDeformer( iBlendShapeIndex , FbxDeformer::eBlendShape );

		int iBlendShapeChannelCount = pBlendShape->GetBlendShapeChannelCount();

		for ( int iBlendShapeChannelIndex = 0; iBlendShapeChannelIndex < iBlendShapeChannelCount; iBlendShapeChannelIndex++ )
		{
			FbxBlendShapeChannel* pBlendShapeChannel = pBlendShape->GetBlendShapeChannel( iBlendShapeChannelIndex );

			float defaultDeformValue = ( float )pBlendShapeChannel->DeformPercent.Get();

			int iTargetShapeCount = pBlendShapeChannel->GetTargetShapeCount();
			for ( int iTargetShapeIndex = 0; iTargetShapeIndex < iTargetShapeCount; iTargetShapeIndex++ )
			{
				FbxShape* pTargetShape = pBlendShapeChannel->GetTargetShape( iTargetShapeIndex );

				int iControlPointCount = pTargetShape->GetControlPointsCount();
				FbxVector4* pControlPoints = pTargetShape->GetControlPoints();

				FbxLayerElementArrayTemplate<FbxVector4>* pNormals = nullptr;

				bool bStatus = pTargetShape->GetNormals( &pNormals );
				for ( int j = 0; j < iControlPointCount; j++ )
				{
					float x = ( float )pControlPoints[j][0];
					float y = ( float )pControlPoints[j][1];
					float z = ( float )pControlPoints[j][2];

					if ( bStatus && pNormals && pNormals->GetCount() == iControlPointCount )
					{
						float nx = ( float )pNormals->GetAt( j )[0];
						float ny = ( float )pNormals->GetAt( j )[1];
						float nz = ( float )pNormals->GetAt( j )[2];
					}
				}
			}
		}
	}
}