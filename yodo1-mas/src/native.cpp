// myextension.cpp
// Extension lib defines
#define EXTENSION_NAME yodo1_mas
#define LIB_NAME "yodo1_mas"
#define MODULE_NAME "yodo1_mas"
// include the Defold SDK
#include <dmsdk/sdk.h>
#include "yodo1_mas.h"
#include "static_hash.h"

#if defined(DM_PLATFORM_ANDROID)

namespace yodo1mas {

static int LuaSetAdBuildConfig(lua_State* L){
    if(!lua_istable(L,1)){
         luaL_error(L,"need config table");
    }

    bool enableAdaptiveBanner = false;
    bool enableUserPrivacyDialog = false;
    const char *userAgreementUrl = NULL;
    const char *privacyPolicyUrl = NULL;

     lua_pushvalue(L,1);
    /* table is in the stack at index 't' */
     lua_pushnil(L);  /* first key */
     while (lua_next(L, -2) != 0) {
       /* uses 'key' (at index -2) and 'value' (at index -1) */
        //printf("%s - %s\n",lua_tostring(L, -2),lua_tostring(L, -1));
        const char* key = lua_tostring(L, -2);
        switch (hash_string(key)) {
            case HASH_enableAdaptiveBanner:
                enableAdaptiveBanner = lua_toboolean(L,-1);
                break;
            case HASH_enableUserPrivacyDialog:
                enableUserPrivacyDialog = lua_toboolean(L,-1);
                break;
            case HASH_userAgreementUrl:
                userAgreementUrl = lua_tostring(L, -1);
                break;
            case HASH_privacyPolicyUrl:
                privacyPolicyUrl = lua_tostring(L, -1);
                break;
            default:
                luaL_error(L, "unknown key:%s", key);
                break;
        }
       /* removes 'value'; keeps 'key' for next iteration */
       lua_pop(L, 1);
    }
    lua_pop(L,1); //remove table

    setAdBuildConfig(enableAdaptiveBanner,enableUserPrivacyDialog,userAgreementUrl,privacyPolicyUrl);
    return 0;
}

static int LuaInitMAS(lua_State* L){
     if(!lua_isstring(L,1)){
         luaL_error(L,"need app key string");
     }else{
        init(lua_tostring(L,1));
     }
    return 0;
}

}


static const luaL_reg Module_methods[] = {
    {"setAdBuildConfig", yodo1mas::LuaSetAdBuildConfig},
    {"init", yodo1mas::LuaInitMAS},
    {0, 0}
};


static void LuaInit(lua_State* L){
	int top = lua_gettop(L);
	// Register lua names
	luaL_register(L, MODULE_NAME, Module_methods);
	lua_pop(L, 1);
	assert(top == lua_gettop(L));
}



static dmExtension::Result InitializeMyExtension(dmExtension::Params* params) {
    yodo1mas::initExtension();
    LuaInit(params->m_L);
    printf("Registered %s Extension\n", MODULE_NAME);
    return dmExtension::RESULT_OK;
}

static dmExtension::Result FinalizeMyExtension(dmExtension::Params* params) {
    return dmExtension::RESULT_OK;
}

static dmExtension::Result UpdateMyExtension(dmExtension::Params* params){
    return dmExtension::RESULT_OK;
}

#else

dmExtension::Result InitializeMyExtension(dmExtension::Params* params) { return dmExtension::RESULT_OK;}
dmExtension::Result FinalizeMyExtension(dmExtension::Params* params) { return dmExtension::RESULT_OK;}
dmExtension::Result UpdateMyExtension(dmExtension::Params* params) { return dmExtension::RESULT_OK;}
#endif

DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, NULL, NULL, InitializeMyExtension, UpdateMyExtension, 0, FinalizeMyExtension)
