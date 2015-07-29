//
// Created by alex on 25/07/2015.
//

#include <lauxlib.h>
#include <stdint.h>
#include <base64encode.h>
#include "lpdkdf2.h"
#include "fastpbkdf2/fastpbkdf2.h"
#include <openssl/rand.h>
#include <stdio.h>
#include <time.h>

// max base64 size result supported
#define BUFF_SIZE 1024 * 32


// convert bytes to hex
static void byteHex(char buff[], char key[], int size) {
    srand(time(NULL));
    char *fmt[] = {"%02x", "%02X"};
    for (int i = 0; i < size; i++) {
        sprintf(buff + 2 * i, fmt[rand() % 2], key[i]);
    }
}


// random salt generator
void rand_salt(lua_State *L) {
    lua_Object obj = lua_getparam(L, 1);

    int num = (int) lua_getnumber(L, obj);
    num = num > 0 ? num : 32;

    char key[num];

    if (RAND_bytes((unsigned char *) key, num)) {
        char buff[num * 2 + 1];

        byteHex(buff, key, num);
        lua_pushlstring(L, &buff[0], num);
    } else {
        lua_pushnil(L); // error
    }
}

/*
 * HMAC-SHA1
 * 1: password
 * 2: salt
 * 3 iterations
 */
void pbkdf2_hmac_sha1(lua_State *L) {
    char *pwd = luaL_check_string(L, 1);
    char *salt = luaL_check_string(L, 2);

    uint32_t iterations = (unsigned) luaL_check_int(L, 3);

    size_t byteSize = 20; // sha1-bit (20-byte)
    char encoded[byteSize];

    fastpbkdf2_hmac_sha1(
            (unsigned char *) pwd, strlen(pwd),
            (unsigned char *) salt, strlen(salt),
            iterations,
            (unsigned char *) encoded, byteSize);

    char out[BUFF_SIZE];
    int length = base64_encode((unsigned char *) encoded, byteSize, out);

    lua_pushlstring(L, &out[0], length);
}

/*
 * HMAC-SHA256
 * params: password (str), salt (str), iterations (int)
 */
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
    {"pbkdf2_hmac_sha1", pbkdf2_hmac_sha1},
    {"pbkdf2_hmac_sha256", pbkdf2_hmac_sha256},
    {"rand_salt", rand_salt}
};

int LUA_LIBRARY lua_lpbkdf2open(lua_State *L) {
    luaL_openlib(L, lpbkdf2, (sizeof(lpbkdf2)/sizeof(lpbkdf2[0])));
    return 0;
}