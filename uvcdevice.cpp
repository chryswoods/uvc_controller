
#include "uvcdevice.h"

#include <iostream>

using namespace UVC;

UVCDevice::UVCDevice() : ctx(0), dev(0), devh(0)
{}

UVCDevice::UVCDevice(const UVCDevice &other)
          : ctx(other.ctx), dev(other.dev), devh(other.devh)
{}

UVCDevice::~UVCDevice()
{}

UVCDevice& UVCDevice::operator=(const UVCDevice &other)
{
    if (this != &other)
    {
        ctx = other.ctx;
        dev = other.dev;
        devh = other.devh;
    }

    return *this;
}

void UVCDevice::open()
{
    if (ctx != 0) return;

    uvc_error_t err;
    err = uvc_init(&ctx, NULL);

    if (err != 0) {
        uvc_perror(err, "uvc_init");
        this->close();
        return;
    }

    /* Locates the first attached UVC device, stores in dev */
    err = uvc_find_device(
                    ctx, &dev,
                    0, 0, NULL); 
                    /* filter devices: vendor_id, product_id, "serial_num" */
    
    if (err != 0) {
        uvc_perror(err, "uvc_find_device"); /* no devices found */
        this->close();
        return;
    }

    /* Try to open the device: requires exclusive access */
    err = uvc_open(dev, &devh);
    if (err != 0) {
        uvc_perror(err, "uvc_open"); /* unable to open device */
        this->close();
        return;
    }
}

void UVCDevice::close()
{
    if (devh)
    {
        uvc_close(devh);
        devh = 0;
    }

    if (dev)
    {
        uvc_unref_device(dev);
        dev = 0;
    }

    if (ctx)
    {
        uvc_exit(ctx);
    }
}

bool UVCDevice::isOpen() const
{
    return devh != 0;
}

uvc_device_handle_t* UVCDevice::handle()
{
    if (devh == 0)
    {
        throw std::runtime_error("Cannot get handle as device not connected.");
    }

    return devh;
}
