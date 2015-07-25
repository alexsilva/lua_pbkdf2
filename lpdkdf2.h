//
// Created by alex on 25/07/2015.
//

#ifndef LUA_PBKDF2_LBPDKDF2_H
#define LUA_PBKDF2_LBPDKDF2_H

#define LUA_LIBRARY __declspec(dllexport)
#include "lua.h"

int LUA_LIBRARY lua_lpbkdf2open(lua_State *);

#endif //LUA_PBKDF2_LBPDKDF2_H
