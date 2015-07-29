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

hashers = {
    ['hmac_sha1'] = {
        {
            pwd = 'test',
            pwd_base64 = 'Cvdv4d3xxO2uvIT8NJQ3WuEAdGs=',
            salt = 'SaltsaltSALT',
            iterations = 15000
        },
        {
            pwd = 'Bpgb$%pdCK8#uWEw',
            pwd_base64 = 'HxjlEcrsHwEKBdctjwWVeVzD70w=',
            salt = 'ulVOSa99lCAi6S8h',
            iterations = 15000
        },
        {
            pwd = 'bWgbO7WQ8OIjfVtp7tcjMfcc4M78KBMK',
            pwd_base64 = '9wKIFotQ5M2oxxkobhYZiWlgAcM=',
            salt = 'w%#Yx6_mQZrQK=&C5N!',
            iterations = 20000
        }
    },
    ['hmac_sha256'] = {
        {
            pwd = 'test',
            pwd_base64 = 'O2q3Vg/lH8+l5QKmVUqq+novPt4nSIYDZvvTpdi8PRo=',
            salt = 'saltSALTSaLtsalt',
            iterations = 15000
        },
        {
            pwd = 'mypass',
            pwd_base64 = 'Q2QI49JPpcJKTDf/A7IqLDbDsvnFbgViSLMqTXMiqnk=',
            salt = 'saltSALTSaLtsalt',
            iterations = 15000
        },
        {
            pwd = '12345678',
            pwd_base64 = '5RSe+1NV14olQNiCJ+S9ykPQd/qQjqNtO5uwqRA117s=',
            salt = 'asdf12345',
            iterations = 15000
        }
    },
    --
    ['hmac_sha512'] = {
        {
            pwd = '5pmU73T_e7Z+w_X@+?_QEUfu2A&-6BRKtW64qqZs',
            pwd_base64 = 'Nc5iSSPE5Tnt3/OhMu195yHlc6Qgrr5Vs96Z1R/fhbphU1AgaBr7LMXec+Qchg8OJv8jv2wQMmTufb5/lh0Vyw==',
            salt = 'Cm2mJ?-v',
            iterations = 15000
        },
    }
}

-- testing
print('==============================')
print('testing hmac_sha1')
foreachi(hashers['hmac_sha1'], function(i, obj)
    local hash_base64 = pbkdf2_hmac_sha1(obj.pwd, obj.salt, obj.iterations)
    print(hash_base64, obj.pwd_base64)
    assert(hash_base64 == obj.pwd_base64, '[hmac_sha1] invalid hash!')
end)

print('==============================')
print('testing hmac_sha256')
foreachi(hashers['hmac_sha256'], function(i, obj)
    local hash_base64 = pbkdf2_hmac_sha256(obj.pwd, obj.salt, obj.iterations)
    print(hash_base64, obj.pwd_base64)
    assert(hash_base64 == obj.pwd_base64, '[hmac_sha256] invalid hash!')
end)

print('==============================')
print('testing hmac_sha512')
foreachi(hashers['hmac_sha512'], function(i, obj)
    local hash_base64 = pbkdf2_hmac_sha512(obj.pwd, obj.salt, obj.iterations)
    print(format("%s\n%s", hash_base64, obj.pwd_base64))
    assert(hash_base64 == obj.pwd_base64, '[hmac_sha512] invalid hash!')
end)

print('==============================')
print('testing rand_salt')
local i = 4
local rsalt
while (i < 128) do
    rsalt = rand_salt(i)
    print(i, rsalt, strlen(rsalt) == i)
    i = i * 2
 end