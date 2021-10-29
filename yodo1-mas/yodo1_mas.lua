local CHECKS = require "yodo1-mas.checks"

local M = {}

M.callbacks = {}

local setAdBuildConfig_CHECKS = {
    enableAdaptiveBanner = "?boolean",
    enableUserPrivacyDialog = "?boolean",
    userAgreementUrl = "?string",
    privacyPolicyUrl = "?string",
}
function M.setAdBuildConfig(config)
    CHECKS(setAdBuildConfig_CHECKS)
    yodo1_mas_private.setAdBuildConfig(config)
end

function M.callback(callback_id, message, data)
    print("yodo callback. id:" .. callback_id .. " message:" .. message)
    local cb = M.callbacks[callback_id]
    if (message == "onMasInitSuccessful") then
        if (cb.cb_success) then cb.cb_success() end
    elseif (message == "onMasInitFailed") then
        if (cb.cb_error) then cb.cb_error(data) end
    elseif (message == "BannerOnAdOpened") then
        if (M.banner_listener and M.banner_listener.onAddOpened) then M.banner_listener.onAddOpened(data.event) end
    elseif (message == "BannerOnAdError") then
        if (M.banner_listener and M.banner_listener.onAddError) then M.banner_listener.onAddError(data.event, data.error) end
    elseif (message == "BannerAdClosed") then
        if (M.banner_listener and M.banner_listener.onAddClosed) then M.banner_listener.onAddClosed(data.event) end
    elseif (message == "InterstitialOnAdOpened") then
        if (M.interstitial_listener and M.interstitial_listener.onAddOpened) then M.interstitial_listener.onAddOpened(data.event) end
    elseif (message == "InterstitialOnAdError") then
        if (M.interstitial_listener and M.interstitial_listener.onAddError) then M.interstitial_listener.onAddError(data.event, data.error) end
    elseif (message == "InterstitialOnAdClosed") then
        if (M.interstitial_listener and M.interstitial_listener.onAddClosed) then M.interstitial_listener.onAddClosed(data.event) end
    elseif (message == "RewardOnAdOpened") then
        if (M.reward_listener and M.reward_listener.onAddOpened) then M.reward_listener.onAddOpened(data.event) end
    elseif (message == "RewardOnAdError") then
        if (M.reward_listener and M.reward_listener.onAddError) then M.reward_listener.onAddError(data.event, data.error) end
    elseif (message == "RewardOnAdClosed") then
        if (M.reward_listener and M.reward_listener.onAddClosed) then M.reward_listener.onAddClosed(data.event) end
    elseif (message == "RewardOnAdvertRewardEarned") then
        if (M.reward_listener and M.reward_listener.onAdvertRewardEarned) then M.reward_listener.onAdvertRewardEarned(data.event) end
    end
end

function M.init(appKey, cb_success, cb_error)
    CHECKS("string", "?function", "?function")
    local cb_id = yodo1_mas_private.getCallbackID()
    M.callbacks[cb_id] = {
        id = "init",
        cb_success = cb_success,
        cb_error = cb_error
    }
    yodo1_mas_private.init(appKey)
end

function M.setBannerListener(onAddOpened, onAddError, onAddClosed)
    M.banner_listener = {
        onAddOpened = onAddOpened,
        onAddError = onAddError,
        onAddClosed = onAddClosed,
    }
end
function M.setInterstitialListener(onAddOpened, onAddError, onAddClosed)
    M.interstitial_listener = {
        onAddOpened = onAddOpened,
        onAddError = onAddError,
        onAddClosed = onAddClosed,
    }
end

function M.setRewardListener(onAddOpened, onAdvertRewardEarned, onAddError, onAddClosed)
    M.reward_listener = {
        onAddOpened = onAddOpened,
        onAdvertRewardEarned = onAdvertRewardEarned,
        onAddError = onAddError,
        onAddClosed = onAddClosed,
    }
end

function M.showBannerAd(placement, align, offsetX, offsetY)
    align = align or bit.bor(yodo1_mas_private.Align.BannerBottom, yodo1_mas_private.Align.BannerHorizontalCenter)
    offsetX = align or 0
    offsetY = align or 0
    yodo1_mas_private.showBannerAd(placement, align, offsetX, offsetY)
end

function M.isInterstitialAdLoaded()
    return yodo1_mas_private.isInterstitialAdLoaded()
end

function M.showInterstitialAd(placement)
    return yodo1_mas_private.showInterstitialAd(placement)
end

function M.isRewardedAdLoaded()
    return yodo1_mas_private.isRewardedAdLoaded()
end

function M.showRewardedAd(placement)
    return yodo1_mas_private.showRewardedAd(placement)
end

yodo1_mas_private.setCallback(M.callback)

return M