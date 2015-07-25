//
// Created by alex on 25/07/2015.
//

#include <lauxlib.h>
#include <stdint.h>
#include <base64encode.h>
#include "lpdkdf2.h"
#include "fastpbkdf2/fastpbkdf2.h"

// max base64 size result supported
#define BUFF_SIZE 1024 * 32


void pbkdf2_hmac_sha256(lua_State *L) {
    char *pwd = luaL_check_string(L, 1);
    char *salt = luaL_check_string(L, 2);

    uint32_t iterations = (unsigned) luaL_check_int(L, 3);

    size_t byteSize = 32; // 256-bit (32-byte)
    char encoded[byteSize];

    fastpbkdf2_hmac_sha256(
            (unsigned char *) pwd, strlen(pwd),
            (unsigned char *) salt, strlen(salt),
            iterations,
            (unsigned char *) encoded, byteSize);

    char out[BUFF_SIZE];
    int length = base64_encode((unsigned char *) encoded, byteSize, out);

    lua_pushlstring(L, &out[0], length);
}


static struct luaL_reg lpbkdf2[] = {
    {"fastpbkdf2_hmac_sha256", pbkdf2_hmac_sha256}
};

int LUA_LIBRARY lua_lpbkdf2open(lua_State *L) {
    luaL_openlib(L, lpbkdf2, (sizeof(lpbkdf2)/sizeof(lpbkdf2[0])));
    return 0;
}