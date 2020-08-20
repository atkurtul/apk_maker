cd cpp
./cl.sh
cd ..
aapt package -f -M ./com/AndroidManifest.xml -I $ANDROID_SDK_ROOT/platforms/android-30/android.jar -F app0.apk cpp/libs
javac -target 8 -source 8 com/native_activity/R.java
dx --dex --output=classes.dex com/native_activity/R.class
aapt add -f app0.apk classes.dex
zipalign -f -v 4 app0.apk app.apk
signapk.sh app.apk
rm app0.apk
rm app.apk.idsig
rm classes.dex
adb uninstall com.native_activity
adb install ./app.apk
adb shell monkey -p com.native_activity 1
adb logcat -c
adb logcat -s native-activity:D vulkan:D ActivityManager:I libc:I DEBUG:I AndroidRuntime:I