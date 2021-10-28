package com.d954mas.defold.yodo1.mas;

import android.app.Activity;
import android.content.Context;
import android.util.Log;

import androidx.annotation.NonNull;

import com.yodo1.mas.Yodo1Mas;
import com.yodo1.mas.error.Yodo1MasError;
import com.yodo1.mas.helper.model.Yodo1MasAdBuildConfig;


public class MASManager {
    private static final String TAG = "<MASManager>";
    private static Context context;
    private static Activity activity;


    public static void initExtension(Context context) {
        MASManager.context = context;
        MASManager.activity = (Activity) context;
    }


    public static void update() {

    }

    void setAdBuildConfig(boolean enableAdaptiveBanner, boolean enableUserPrivacyDialog,
                          String userAgreementUrl, String privacyPolicyUrl) {
        Yodo1MasAdBuildConfig.Builder b = new Yodo1MasAdBuildConfig.Builder().enableAdaptiveBanner(enableAdaptiveBanner)
                .enableUserPrivacyDialog(enableUserPrivacyDialog).userAgreementUrl(userAgreementUrl).privacyPolicyUrl(privacyPolicyUrl);
        Yodo1Mas.getInstance().setAdBuildConfig(b.build());
    }

    void init(String appkey) {
        Yodo1Mas.getInstance().init(activity, appkey, new Yodo1Mas.InitListener() {
            @Override
            public void onMasInitSuccessful() {
                Log.i(TAG, "onMasInitSuccessful");
            }

            @Override
            public void onMasInitFailed(@NonNull Yodo1MasError error) {
                Log.i(TAG, "onMasInitFailed:" + error);
            }
        });
    }


}