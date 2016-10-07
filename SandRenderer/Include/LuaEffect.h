#ifndef LUA_EFFECT_H
#define LUA_EFFECT_H

#include "ScriptManager.h"
#include "Renderer.h"

class LuaEffect
{
public:
	LuaEffect( Sand::Renderer* pRenderer );
	~LuaEffect();

public:
	void Register( lua_State* L );

	static int Create( lua_State* L );

private:
	static Sand::Renderer* m_pRenderer;
};
#endif