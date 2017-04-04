#include <Engine/PCH.h>
#include "MaterialLua.h"

using namespace Sand;

void MaterialLua::Apply( lua_State* L , std::map<std::string , MatItem>& ParamList )
{
	int ioldtop = lua_gettop( L );
	lua_getglobal( L , "MatTable" );									// -0 , +1
		lua_pushnil( L );												// -0 , +1
		while ( lua_next( L , -2 ) )									// -1 , +2 | +0
		{
			// value : -1
			// key   : -2
			// table : -3
			int param_type = lua_type( L , -1 );
			const char* param_name = lua_tostring( L , -2 );

			MatItem item;

			switch ( param_type )
			{
				case LUA_TNUMBER:
				{
					bool bInteger = lua_isinteger( L , -1 ) == 1;
					if ( bInteger )
					{
						item.eType = ELT_INTEGER;
						item.v.i = ( int )lua_tointeger( L , -1 );
					}
					else
					{
						item.eType = ELT_NUMBER;
						item.v.f = ( float )lua_tonumber( L , -1 );
					}

					ParamList[param_name] = item;
					break;
				}

				case LUA_TTABLE:
				{
					lua_len( L , -1 );	int len = ( int )lua_tointeger( L , -1 );	lua_pop( L , 1 );
					if ( len == 4 )
					{
						int type = lua_rawgeti( L , -1 , 1 );
						if ( type == 3 )	item.eType = ELT_ARRAY;
						lua_pop( L , 1 );
					}
					else
					{
						// Sampler应当是与shader绑定的，在shader中指定
						// 但是由于目前的设计缺陷，所以先暂时将其置于材质中
						item.eType = ELT_SAMPLER;
					}
					
					if ( item.eType == ELT_ARRAY )
					{
						for ( int i = 0; i < 4; i++ )
						{
							float v = 0.0f;
							lua_rawgeti( L , -1 , i + 1 );	v = ( float )lua_tonumber( L , -1 );	lua_pop( L , 1 );
							item.v.arr[i] = v;
						}
					}
					else
					{
						// ELT_Sampler
						ParseLuaSamplerTable( L , &item.v.sampler );
					}
					

					ParamList[param_name] = item;

					break;
				}
			
				case LUA_TBOOLEAN:
				{
					item.eType = ELT_BOOL;
					item.v.b = lua_toboolean( L , -1 ) == 1;

					ParamList[param_name] = item;

					break;
				}

				case LUA_TSTRING:
				{
					item.eType = ELT_STRING;
					strcpy_s( item.v.str , ( const char* )lua_tostring( L , -1 ) );
					ParamList[param_name] = item;

					break;
				}
			}
			lua_pop( L , 1 );	// keep 'key' for next iteration			// -1 , +0
		}
	lua_pop( L , 1 );														// -1 , +0
	assert( lua_gettop( L ) == ioldtop );
}