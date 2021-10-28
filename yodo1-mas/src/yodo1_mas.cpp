#if defined(DM_PLATFORM_ANDROID)

#include <dmsdk/sdk.h>
#include "yodo1_mas.h"
#include "djni.h"

namespace yodo1mas {

void initExtension(){
    JNIEnv* env = yodo1masDjni::env();
    jclass cls = yodo1masDjni::GetClass(env, "com.d954mas.defold.yodo1.mas.MASManager");
    jmethodID method = env->GetStaticMethodID(cls, "initExtension", "(Landroid/content/Context;)V");
    env->CallStaticVoidMethod(cls, method, dmGraphics::GetNativeAndroidActivity());
}

void init(const char* appKey){
    JNIEnv* env = yodo1masDjni::env();
    jclass cls = yodo1masDjni::GetClass(env, "com.d954mas.defold.yodo1.mas.MASManager");
    jmethodID method = env->GetStaticMethodID(cls, "init", "(Ljava/lang/String;)V");

    jstring jString = env->NewStringUTF(appKey);
    env->CallStaticVoidMethod(cls, method,jString);
}

void setAdBuildConfig(bool enableAdaptiveBanner, bool enableUserPrivacyDialog, const char* userAgreementUrl, const char* privacyPolicyUrl){

}



}
#endif