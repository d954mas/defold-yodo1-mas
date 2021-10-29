// myextension.cpp
// Extension lib defines
#define EXTENSION_NAME yodo1_mas_private
#define LIB_NAME "yodo1_mas_private"
#define MODULE_NAME "yodo1_mas_private"
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

static int LuaShowBannerAd(lua_State* L){
    const char* placement = NULL;
    if(lua_isstring(L,1)){
        placement = lua_tostring(L,1);
    }
    showBannerAd(placement,lua_tonumber(L,2),lua_tonumber(L,3),lua_tonumber(L,4));
    return 0;
}

static int LuaGetCallbackId(lua_State* L){
    lua_pushnumber(L, getCallbackId());
    return 1;
}

static int Lua_SetCallback(lua_State* L){
    DM_LUA_STACK_CHECK(L, 0);
    yodo1mas::SetLuaCallback(L, 1);
    return 0;
}

static int LuaIsInterstitialAdLoaded(lua_State* L){
    bool result = isInterstitialAdLoaded();
    lua_pushboolean(L,result);
    return 1;
}

static int LuaShowInterstitialAd(lua_State* L){
    const char* placement = NULL;
    if(lua_isstring(L,1)){
        placement = lua_tostring(L,1);
    }
    showInterstitialAd(placement);
    return 0;
}

static int LuaIsRewardedAdLoaded(lua_State* L){
    bool result = isRewardedAdLoaded();
    lua_pushboolean(L,result);
    return 1;
}

static int LuaShowRewardedAd(lua_State* L){
    const char* placement = NULL;
    if(lua_isstring(L,1)){
        placement = lua_tostring(L,1);
    }
    showRewardedAd(placement);
    return 0;
}

}


static const luaL_reg Module_methods[] = {
    {"setAdBuildConfig", yodo1mas::LuaSetAdBuildConfig},
    {"getCallbackID", yodo1mas::LuaGetCallbackId},
    {"setCallback", yodo1mas::Lua_SetCallback},
    {"showBannerAd", yodo1mas::LuaShowBannerAd},
    {"isInterstitialAdLoaded", yodo1mas::LuaIsInterstitialAdLoaded},
    {"showInterstitialAd", yodo1mas::LuaShowInterstitialAd},
    {"isRewardedAdLoaded", yodo1mas::LuaIsRewardedAdLoaded},
    {"showRewardedAd", yodo1mas::LuaShowRewardedAd},
    {"init", yodo1mas::LuaInitMAS},
    {0, 0}
};


static void LuaInit(lua_State* L){
	int top = lua_gettop(L);
	// Register lua names
	luaL_register(L, MODULE_NAME, Module_methods);

	lua_newtable(L);
            lua_pushnumber(L, 1);
            lua_setfield(L, -2, "BannerLeft");
            lua_pushnumber(L, 2);
            lua_setfield(L, -2, "BannerHorizontalCenter");
            lua_pushnumber(L, 4);
            lua_setfield(L, -2, "BannerRight");
            lua_pushnumber(L, 8);
            lua_setfield(L, -2, "BannerTop");
            lua_pushnumber(L, 16);
            lua_setfield(L, -2, "BannerVerticalCenter");
            lua_pushnumber(L, 32);
            lua_setfield(L, -2, "BannerBottom");
    lua_setfield(L, -2, "Align");

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
    yodo1mas::finalizeExtension(params->m_L);
    return dmExtension::RESULT_OK;
}

static dmExtension::Result UpdateMyExtension(dmExtension::Params* params){
    yodo1mas::updateExtension(params->m_L);
    return dmExtension::RESULT_OK;
}

#else

dmExtension::Result InitializeMyExtension(dmExtension::Params* params) { return dmExtension::RESULT_OK;}
dmExtension::Result FinalizeMyExtension(dmExtension::Params* params) { return dmExtension::RESULT_OK;}
dmExtension::Result UpdateMyExtension(dmExtension::Params* params) { return dmExtension::RESULT_OK;}
#endif

DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, NULL, NULL, InitializeMyExtension, UpdateMyExtension, 0, FinalizeMyExtension)
