#include "PCH.h"
#include "LuaEntity.h"
#include "Entity.h"
#include "Geometry.h"
#include "Material.h"

using namespace Sand;

LuaEntity::LuaEntity()
{

}

LuaEntity::~LuaEntity()
{

}

void LuaEntity::Register( lua_State* L )
{
	static const luaL_Reg RegFuncList[] =
	{
		{ "new" , LuaEntity::Create } ,
		{ "set_geometry" , LuaEntity::SetGeometry } ,
		{ "set_material" , LuaEntity::SetMaterial } ,
		{ "set_effect" , LuaEntity::SetEffect } ,
		{ "set_pos" , LuaEntity::SetPos } ,
		{ NULL , NULL }
	};

	luaL_newmetatable( L , "luaL_Entity" );

	luaL_setfuncs( L , RegFuncList , 0 );

	lua_pushvalue( L , -1 );

	lua_setfield( L , -2 , "__index" );

	lua_setglobal( L , "Entity" );
}

int LuaEntity::Create( lua_State* L )
{
	Entity** udata = ( Entity** )lua_newuserdata( L , sizeof( Entity* ) );
	*udata = new Entity;

	luaL_getmetatable( L , "luaL_Entity" );

	lua_setmetatable( L , -2 );

	return 1;
}

int LuaEntity::SetGeometry( lua_State* L )
{
	Entity* pEntity = ( *( Entity** )luaL_checkudata( L , 1 , "luaL_Entity" ) );

	GeometryPtr pGeometry = GeometryPtr( *( Geometry** )luaL_checkudata( L , 2, "luaL_Geometry" ) );

	pEntity->GetRenderableRef().SetGeometry( pGeometry );

	return 0;
}

int LuaEntity::SetMaterial( lua_State* L )
{
	Entity* pEntity = *( Entity** )luaL_checkudata( L , 1 , "luaL_Entity" );

	Material* pMaterial = *( Material** )luaL_checkudata( L , 2 , "luaL_Material" );

	pEntity->GetRenderableRef().SetMaterial( pMaterial );

	return 0;
}

int LuaEntity::SetEffect( lua_State* L )
{
	Entity* pEntity = *( Entity** )luaL_checkudata( L , 1 , "luaL_Entity" );

	RenderEffect* pRenderEffect = *( RenderEffect** )luaL_checkudata( L , 2 , "luaL_Effect" );

	EffectPtr pEffect = EffectPtr( new Effect );

	pEffect->Schemes[VT_PERSPECTIVE].bRender = true;
	pEffect->Schemes[VT_PERSPECTIVE].pEffect = pRenderEffect;

	pEntity->GetRenderableRef().SetEffect( pEffect );

	return 0;
}

int LuaEntity::SetPos( lua_State* L )
{
	Entity* pEntity = ( *( Entity** )luaL_checkudata( L , 1 , "luaL_Entity" ) );

	float x = ( float )lua_tonumber( L , 2 );
	float y = ( float )lua_tonumber( L , 3 );
	float z = ( float )lua_tonumber( L , 4 );

	pEntity->GetTransformRef().GetPositionRef() = Vector3f( x , y , z );

	return 0;
}