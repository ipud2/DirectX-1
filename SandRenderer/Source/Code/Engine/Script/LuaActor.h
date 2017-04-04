#ifndef LUA_ACTOR_H
#define LUA_ACTOR_H

#include "ScriptManager.h"
#include "Engine/Object/Actor/Actor.h"

class LuaActor
{
public:
	LuaActor();
	~LuaActor();

	void Register( lua_State* L );

	static int Create( lua_State* L );

	static int AttachEntity( lua_State* L );

public:
	static std::vector<Sand::Actor*> ActorList;
};
#endif