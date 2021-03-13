#ifndef UVC_DEVICE_H
#define UVC_DEVICE_H

#include "libuvc/libuvc.h"

namespace UVC
{
    class UVCDevice
    {
    public:
        UVCDevice();
        UVCDevice(const UVCDevice &other);
        ~UVCDevice();

        UVCDevice& operator=(const UVCDevice &other);

        void open();
        void close();

        bool isOpen() const;

        uvc_device_handle_t* handle();
    
    private:
        uvc_context_t *ctx;
        uvc_device_t *dev;
        uvc_device_handle_t *devh;
    };
}

#endif
