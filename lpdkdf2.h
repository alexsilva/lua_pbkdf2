//
// Created by alex on 25/07/2015.
//

#ifndef LUA_PBKDF2_LBPDKDF2_H
#define LUA_PBKDF2_LBPDKDF2_H

#if defined(_MSC_VER)
    //  Microsoft
    #define LUA_LIBRARY __declspec(dllexport)
#else
    //  GCC
    #define LUA_LIBRARY __attribute__((visibility("default")))
#endif

#include "lua.h"

int LUA_LIBRARY lua_lpbkdf2open(lua_State *);

#endif //LUA_PBKDF2_LBPDKDF2_H
