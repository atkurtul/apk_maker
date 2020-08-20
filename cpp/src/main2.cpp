#include "android_native_app_glue.h"
#include "android/log.h"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))

static void handle_proc(struct android_app* app, int32_t cmd){
  LOGI("Handling proc %d", cmd);
  switch (cmd) {
    case APP_CMD_INIT_WINDOW:
    case APP_CMD_TERM_WINDOW:
    case APP_CMD_GAINED_FOCUS:
    case APP_CMD_LOST_FOCUS:
    default: break;
  }
}

static int32_t input_proc(struct android_app* app, AInputEvent* event) {
    int32_t type = AInputEvent_getType(event);
    LOGI("Got input of type %d", type);
    return 0;
}

#include "dlfcn.h"
#include "vulkan/vulkan.h"
#include "vector"
using namespace std;
#define load_proc(fn) (PFN_##fn)proc_addr(0, #fn)

void android_main(struct android_app* state) {
    void* lib = dlopen("libvulkan.so", RTLD_NOW | RTLD_LOCAL);
    if(!lib) {
        LOGI("Cant find vulkan");
        return;
    }
    auto proc_addr = (PFN_vkGetInstanceProcAddr)dlsym(lib, "vkGetInstanceProcAddr");
    if(!proc_addr) {
        LOGI("Proc addr not found");
        return;
    }

    LOGI("Proc is %p", proc_addr);

    auto create_instance = load_proc(vkCreateInstance);
    auto enum_ext = load_proc(vkEnumerateInstanceExtensionProperties);
    auto layer_props = load_proc(vkEnumerateInstanceLayerProperties);
    LOGI("create_instance is %p", create_instance);
    vector<const char*> extensions = {"VK_KHR_surface", "VK_KHR_android_surface" };
    {
        uint32_t count = 0;
        enum_ext(0, &count, 0);
        vector<VkExtensionProperties> props(count);
        enum_ext(0, &count, props.data());
        for(auto& p : props) {
            LOGI("%s", p.extensionName);
        }
        layer_props(&count, 0);
        vector<VkLayerProperties> lay(count);
        layer_props(&count, lay.data());
        for(auto& p : lay) {
            LOGI("%s", p.layerName);
        }
        if(lay.empty()) LOGI("No layers found");
    }
    VkInstanceCreateInfo info = { VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
    info.enabledExtensionCount;
    info.ppEnabledExtensionNames;
    state->onAppCmd = handle_proc;
    state->onInputEvent = input_proc;
    int i = 0;
    while (true) {
        // Read all pending events.
        int ident;
        int events;
        struct android_poll_source* source;
        LOGI("POLLING%d", i++);
        // If not animating, we will block forever waiting for events.
        // If animating, we loop until all events are read, then continue
        // to draw the next frame of animation.
        while ((ident = ALooper_pollAll(-1, 0, &events, (void**)&source)) >= 0) 
        {
            if(state->destroyRequested)
                return;
        }
    }
}
