::adb shell pm uninstall com.d954mas.yodo1mas.test.dev
adb install -r "C:\Users\d954m\Desktop\armv7-android\yodo1-mas\yodo1-mas.apk"
adb shell monkey -p com.com.d954mas.yodo1mas.test.dev -c android.intent.category.LAUNCHER 1
pause
