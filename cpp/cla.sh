export NDK_LIBS_OUT=./libs/lib
export NDK_PROJECT_PATH=.
export CURRENT_ABI=$1
export VALIDATION_LAYER=$ANDROID_NDK_HOME/sources/third_party/vulkan/src/build-android/jniLibs/$CURRENT_ABI/libVkLayer_khronos_validation.so
ndk-build NDK_APPLICATION_MK=./Application.mk
cp $VALIDATION_LAYER ./libs/lib/$CURRENT_ABI