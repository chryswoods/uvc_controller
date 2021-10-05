
#include "options.h"
#include "controller.h"

#include <iostream>
#include <fstream>

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
            //uvc_perror(err, "uvc_get_X");
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
            //uvc_perror(err, "uvc_set_X");
            throw std::runtime_error("Option not supported");
        }

    };

    return f;
}

Controller Options::getOption(int i) const
{
    for (auto opt : opts)
    {
        if (opt.second.isAvailable())
        {
            i -= 1;
            if (i == 0){
                return opt.second;
            }
        }
    }

    throw std::runtime_error("Invalid option");
}

std::string Options::toString(int s) const
{
    std::string out;

    int i = 1;

    for (auto opt : opts)
    {
        if (opt.second.isAvailable())
        {
            if ( s == 0 || s == i )
            out += "      [" + std::to_string(i) + "]: " + 
                    opt.second.toString() + "\n";
            
            i += 1;
        }
    }

    return out;
}

void Options::loadFromFile(const std::string &filename)
{
    std::ifstream file;
    file.open(filename);

    std::string option, value;
    while (std::getline(file, option))
    {
        if (not std::getline(file, value))
        {
            break;
        }

        try
        {
            opts[option].setCurrent(std::stoi(value));
            std::cout << "Set " << option << " to " << value << std::endl;
        }
        catch(const std::exception &e)
        {
            std::cout << "Cannot set " << option << " to " << value << std::endl;
        }
    }

    file.close();
}

void Options::saveToFile(const std::string &filename) const
{
    std::ofstream file;
    file.open(filename);

    for (auto opt : opts)
    {
        if (opt.second.isAvailable())
        {
            file << opt.second.getName() << "\n" <<
                    opt.second.getCurrent() << "\n";
        }
    }

    file.close();
}

void Options::add(Controller c)
{
    if (c.isAvailable())
    {
        opts[c.getName()] = c;
    }
}

void Options::rescan()
{
    if (_device.isOpen())
        this->populate(_device);
}

void Options::populate(UVCDevice device)
{
    opts = std::map<std::string, Controller>();

    add(Controller("gamma", device,
                    create_get_function<uint16_t>(&uvc_get_gamma),
                    create_set_function<uint16_t>(&uvc_set_gamma)));

    add(Controller("scanning_mode", device,
                    create_get_function<uint8_t>(&uvc_get_scanning_mode),
                    create_set_function<uint8_t>(&uvc_set_scanning_mode)));

    add(Controller("ae_mode", device,
                    create_get_function<uint8_t>(&uvc_get_ae_mode),
                    create_set_function<uint8_t>(&uvc_set_ae_mode)));

    add(Controller("ae_priority", device,
                    create_get_function<uint8_t>(&uvc_get_ae_priority),
                    create_set_function<uint8_t>(&uvc_set_ae_priority)));

    add(Controller("exposure_abs", device,
                    create_get_function<uint32_t>(&uvc_get_exposure_abs),
                    create_set_function<uint32_t>(&uvc_set_exposure_abs)));

    add(Controller("exposure_rel", device,
                    create_get_function<int8_t>(&uvc_get_exposure_rel),
                    create_set_function<int8_t>(&uvc_set_exposure_rel)));

    add(Controller("focus_abs", device,
                    create_get_function<uint16_t>(&uvc_get_focus_abs),
                    create_set_function<uint16_t>(&uvc_set_focus_abs)));

    add(Controller("focus_simple_range", device,
                    create_get_function<uint8_t>(&uvc_get_focus_simple_range),
                    create_set_function<uint8_t>(&uvc_set_focus_simple_range)));

    add(Controller("focus_auto", device,
                    create_get_function<uint8_t>(&uvc_get_focus_auto),
                    create_set_function<uint8_t>(&uvc_set_focus_auto)));

    add(Controller("iris_abs", device,
                    create_get_function<uint16_t>(&uvc_get_iris_abs),
                    create_set_function<uint16_t>(&uvc_set_iris_abs)));

    add(Controller("iris_rel", device,
                    create_get_function<uint8_t>(&uvc_get_iris_rel),
                    create_set_function<uint8_t>(&uvc_set_iris_rel)));

    add(Controller("zoom_abs", device,
                    create_get_function<uint16_t>(&uvc_get_zoom_abs),
                    create_set_function<uint16_t>(&uvc_set_zoom_abs)));

    add(Controller("brightness", device,
                    create_get_function<int16_t>(&uvc_get_brightness),
                    create_set_function<int16_t>(&uvc_set_brightness)));

    add(Controller("backlight compensation", device,
                    create_get_function<uint16_t>(&uvc_get_backlight_compensation),
                    create_set_function<uint16_t>(&uvc_set_backlight_compensation)));

    add(Controller("contrast", device,
                    create_get_function<uint16_t>(&uvc_get_contrast),
                    create_set_function<uint16_t>(&uvc_set_contrast)));

    add(Controller("contrast_auto", device,
                    create_get_function<uint8_t>(&uvc_get_contrast_auto),
                    create_set_function<uint8_t>(&uvc_set_contrast_auto)));

    add(Controller("gain", device,
                    create_get_function<uint16_t>(&uvc_get_gain),
                    create_set_function<uint16_t>(&uvc_set_gain)));

    add(Controller("power_line_frequency", device,
                    create_get_function<uint8_t>(&uvc_get_power_line_frequency),
                    create_set_function<uint8_t>(&uvc_set_power_line_frequency)));

    add(Controller("hue", device,
                    create_get_function<int16_t>(&uvc_get_hue),
                    create_set_function<int16_t>(&uvc_set_hue)));

    add(Controller("hue_auto", device,
                    create_get_function<uint8_t>(&uvc_get_hue_auto),
                    create_set_function<uint8_t>(&uvc_set_hue_auto)));

    add(Controller("saturation", device,
                    create_get_function<uint16_t>(&uvc_get_saturation),
                    create_set_function<uint16_t>(&uvc_set_saturation)));

    add(Controller("sharpness", device,
                    create_get_function<uint16_t>(&uvc_get_sharpness),
                    create_set_function<uint16_t>(&uvc_set_sharpness)));

    add(Controller("white_balance_temperature", device,
                    create_get_function<uint16_t>(&uvc_get_white_balance_temperature),
                    create_set_function<uint16_t>(&uvc_set_white_balance_temperature)));

    add(Controller("white_balance_temperature_auto", device,
                    create_get_function<uint8_t>(&uvc_get_white_balance_temperature_auto),
                    create_set_function<uint8_t>(&uvc_set_white_balance_temperature_auto)));

    add(Controller("digital_multiplier", device,
                    create_get_function<uint16_t>(&uvc_get_digital_multiplier),
                    create_set_function<uint16_t>(&uvc_set_digital_multiplier)));

    _device = device;
}
