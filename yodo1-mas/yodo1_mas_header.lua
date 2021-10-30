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