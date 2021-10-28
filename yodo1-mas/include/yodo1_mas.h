#ifndef YODO1_MAS
#define YODO1_MAS

#if defined(DM_PLATFORM_ANDROID)

#include <dmsdk/sdk.h>
#include "djni.h"

namespace yodo1mas {

struct CallbackData{
    int callbackId;
    char* message;
    char* data;
};

int getCallbackId();
void callback_AddToQueue(int callbackId,const char* message,const char* data);
void SetLuaCallback(lua_State* L, int pos);

void initExtension();
void finalizeExtension();
void updateExtension();
void init(const char* appKey);

void setAdBuildConfig(bool enableAdaptiveBanner, bool enableUserPrivacyDialog, const char* userAgreementUrl, const char* privacyPolicyUrl);



}
#endif

#endif