#ifndef COMPONENT_H
#define COMPONENT_H
#include "IJMessage.h"
#include "luaIncludes.h"
#include "LuaBaseComponent.h"
#include "Drawable.h"
#include <vector>

using namespace std;
class Component: public Drawable
{
public:
	Component(){
		parent = NULL;
		updateScript = "";
		usingScript = false;
	}

	Component(string scriptFile ) {
		parent = NULL;
		updateScript = scriptFile;
		usingScript = true;
	}

	virtual void update(float dT ) {
		if ( usingScript ) {
			cout << "update using lua script" << updateScript << endl;
			try {
				luabind::call_function<int>(lua->getState(), "updateCompass", dT);
			} catch (luabind::error &e){
				cerr << "Lua Error:" << lua_tostring( e.state(), -1) << "\n";
			}
		}
	}

	virtual void setLuaBase( LuaBaseComponent * luaBase ){
		lua = luaBase;
	}

	virtual void setUpdateScript( string scriptFile ) {
		updateScript = scriptFile;
		usingScript = true;
	}

	virtual Component * getParent(){return parent;};
	virtual void setParent(Component * p){parent = p;};
	virtual glm::mat4 transform(void){
		return transform(glm::mat4());
	}
	virtual glm::mat4 transform(glm::mat4 in){
		if (parent)
			return parent->transform(in);
		return in;
	}

	virtual void sendMessage(Component* that, Component* other, const char *s, glm::vec4 v = glm::vec4(0,0,0,0)){
		IJMessage *m =  new IJMessage(this, that, other, s, v);
		sendMessage(m, that);
		delete m; m = NULL;
	}

	virtual void sendMessage(Component* that, Component* other, const char *s, float x, float y, float z, float w){
		glm::vec4 v = glm::vec4( x, y, z, w );
		IJMessage *m =  new IJMessage(this, that, other, s, v);
		sendMessage(m, that);
		delete m; m = NULL;
	}

	virtual void sendMessage( IJMessage *m, Component* that){
		if (that){
			that->receiveMessage(m);
		} else {
			//cout << "Message fell out of parent chain:" << m->content << " " << m->vecContent.x << " " << m->vecContent.y << " " << m->vecContent.z << endl;
		}
	}

	virtual void receiveMessage( IJMessage *m ){
		sendMessage(m, parent);
	}

	virtual char* getType(){
		return "Component";
	}

	static void registerLua(lua_State *lua){
		module(lua)
		[luabind::class_<Component>("Component")
        .def(constructor<>())
		//.def("sendMessage", ((void(*)(Component*, Component*, const char*, float, float, float, float))&Component::sendMessage))
		];
	}

protected:
	Component *parent;
	string updateScript;
	bool usingScript;
	LuaBaseComponent * lua;
};

typedef std::vector<Component*> componentVector;
typedef componentVector::iterator componentIter;

#endif COMPONENT_H