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

function M.showBannerAd(placement, align, offsetX, offsetY)
    align = align or bit.bor(yodo1_mas_private.Align.BannerBottom ,yodo1_mas_private.Align.BannerHorizontalCenter)
    offsetX = align or 0
    offsetY = align or 0
    yodo1_mas_private.showBannerAd(placement, align, offsetX, offsetY)
end

yodo1_mas_private.setCallback(M.callback)

return M