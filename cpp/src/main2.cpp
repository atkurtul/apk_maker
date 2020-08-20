#include "android_native_app_glue.h"
#include "android/looper.h"

void android_main(struct android_app* state) {

    while (true) {
        // Read all pending events.
        int ident;
        int events;
        struct android_poll_source* source;

        // If not animating, we will block forever waiting for events.
        // If animating, we loop until all events are read, then continue
        // to draw the next frame of animation.
        while ((ident=ALooper_pollAll(-1, nullptr, &events,(void**)&source)) >= 0) 
        {

        }
    }
}
