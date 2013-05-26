#include "LuaComponent.h"


LuaComponent::LuaComponent(lua_State* s)
{
	state = s;
	table = luabind::newtable( state );
}


LuaComponent::~LuaComponent(void)
{
}
