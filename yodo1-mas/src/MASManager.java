package com.d954mas.defold.yodo1.mas;

import android.app.Activity;
import android.content.Context;
import android.util.Log;

import androidx.annotation.NonNull;

import com.yodo1.mas.Yodo1Mas;
import com.yodo1.mas.error.Yodo1MasError;
import com.yodo1.mas.event.Yodo1MasAdEvent;
import com.yodo1.mas.helper.model.Yodo1MasAdBuildConfig;

import org.json.JSONException;
import org.json.JSONObject;


public class MASManager {
    private static final String TAG = "<MASManager>";
    private static Context context;
    private static Activity activity;

    public static native void callbackResult(int callbackId, String message);

    public static native void callbackResultJson(int callbackId, String message, String json);


    public static void initExtension(Context context) {
        MASManager.context = context;
        MASManager.activity = (Activity) context;
        Yodo1Mas.getInstance().setBannerListener(new Yodo1Mas.BannerListener() {
            @Override
            public void onAdOpened(@NonNull Yodo1MasAdEvent event) {
                JSONObject result = new JSONObject();
                try {
                    result.put("event", event.getJSONObject());
                } catch (JSONException e) {
                    e.printStackTrace();
                }
                callbackResultJson(-1, "BannerOnAdOpened", result.toString());
            }

            @Override
            public void onAdError(@NonNull Yodo1MasAdEvent event, @NonNull Yodo1MasError error) {
                JSONObject result = new JSONObject();
                try {
                    result.put("event", event.getJSONObject());
                    result.put("error", error.getJsonObject());
                } catch (JSONException e) {
                    e.printStackTrace();
                }
                callbackResultJson(-1, "BannerOnAdError", result.toString());
            }

            @Override
            public void onAdClosed(@NonNull Yodo1MasAdEvent event) {
                JSONObject result = new JSONObject();
                try {
                    result.put("event", event.getJSONObject());
                } catch (JSONException e) {
                    e.printStackTrace();
                }
                callbackResultJson(-1, "BannerOnAdClosed", result.toString());

            }
        });

        Yodo1Mas.getInstance().setInterstitialListener(new Yodo1Mas.InterstitialListener() {
            @Override
            public void onAdOpened(@NonNull Yodo1MasAdEvent event) {
                JSONObject result = new JSONObject();
                try {
                    result.put("event", event.getJSONObject());
                } catch (JSONException e) {
                    e.printStackTrace();
                }
                callbackResultJson(-1, "InterstitialOnAdOpened", result.toString());
            }

            @Override
            public void onAdError(@NonNull Yodo1MasAdEvent event, @NonNull Yodo1MasError error) {
                JSONObject result = new JSONObject();
                try {
                    result.put("event", event.getJSONObject());
                    result.put("error", error.getJsonObject());
                } catch (JSONException e) {
                    e.printStackTrace();
                }
                callbackResultJson(-1, "InterstitialOnAdError", result.toString());
            }

            @Override
            public void onAdClosed(@NonNull Yodo1MasAdEvent event) {
                JSONObject result = new JSONObject();
                try {
                    result.put("event", event.getJSONObject());
                } catch (JSONException e) {
                    e.printStackTrace();
                }
                callbackResultJson(-1, "InterstitialOnAdClosed", result.toString());
            }
        });

        Yodo1Mas.getInstance().setRewardListener(new Yodo1Mas.RewardListener() {
            @Override
            public void onAdOpened(@NonNull Yodo1MasAdEvent event) {
                JSONObject result = new JSONObject();
                try {
                    result.put("event", event.getJSONObject());
                } catch (JSONException e) {
                    e.printStackTrace();
                }
                callbackResultJson(-1, "RewardOnAdOpened", result.toString());
            }

            @Override
            public void onAdvertRewardEarned(@NonNull Yodo1MasAdEvent event) {
                JSONObject result = new JSONObject();
                try {
                    result.put("event", event.getJSONObject());
                } catch (JSONException e) {
                    e.printStackTrace();
                }
                callbackResultJson(-1, "RewardOnAdvertRewardEarned", result.toString());
            }

            @Override
            public void onAdError(@NonNull Yodo1MasAdEvent event, @NonNull Yodo1MasError error) {
                JSONObject result = new JSONObject();
                try {
                    result.put("event", event.getJSONObject());
                    result.put("error", error.getJsonObject());
                } catch (JSONException e) {
                    e.printStackTrace();
                }
                callbackResultJson(-1, "RewardOnAdError", result.toString());
            }

            @Override
            public void onAdClosed(@NonNull Yodo1MasAdEvent event) {
                JSONObject result = new JSONObject();
                try {
                    result.put("event", event.getJSONObject());
                } catch (JSONException e) {
                    e.printStackTrace();
                }
                callbackResultJson(-1, "RewardOnAdClosed", result.toString());
            }
        });
    }


    static void setAdBuildConfig(boolean enableAdaptiveBanner, boolean enableUserPrivacyDialog,
                                 String userAgreementUrl, String privacyPolicyUrl) {
        Yodo1MasAdBuildConfig.Builder b = new Yodo1MasAdBuildConfig.Builder().enableAdaptiveBanner(enableAdaptiveBanner)
                .enableUserPrivacyDialog(enableUserPrivacyDialog).userAgreementUrl(userAgreementUrl).privacyPolicyUrl(privacyPolicyUrl);
        Yodo1Mas.getInstance().setAdBuildConfig(b.build());
    }

    static void init(int callbackId, String appkey) {
        Log.i(TAG, "init");
        Yodo1Mas.getInstance().init(activity, appkey, new Yodo1Mas.InitListener() {
            @Override
            public void onMasInitSuccessful() {
                Log.i(TAG, "onMasInitSuccessful");
                callbackResult(callbackId, "onMasInitSuccessful");
            }

            @Override
            public void onMasInitFailed(@NonNull Yodo1MasError error) {
                Log.i(TAG, "onMasInitFailed:" + error);
                callbackResultJson(callbackId, "onMasInitFailed", error.getJsonObject().toString());
            }
        });
    }

    static void showBannerAd(String placement, int align, int offsetX, int offsetY) {
        Yodo1Mas.getInstance().showBannerAd(activity, placement, align, offsetX, offsetY);
    }


    static void showInterstitialAd(String placement) {
        Yodo1Mas.getInstance().showInterstitialAd(activity, placement);
    }

    static boolean isInterstitialAdLoaded() {
        return Yodo1Mas.getInstance().isInterstitialAdLoaded();
    }

    static void showRewardedAd(String placement) {
        Yodo1Mas.getInstance().showRewardedAd(activity, placement);
    }

    static boolean isRewardedAdLoaded() {
        return Yodo1Mas.getInstance().isRewardedAdLoaded();
    }


}