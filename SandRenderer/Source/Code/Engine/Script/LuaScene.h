#ifndef LUA_SCENE_H
#define LUA_SCENE_H

#include "ScriptManager.h"
#include "Engine/Object/Scene/Scene.h"

namespace Sand
{
	class LuaScene
	{
	public:
		LuaScene();
		virtual ~LuaScene();

		static void Register( lua_State* L );
		static void CheckType( lua_State* L );
		
		static int Creator( lua_State* L );
		static int CreateExisting( lua_State* L , std::string& name , Scene* pScene );
		static int Destoryer( lua_State* L );

		static int AddActor( lua_State* L );
	};
}

#endif