#ifndef LUA_COMPONENT_H
#define LUA_COMPONENT_H
#include "LuaBaseComponent.h"
#include "Component.h"

class LuaComponent : public Component
{
public:
	LuaComponent(lua_State*);
	~LuaComponent(void);

protected:
	lua_State *state;
	luabind::object table;
};

#endif