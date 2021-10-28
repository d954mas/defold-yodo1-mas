#ifndef YODO1_MAS
#define YODO1_MAS

#if defined(DM_PLATFORM_ANDROID)

#include <dmsdk/sdk.h>
#include "djni.h"

namespace yodo1mas {

void initExtension();
void init(const char* appKey);

void setAdBuildConfig(bool enableAdaptiveBanner, bool enableUserPrivacyDialog, const char* userAgreementUrl, const char* privacyPolicyUrl);


}
#endif

#endif