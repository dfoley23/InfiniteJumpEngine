#include "LuaBaseComponent.h"

void greet()
{
    std::cout << "Lua Component Initialized\n";
}

LuaBaseComponent::LuaBaseComponent(void)
{
	state = luaL_newstate();
	open(state);
	module(state)
    [
        def("greet", &greet)
    ];
	luaL_dostring(state,"greet()\n");
 }


LuaBaseComponent::~LuaBaseComponent(void)
{
  lua_close(state);
}