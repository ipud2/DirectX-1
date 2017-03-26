#ifndef V_TRIANGLE_LIST_H
#define V_TRIANGLE_LIST_H

namespace Sand
{
	class VTriangle
	{
	public:
		VTriangle();

		void SetMaterialIndex( int32 iMaterialIndex );

		int32 GetMatrixIndex();

		uint32& operator[]( uint32 index );
		uint32 operator[]( uint32 index ) const;

	private:
		int32 m_iMaterialIndex;
		uint32 m_aIndex[3];
	};
}
#endif