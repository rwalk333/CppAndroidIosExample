//
//  Core.cpp
//  HelloCpp
//
//  Created by Ademar Alves de Oliveira on 5/28/13.
//  Copyright (c) 2013 Jurema. All rights reserved.
//

#include "Core.h"

extern "C"{
 #include "lua.h"
 #include "lauxlib.h"
 #include "lualib.h"
}

#include "iostream"

std::string CPP_BASE_STRING = "cpp says hello world to ";

const char* concateneMyStringWithCppString(const char* myString) {
    std::string msg;
    
    // open the lua stack and push the echo function
    lua_State * L = luaL_newstate();
    luaL_openlibs(L);
    std::string astr = "echo = function(x) return x end";
    luaL_loadstring(L, astr.c_str());
    int err0 = lua_pcallk(L, 0, LUA_MULTRET, 0, 0, NULL);
    if(err0 != LUA_OK)
    {
        msg = lua_tolstring(L, -1, NULL);
        return msg.c_str();
    }
    
    // now, call the echo function on the input
    lua_settop(L, 0);
    lua_getglobal(L, "echo");
    std::string luamessage;
    luamessage = "lua says hello to cpp";
    lua_pushstring(L, luamessage.c_str());
    int err = lua_pcallk(L, 1, LUA_MULTRET, 0, 0, NULL);
    if(err != LUA_OK)
    {
        msg = lua_tolstring(L, -1, NULL);
        return msg.c_str();
    }
    
    int n = lua_gettop(L);
    if(n==1)
    {
        msg = lua_tolstring(L, -1, NULL);
    }
    
    msg = CPP_BASE_STRING + myString + " : "+msg;
    return msg.c_str();
}