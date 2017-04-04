#ifndef V_ANIM_SEQUENCE_H
#define V_ANIM_SEQUENCE_H

#include <vector>

namespace Sand
{
	class VKeyFrame;

	class VAimSequence
	{
	public:
		VAimSequence();

		void AddKeyFrame( VKeyFrame* key_frame );

		float Evaluate( float t );

	protected:
		std::vector<VKeyFrame*>	m_vKeyFrames;
	};
}
#endif