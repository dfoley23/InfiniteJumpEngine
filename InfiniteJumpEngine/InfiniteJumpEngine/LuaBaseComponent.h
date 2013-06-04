#ifndef LUA_BASE_H
#define LUA_BASE_H

#include "luaIncludes.h"

class LuaBaseComponent
{
public:
	LuaBaseComponent(void);
	~LuaBaseComponent(void);
	lua_State *getState(){return state;}

protected:
	lua_State *state;
}
;

#endif