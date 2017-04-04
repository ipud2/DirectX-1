#ifndef MATERIAL_LUA_H
#define MATERIAL_LUA_H

#include "MaterialHelper.h"

struct lua_State;

namespace Sand
{
	class MaterialLua
	{
	public:
		static void Apply( lua_State* L , std::map < std::string , MatItem >& ParamList );
	};
}
#endif