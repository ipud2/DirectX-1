#pragma once

template<typename T>
struct TIsClass
{
private:
	// int U::*Ϊ�ӳ�Ա����ָ�룬ָ��U��int��Ա����
	// ��UΪclass����struct����ú����ɱ�ʵ����
	// ���򣬸ú����޷�ʵ����
	template<typename U> static uint16 Func( int U::* );
	template<typename U> static uint8  Func( ... );

public:
	enum
	{
		Value = !__is_union( T ) && ( sizeof( Func<T>( 0 ) ) == sizeof( uint16 ) )
	};
};