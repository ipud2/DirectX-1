#pragma once

template<typename T>
struct TIsClass
{
private:
	// int U::*为从成员变量指针，指向U的int成员变量
	// 若U为class或者struct，则该函数可被实例化
	// 否则，该函数无法实例化
	template<typename U> static uint16 Func( int U::* );
	template<typename U> static uint8  Func( ... );

public:
	enum
	{
		Value = !__is_union( T ) && ( sizeof( Func<T>( 0 ) ) == sizeof( uint16 ) )
	};
};