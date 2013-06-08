#include "Component.h"

void Component::update(float dT ) {
	if ( usingScript ) {
		cout << "update using lua script" << updateScript << endl;
		try {
			luabind::call_function<int>(lua->getState(), "updateCompass", dT);
		} catch (luabind::error &e){
			cerr << "Lua Error:" << lua_tostring( e.state(), -1) << "\n";
		}
	}
}

void Component::setLuaBase( LuaBaseComponent * luaBase ){
	lua = luaBase;
}

void Component::setUpdateScript( string scriptFile ) {
	updateScript = scriptFile;
	usingScript = true;
}

