LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := native-activity
LOCAL_C_INCLUDES := $(ANDROID_NDK_HOME)/sources/android/native_app_glue
LOCAL_SRC_FILES := src/main2.cpp
LOCAL_LDFLAGS := -landroid -lEGL -lGLESv1_CM -llog
LOCAL_STATIC_LIBRARIES := android_native_app_glue
include $(BUILD_SHARED_LIBRARY)
$(call import-module,android/native_app_glue)
