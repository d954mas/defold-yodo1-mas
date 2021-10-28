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

function M.callback(_, callback_id, message,data)
    print("yodo callback. id:" .. callback_id .. " message:" .. message)
    pprint(data)
end

function M.init(appKey,cb_success,cb_error)
    CHECKS("string","?function","?function")
    yodo1_mas_private.setCallback(M.callback)


    local cb_id = yodo1_mas_private.getCallbackID()
    M.callbacks[cb_id] = {
        id = "init",
        cb_success = cb_success,
        cb_error = cb_error
    }
    yodo1_mas_private.init(appKey)
end


yodo1_mas_private.setCallback(M.callback)

return M