#if defined(DM_PLATFORM_ANDROID)

#include <dmsdk/sdk.h>
#include "yodo1_mas.h"
#include "djni.h"
#include <stdlib.h>

namespace yodo1mas {

static int CALLBACK_ID = 1;
static dmArray<CallbackData> m_callbacksQueue;
static dmMutex::HMutex m_mutex;
static dmScript::LuaCallbackInfo* m_luaCallback = 0x0;

static void DestroyCallback(){
    if (m_luaCallback != 0x0) {
        dmScript::DestroyCallback(m_luaCallback);
        m_luaCallback = 0x0;
    }
}

void SetLuaCallback(lua_State* L, int pos){
    int type = lua_type(L, pos);
    if (type == LUA_TNONE || type == LUA_TNIL){
        DestroyCallback();
    }
    else{
        m_luaCallback = dmScript::CreateCallback(L, pos);
    }
}


static void callbackResultJNI(JNIEnv * env, jclass cls, jint jCallbackId, jstring jmsg){
    const char* message = env->GetStringUTFChars(jmsg, 0);
    callback_AddToQueue(jCallbackId,message, NULL);
    env->ReleaseStringUTFChars(jmsg, message);
}

static void callbackResultJsonJNI(JNIEnv * env, jclass cls, jint jCallbackId, jstring jmsg, jstring jjson){
    const char* message = env->GetStringUTFChars(jmsg, 0);
    const char* json = env->GetStringUTFChars(jjson, 0);
    callback_AddToQueue(jCallbackId,message, json);
    env->ReleaseStringUTFChars(jjson, json);
    env->ReleaseStringUTFChars(jmsg, message);
}

static void RegisterNatives(JNIEnv* env) {
    JNINativeMethod nativeMethods[] = {
        {"callbackResult", "(ILjava/lang/String;)V", (void*)&callbackResultJNI},
        {"callbackResultJson", "(ILjava/lang/String;Ljava/lang/String;)V", (void*)&callbackResultJsonJNI}
    };

	jclass jclass_class = yodo1masDjni::GetClass(env, "com.d954mas.defold.yodo1.mas.MASManager");
    env->RegisterNatives( jclass_class , nativeMethods, sizeof(nativeMethods) / sizeof(nativeMethods[0]));
    env->DeleteLocalRef( jclass_class );
}

void initExtension(){
    JNIEnv* env = yodo1masDjni::env();
    jclass cls = yodo1masDjni::GetClass(env, "com.d954mas.defold.yodo1.mas.MASManager");
    jmethodID method = env->GetStaticMethodID(cls, "initExtension", "(Landroid/content/Context;)V");
    env->CallStaticVoidMethod(cls, method, dmGraphics::GetNativeAndroidActivity());
    env->DeleteLocalRef(cls);
    RegisterNatives(env);
    m_mutex = dmMutex::New();
}

void finalizeExtension(){
    dmMutex::Delete(m_mutex);
    DestroyCallback();
}

static void InvokeCallback(int callbackId, const char* message, const char*json){
    if (!dmScript::IsCallbackValid(m_luaCallback)){
        dmLogError("yodo1mas callback is invalid.");
        return;
    }

    lua_State* L = dmScript::GetCallbackLuaContext(m_luaCallback);
    int top = lua_gettop(L);
    if (!dmScript::SetupCallback(m_luaCallback)){
        return;
    }

    lua_pushnumber(L, callbackId);
    lua_pushstring(L, message);
    if(json!= NULL){
        bool is_fail = false;
        dmJson::Document doc;
        dmJson::Result r = dmJson::Parse(json, &doc);
        if (r == dmJson::RESULT_OK && doc.m_NodeCount > 0){
            char error_str_out[128];
            if (dmScript::JsonToLua(L, &doc, 0, error_str_out, sizeof(error_str_out)) < 0){
                dmLogError("Failed converting object JSON to Lua; %s", error_str_out);
                is_fail = true;
            }
        }else{
            dmLogError("Failed to parse JSON object(%d): (%s)", r, json);
            is_fail = true;
        }
        dmJson::Free(&doc);
        if (is_fail){
            lua_pop(L, 3);
            assert(top == lua_gettop(L));
            return;
        }
    }else{
        lua_pushnil(L);
    }


    int number_of_arguments = 4;

    int ret = dmScript::PCall(L, number_of_arguments, 0);
    (void)ret;
    dmScript::TeardownCallback(m_luaCallback);

    assert(top == lua_gettop(L));
}

void updateExtension(){
    if (m_callbacksQueue.Empty()){
        return;
    }

    DM_MUTEX_SCOPED_LOCK(m_mutex);

    for(uint32_t i = 0; i != m_callbacksQueue.Size(); ++i)
    {
        CallbackData* data = &m_callbacksQueue[i];
        InvokeCallback(data->callbackId, data->message, data->data);

        free(data->message);
        if(data->data)
        {
            free(data->data);
            data->data = 0;
        }
    }
    m_callbacksQueue.SetSize(0);
}

int getCallbackId(){
    return CALLBACK_ID;
}

void callback_AddToQueue(int callbackId,const char* message, const char* data){
    DM_MUTEX_SCOPED_LOCK(m_mutex);
    CallbackData cbData;
    cbData.callbackId = callbackId;
    cbData.message = strdup(message);
    cbData.data = data ? strdup(data) : NULL;

    if(m_callbacksQueue.Full()) {
        m_callbacksQueue.OffsetCapacity(1);
    }
    m_callbacksQueue.Push(cbData);
}

void init(const char* appKey){
    JNIEnv* env = yodo1masDjni::env();
    jclass cls = yodo1masDjni::GetClass(env, "com.d954mas.defold.yodo1.mas.MASManager");
    jmethodID method = env->GetStaticMethodID(cls, "init", "(ILjava/lang/String;)V");

    jint jCallbackId = CALLBACK_ID;
    CALLBACK_ID++;

    jstring jString = env->NewStringUTF(appKey);
    env->CallStaticVoidMethod(cls,method, jCallbackId, jString);

    env->DeleteLocalRef(cls);
}

void setAdBuildConfig(bool enableAdaptiveBanner, bool enableUserPrivacyDialog, const char* userAgreementUrl, const char* privacyPolicyUrl){
    JNIEnv* env = yodo1masDjni::env();
    jclass cls = yodo1masDjni::GetClass(env, "com.d954mas.defold.yodo1.mas.MASManager");
    jmethodID method = env->GetStaticMethodID(cls, "setAdBuildConfig", "(ZZLjava/lang/String;Ljava/lang/String;)V");
    jboolean jEnableAdaptiveBanner = enableAdaptiveBanner;
    jboolean jEnableUserPrivacyDialog = jEnableAdaptiveBanner;
    jstring jUserAgreementUrl = NULL;
    if(userAgreementUrl!= NULL){
        jUserAgreementUrl=  env->NewStringUTF(userAgreementUrl);
    }
  jstring jPrivacyPolicyUrl = NULL;
    if(privacyPolicyUrl!= NULL){
        jPrivacyPolicyUrl = env->NewStringUTF(privacyPolicyUrl);
    }

    env->CallStaticVoidMethod(cls,method, jEnableAdaptiveBanner, jEnableUserPrivacyDialog,jUserAgreementUrl,jPrivacyPolicyUrl);

    env->DeleteLocalRef(cls);
}




}
#endif