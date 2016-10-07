#ifndef MATERIAL_HELPER_H
#define MATERIAL_HELPER_H

extern "C"
{
#include "Lua/inc/lua.h"
#include "lua/inc/lauxlib.h"
#include "lua/inc/lualib.h"
}
#include <stdio.h>
#include "LuaSampler.h"

typedef union
{
	char str[1024];
	float f;
	int i;
	bool b;
	float arr[4];
	Sand::LuaSampler sampler;
}LuaValue;

typedef enum
{
	ELT_NUMBER ,
	ELT_INTEGER ,
	ELT_STRING ,
	ELT_BOOL ,
	ELT_ARRAY , 
	ELT_SAMPLER
}ELuaType;

struct MatItem
{
	LuaValue v;
	ELuaType eType;
};

std::string GetMatPath( const char* name );

#endif