

# Yodo1 MAS for Defold

[MAS](https://www.yodo1.com/monetization) is the world’s highest-performing game monetization platform.

Grow revenue, get paid quickly, and focus on what you love: making great games.

Installing MAS instantly powers up your game with 15 ad networks and mediators. MAS will always show the ads that bring you the most revenue.


**If you try it. Please use my [refferal link](https://mas.yodo1.com/register?referral_code=RP_EICLH85) :)**


[MAS Android sdk integration](https://developers.yodo1.com/knowledge-base/android-sdk-integration/)


This is experimental project.

WARNING

1. Not all api binding
2. Callback not save script instance.
3. Not test in production.
4. Banner and interstitial not visible in test mode(problem with sdk. For test ads sdk trying to get root view cast it to frame layaout and add ad view. 
It not worked with native view of defold).
5. Only android is supported.

If you like the extension you can support me on patreon.
It will help me make more items for defold.

[![](https://c5.patreon.com/external/logo/become_a_patron_button.png)](https://www.patreon.com/d954mas)




## Installation

__1)__ Add defold-yodo1-mas in your own project as a Defold library dependency. Open your game.project file and in the dependencies field under project add:
https://github.com/d954mas/defold-yodo1-mas/archive/refs/tags/0.5.0.zip

__2)__ Use /yodo1-mas/yodo1-mas.appmanifest.

__3)__ Add admob key from mas
``
[yodo1_mas]  
app_id_android = ca-app-pub-...
``


## EMMYLUA
Supports emmylua. yodo1_mas_header

## EXAMPLE
[main.script](https://github.com/d954mas/defold-yodo1-mas/blob/master/main/main.script)

## API
```lua
---@class Yodo1Mas  
local MAS = {}  
  
MAS.ALIGN = {  
  BannerLeft = 1,  
  BannerHorizontalCenter = 2,  
  BannerRight = 4,  
  BannerTop = 8,  
  BannerVerticalCenter = 16,  
  BannerBottom = 32,  
}  
  
  
---@class Yodo1MasAdBuildConfig  
---@field enableAdaptiveBanner boolean|nil  
---@field enableUserPrivacyDialog boolean|nil  
---@field userAgreementUrl string|nil  
---@field privacyPolicyUrl string|nil  
  
---@param config Yodo1MasAdBuildConfig  
function MAS.setAdBuildConfig(config) end  
  
---@param appKey string  
---@param cb_success function|nil  
---@param cb_error function|nil  
function MAS.init(appKey, cb_success, cb_error) end  
  
  
function MAS.setBannerListener(onAddOpened, onAddError, onAddClosed) end  
  
function MAS.setInterstitialListener(onAddOpened, onAddError, onAddClosed) end  
  
function MAS.setRewardListener(onAddOpened, onAdvertRewardEarned, onAddError, onAddClosed)  
end  
  
function MAS.showBannerAd(placement, align, offsetX, offsetY) end  
  
---@return boolean  
function MAS.isInterstitialAdLoaded() end  
  
---@param placement string|nil  
function MAS.showInterstitialAd(placement) end  
  
function MAS.isRewardedAdLoaded() end  
  
---@param placement string|nil  
function MAS.showRewardedAd(placement) end  
  
  
return MAS
```
