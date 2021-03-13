
#include "options.h"
#include "uvcdevice.h"
#include "controller.h"

#include <iostream>

using namespace UVC;

Options::Options()
{}

Options::Options(UVCDevice device)
{
    this->populate(device);
}

Options::~Options()
{}

template<class VALUE_TYPE, class FUNC>
uvc_get_function_t create_get_function(FUNC *func)
{
    auto f = [=](UVCDevice device, uvc_req_code code){
        VALUE_TYPE result;
        uvc_error_t err = (*func)(device.handle(), &result, code);

        if (err != 0)
        {
            uvc_perror(err, "uvc_get_X");
            throw std::runtime_error("Option not supported");
        }

        int return_val = result;
        return return_val;
    };

    return f;
}

template<class VALUE_TYPE, class FUNC>
uvc_set_function_t create_set_function(FUNC *func)
{
    auto f = [=](UVCDevice device, int value){
        VALUE_TYPE val = value;
        uvc_error_t err = (*func)(device.handle(), val);

        if (err != 0)
        {
            uvc_perror(err, "uvc_set_X");
            throw std::runtime_error("Option not supported");
        }

    };

    return f;
}

std::string Options::toString() const
{
    std::string out;

    for (auto opt : opts)
    {
        out += opt.second.toString() + "\n";
    }

    return out;
}

void Options::populate(UVCDevice device)
{
    opts = std::map<std::string, Controller>();

    opts["gamma"] = Controller("gamma", device,
                               create_get_function<uint16_t>(&uvc_get_gamma),
                               create_set_function<uint16_t>(&uvc_set_gamma));

    opts["scanning_mode"] = Controller("scanning_mode", device,
                               create_get_function<uint8_t>(&uvc_get_scanning_mode),
                               create_set_function<uint8_t>(&uvc_set_scanning_mode));

    opts["ae_mode"] = Controller("ae_mode", device,
                               create_get_function<uint8_t>(&uvc_get_ae_mode),
                               create_set_function<uint8_t>(&uvc_set_ae_mode));

    opts["ae_priority"] = Controller("ae_priority", device,
                               create_get_function<uint8_t>(&uvc_get_ae_priority),
                               create_set_function<uint8_t>(&uvc_set_ae_priority));

    opts["exposure_abs"] = Controller("exposure_abs", device,
                               create_get_function<uint32_t>(&uvc_get_exposure_abs),
                               create_set_function<uint32_t>(&uvc_set_exposure_abs));

    opts["exposure_rel"] = Controller("exposure_rel", device,
                               create_get_function<int8_t>(&uvc_get_exposure_rel),
                               create_set_function<int8_t>(&uvc_set_exposure_rel));

    opts["focus_abs"] = Controller("focus_abs", device,
                               create_get_function<uint16_t>(&uvc_get_focus_abs),
                               create_set_function<uint16_t>(&uvc_set_focus_abs));

    opts["zoom_abs"] = Controller("zoom_abs", device,
                               create_get_function<uint16_t>(&uvc_get_zoom_abs),
                               create_set_function<uint16_t>(&uvc_set_zoom_abs));

    opts["brightness"] = Controller("brightness", device,
                               create_get_function<int16_t>(&uvc_get_brightness),
                               create_set_function<int16_t>(&uvc_set_brightness));

    opts["backlight compensation"] = Controller("backlight compensation", device,
                               create_get_function<uint16_t>(&uvc_get_backlight_compensation),
                               create_set_function<uint16_t>(&uvc_set_backlight_compensation));

}
