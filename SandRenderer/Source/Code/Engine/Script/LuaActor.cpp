#include <Engine/PCH.h>
#include "LuaActor.h"
#include "Engine/Object/Actor/Actor.h"

using namespace Sand;

std::vector<Actor*> LuaActor::ActorList;

LuaActor::LuaActor()
{

}

LuaActor::~LuaActor()
{

}

int LuaActor::Create( lua_State* L )
{
	Actor** pActorUserData = ( Actor** )lua_newuserdata( L , sizeof( Actor** ) );
	*pActorUserData = new Actor;

	ActorList.push_back( *pActorUserData );

	// 1 | -1 | userdata

	luaL_getmetatable( L , "luaL_Actor" );
	// 2 | -1 | metatable : luaL_Actor
	// 1 | -2 | userdata

	lua_setmetatable( L , -2 );
	// 1 | -1 | userdata

	return 1;
}

Actor* CheckType( lua_State* L , int n )
{
	return *( Actor** )luaL_checkudata( L , n , "luaL_Actor" );
}

void LuaActor::Register( lua_State* L )
{
	luaL_Reg LuaRegList[] = 
	{
		{ "new" , LuaActor::Create } , 
		{ "attach" , LuaActor::AttachEntity },
		{ NULL , NULL }
	};

	luaL_newmetatable( L , "luaL_Actor" );
	// 1 | -1 | metatable : luaL_Actor

	// register for function for this class into the metatable we just created.
	luaL_setfuncs( L , LuaRegList , 0 );

	lua_pushvalue( L , -1 );
	// 2 | -1 | metatable : luaL_Actor
	// 1 | -2 | metatable : luaL_Actor

	lua_setfield( L , -2 , "__index" );
	// 1 | -1 | metatable : luaL_Actor

	lua_setglobal( L , "Actor" );
}

int LuaActor::AttachEntity( lua_State* L )
{
	Actor* pActor = *( Actor** )luaL_checkudata( L , 1 , "luaL_Actor" );

	Entity* pEntity = *( Entity** )luaL_checkudata( L , 2 , "luaL_Entity" );
	pEntity->GetTransformRef().GetScaleRef() = Vector3f( 10.0f , 10.0f , 10.0f );
	pEntity->GetTransformRef().GetPositionRef() = Vector3f( 0.0f , 0.0f , 0.0f );

	pActor->GetRootNode()->AttachChild( pEntity );

	return 0;
}