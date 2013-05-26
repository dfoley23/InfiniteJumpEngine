#ifndef LUA_BASE_H
#define LUA_BASE_H

#include "luaIncludes.h"
class LuaBaseComponent
{
public:
	LuaBaseComponent(void);
	~LuaBaseComponent(void);
protected:
	lua_State *state;
};

#endif