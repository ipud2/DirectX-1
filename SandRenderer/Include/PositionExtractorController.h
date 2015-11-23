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

		void SetParameterWriter( VectorParameterWriter* pWriter );

	protected:
		VectorParameterWriter* m_pWriter;
	};

#include "PositionExtractorController.inl"
};
#endif