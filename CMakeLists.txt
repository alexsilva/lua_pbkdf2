cmake_minimum_required(VERSION 3.2)
project(lua_pbkdf2)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -Wall -Wextra -pedantic -std=c99")

link_directories(
    ${OPENSSL_DIR}/Release
)

include_directories(
    ${OPENSSL_DIR}/include
    ${LUA_DIR}/include
    base64
)

set(SOURCE_FILES
    base64/base64encode.c
    fastpbkdf2/fastpbkdf2.c
    lpdkdf2.c)

add_library(lua_pbkdf2 SHARED ${SOURCE_FILES})
target_link_libraries(lua_pbkdf2 crypto ${LUA_LIB})
set_target_properties(lua_pbkdf2 PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
