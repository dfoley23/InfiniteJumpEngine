#ifndef LUA_INCLUDES_H
#define LUA_INCLUDES_H

// Include the lua headers (the extern "C" is a requirement because we're
// using C++ and lua has been compiled as C code)
extern "C" {
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
}

// This is the only header we need to include for LuaBind to work
#include "luabind/luabind.hpp"

// Some other C++ headers we're most likely going to use
#include <iostream>
#include <string>

// We don't want to write std:: every time we're displaying some debug output
using namespace std;

#endif