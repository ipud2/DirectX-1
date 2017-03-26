#ifndef V_KEY_FRAME_H
#define V_KEY_FRAME_H

namespace Sand
{
	class VKeyFrame
	{
	public:
		VKeyFrame();

		void SetValue( float start_time , float value );

		void SetDuration( float dur );

		float GetStart()
		{
			return m_fStartTime;
		}

		float GetEnd()
		{
			return m_fStartTime + m_fDuration;
		}
	protected:
		float m_fStartTime;
		float m_fDuration;
		float m_fValue;
	};
}
#endif