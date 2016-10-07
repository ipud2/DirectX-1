#ifndef SCRIPT_MANAGER_H
#define SCRIPT_MANAGER_H

#include "PCH.h"

extern "C"
{
#include "Lua-5.3.3/src/lua.h"
#include "lua-5.3.3/src/lauxlib.h"
#include "lua-5.3.3/src/lualib.h"
}

struct ClassData
{
	std::string name;
	unsigned int count;
	unsigned int id;

public:
	ClassData()
	{
		name = "";
		count = 0;
		id = 0;
	}

	unsigned int ReserveHandle()
	{
		unsigned int handle = count + id;
		count++;
		return handle;
	}
};

struct ObjectData
{
	void* pointer;

public:
	ObjectData()
	{
		pointer = nullptr;
	}
};

struct PointerData
{
	unsigned int handle;
public:
	PointerData()
	{
		handle = 0xffffffff;
	}
};

class ScriptManager
{
public:
	ScriptManager();
	~ScriptManager();

	static ScriptManager* Get();

	// registration of standard static function
	void RegisterFunction( const char* name , lua_CFunction func );
	void RegisterClassFunction( const char* classname , const char* funcname , lua_CFunction func );

	void ExecuteChunk( char* chunk );

	// registration of classes , their class methods , and instance of an object
	unsigned int RegisterEngineClass( const char* name );
	unsigned int RegisterEngineObject( const char* name , void* pObject );

	bool UnRegisterObjectByHandle( unsigned int handle );
	bool UnRegisterObjectByPointer( void* pObject );
	bool IsRegister( void* pObject );

	void* GetObjectPointer( unsigned int uID );
	unsigned int GetObjectHandle( void* pObject );

	void Run( const char* szFIlename );
	lua_State* GetState();

	void ReportErrors();

protected:
	static ScriptManager* ms_pScriptManager;

	lua_State* m_pLuaState;

	int m_iClassIndex;
	std::map<const char* , ClassData>	m_kClassRegistry;
	std::map<unsigned int , ObjectData> m_kObjectRegistry;
	std::map<void* , PointerData>		m_kPointerRegistry;
};
#endif