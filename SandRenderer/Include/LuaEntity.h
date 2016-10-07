#ifndef LUA_ENTITY_H
#define LUA_ENTITY_H

#include "ScriptManager.h"

class LuaEntity
{
public:
	LuaEntity();
	~LuaEntity();

	void Register( lua_State* L );

	static int Create( lua_State* L );

	static int SetGeometry( lua_State* L );

	static int SetMaterial( lua_State* L );

	static int SetEffect( lua_State* L );

	static int SetPos( lua_State* L );
};
#endif