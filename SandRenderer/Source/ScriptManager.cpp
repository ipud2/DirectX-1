#include "PCH.h"
#include "ScriptManager.h"
#include "Log.h"
#include "SandString.h"

using namespace Sand;

ScriptManager* ScriptManager::ms_pScriptManager = nullptr;

ScriptManager::ScriptManager()
{
	ms_pScriptManager = this;

	m_pLuaState = nullptr;
	m_pLuaState = luaL_newstate();

	luaL_openlibs( m_pLuaState );

	m_iClassIndex = 1;
}

ScriptManager::~ScriptManager()
{
	lua_close( m_pLuaState );
	m_pLuaState = nullptr;
}

ScriptManager* ScriptManager::Get()
{
	return ms_pScriptManager;
}

void ScriptManager::Run( const char* szFIlename )
{
	if ( luaL_dofile( m_pLuaState , szFIlename ) != LUA_OK )
	{
		ReportErrors();
	}
}

void ScriptManager::ExecuteChunk( char* chunk )
{
	// load and run string
	// equivalent to lua_loadstring(m_pLuaState , chunk) || lua_pcall(L , 0 , LUA_MULTRET , 0)
	// return fasle if no error occur or true in case of errors
	luaL_dostring( m_pLuaState , chunk );
}

void ScriptManager::RegisterFunction( const char* name , lua_CFunction func )
{
	// set the C function func as the new value of global name
	lua_register( m_pLuaState , name , func );
}

void ScriptManager::RegisterClassFunction( const char* classname , const char* funcname , lua_CFunction func )
{
	// get the global environment table from registry
	lua_rawgeti(m_pLuaState , LUA_REGISTRYINDEX , LUA_RIDX_GLOBALS);		// [-0 , +1 , -]

	lua_getfield( m_pLuaState , -1 , classname );							// [-0 , +1 , e]
	lua_pushcfunction( m_pLuaState , func );								// [-0 , +1 , -]
	lua_setfield( m_pLuaState , -2 , funcname );								// [-1 , +0 , e]
	lua_pop( m_pLuaState , 2 );												// [-2 , +0 , -] pop table and global environment
}

lua_State* ScriptManager::GetState()
{
	return m_pLuaState;
}

unsigned int ScriptManager::RegisterEngineClass( const char* name )
{
	ClassData data = m_kClassRegistry[name];

	if ( data.name == "" )
	{
		data.name = name;
		data.id = m_iClassIndex << 16;
		data.count = 0;

		m_kClassRegistry[name] = data;
		m_iClassIndex++;

		lua_rawgeti( m_pLuaState , LUA_REGISTRYINDEX , LUA_RIDX_GLOBALS );
		lua_newtable( m_pLuaState );
		lua_setfield( m_pLuaState , -2 , name );
		lua_pop( m_pLuaState , 1 );
	}

	return data.id;
}

unsigned int ScriptManager::RegisterEngineObject( const char* name , void* pObject )
{
	if ( m_kPointerRegistry[pObject].handle != 0xffffffff )
	{
		return ( m_kPointerRegistry[pObject].handle );
	}

	// 如果该类之前未被注册过，先注册该类
	if ( m_kClassRegistry[name].name == "" )
	{
		RegisterEngineClass( name );
	}

	unsigned int handle = m_kClassRegistry[name].ReserveHandle();

	m_kObjectRegistry[handle].pointer = pObject;
	m_kPointerRegistry[pObject].handle = handle;
}

bool ScriptManager::UnRegisterObjectByHandle( unsigned int handle )
{
	if ( m_kObjectRegistry[handle].pointer )
	{
		m_kPointerRegistry[m_kObjectRegistry[handle].pointer].handle = 0xffffffff;
		m_kObjectRegistry[handle].pointer = nullptr;
		return true;
	}

	return false;
}

bool ScriptManager::UnRegisterObjectByPointer( void* pObject )
{
	if ( m_kPointerRegistry[pObject].handle != 0xffffffff )
	{
		m_kObjectRegistry[m_kPointerRegistry[pObject].handle].pointer = nullptr;
		m_kPointerRegistry[pObject].handle = 0xffffffff;
		return true;
	}

	return false;
}

void* ScriptManager::GetObjectPointer( unsigned int handle )
{
	return m_kObjectRegistry[handle].pointer;
}

unsigned int ScriptManager::GetObjectHandle( void* pObject )
{
	return m_kPointerRegistry[pObject].handle;
}

void ScriptManager::ReportErrors()
{
	const char* errormessage = lua_tostring( m_pLuaState , 1 );

	Log::Get().Write( SandString::ToUnicode( std::string( errormessage ) ) );

	lua_pop( m_pLuaState , 1 );
}