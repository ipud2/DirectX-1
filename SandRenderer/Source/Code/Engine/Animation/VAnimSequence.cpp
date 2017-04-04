#include "Engine/PCH.h"
#include "VKeyFrame.h"
#include "VAnimSequence.h"

Sand::VAimSequence::VAimSequence()
{
	m_vKeyFrames.clear();
}

void Sand::VAimSequence::AddKeyFrame( VKeyFrame* key_frame )
{
	m_vKeyFrames.push_back( key_frame );
}

float Sand::VAimSequence::Evaluate( float t )
{
	int index = -1;
	return 1.0f;
}