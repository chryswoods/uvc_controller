g++ --std=c++17 main.cpp controller.cpp \
                uvcdevice.cpp options.cpp \
                /usr/local/lib/libuvc.dylib -o uvc_controller
