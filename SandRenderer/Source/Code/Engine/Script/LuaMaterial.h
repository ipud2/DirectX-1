#ifndef LUA_MATERIAL_H
#define LUA_MATERIAL_H

#include "ScriptManager.h"

class LuaMaterial
{
public:
	LuaMaterial();

	~LuaMaterial();

	void Register( lua_State* L );

private:
	static int Create( lua_State* L );
};
#endif