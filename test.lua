--
-- Created by IntelliJ IDEA.
-- User: alex
-- Date: 25/07/2015
-- Time: 15:35
-- To change this template use File | Settings | File Templates.
--
handle, msg = loadlib(getenv("LIBRARY_PATH"))

if (not handle or handle == -1) then
    error(msg)
end

callfromlib(handle, 'lua_lpbkdf2open')

local pwd_base64 = 'G8xbilfZyeNcYVAW3o9fs42l7hypVRec1XfdjoofPco='
local salt = 'eLZ6kQDRVu9n'
local iterations = 15000

-- testing
local hash_base64 = pbkdf2_hmac_sha256("teste", salt, iterations)

print(hash_base64, pwd_base64)
assert(hash_base64 == pwd_base64)

local i = 4
local rsalt
while (i < 512) do
    rsalt = rand_salt(i)
    print(i, rsalt, strlen(rsalt) == i)
    i = i ^ 2
 end