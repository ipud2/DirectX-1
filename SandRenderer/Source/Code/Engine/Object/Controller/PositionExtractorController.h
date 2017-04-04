#ifndef PositionExtractorController_h
#define PositionExtractorController_h

namespace Sand
{
	template<typename T>
	class PositionExtractorController : public IController < T >
	{
	public:
		PositionExtractorController();
		virtual ~PositionExtractorController();

		virtual void Update( float fTime );

		void SetParameterWriter( Vector4fParameterWriter* pWriter );

	protected:
		Vector4fParameterWriter* m_pWriter;
	};

#include "PositionExtractorController.inl"
};
#endif