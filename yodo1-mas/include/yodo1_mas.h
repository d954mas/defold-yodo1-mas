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
void finalizeExtension(lua_State* L);
void updateExtension(lua_State* L);
void init(const char* appKey);

void setAdBuildConfig(bool enableAdaptiveBanner, bool enableUserPrivacyDialog, const char* userAgreementUrl, const char* privacyPolicyUrl);
void showBannerAd(const char* placement, int align, int offsetX, int offsetY);

bool isInterstitialAdLoaded();
void showInterstitialAd(const char* placement);

bool isRewardedAdLoaded();
void showRewardedAd(const char* placement);



}
#endif

#endif