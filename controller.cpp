
#include "controller.h"

#include <exception>
#include <iostream>
#include <string>

using namespace UVC;

Controller::Controller()
           : _name("unknown"),
             _current(0),
             _minimum(0),
             _maximum(0),
             _default(0)
{}

Controller::Controller(const std::string &name,
                       UVCDevice device,
                       uvc_get_function_t get_function,
                       uvc_set_function_t set_function)
           : _name(name), _device(device), _get_function(get_function),
             _set_function(set_function), _current(0),
             _minimum(0), _maximum(0), _default(0)
{
    this->populate();
}

Controller::Controller(const Controller &other)
           : _name(other._name), _device(other._device),
             _get_function(other._get_function),
             _set_function(other._set_function),
             _current(other._current), _minimum(other._minimum),
             _maximum(other._maximum), _default(other._default)
{}

Controller::~Controller()
{}

Controller& Controller::operator=(const Controller &other)
{
    if (this != &other)
    {
        _name = other._name;
        _device = other._device;
        _get_function = other._get_function;
        _set_function = other._set_function;
        _current = other._current;
        _minimum = other._minimum;
        _maximum = other._maximum;
        _default = other._default;
    }

    return *this;
}

std::string Controller::toString() const
{
    if (not this->_device.isOpen())
    {
        return this->_name + " : Not available";
    }

    return this->_name + " : " + 
           std::to_string(this->_minimum) + " <= " +
           std::to_string(this->_current) + " <= " +
           std::to_string(this->_maximum) + " : default " +
           std::to_string(this->_default);
}

const std::string& Controller::getName() const
{
    return this->_name;
}

int Controller::getCurrent() const
{
    return this->_current;
}

int Controller::getDefault() const
{
    return this->_default;
}

int Controller::getMinimum() const
{
    return this->_minimum;
}

int Controller::getMaximum() const
{
    return this->_maximum;
}

void Controller::populate()
{
    try
    {
        this->_current = this->_get_function(this->_device,
                                             UVC_GET_CUR);
        this->_maximum = this->_get_function(this->_device,
                                             UVC_GET_MAX);
        this->_minimum = this->_get_function(this->_device,
                                             UVC_GET_MIN);
        this->_default = this->_get_function(this->_device,
                                             UVC_GET_DEF);
    } 
    catch (std::exception &e)
    {
        // option is not supported
        std::string name = this->_name;
        this->operator=(Controller());
        this->_name = name;
    }
}

void Controller::setCurrent(int value)
{
    if (not this->_device.isOpen())
    {
        throw std::runtime_error("Option is not available: device not open");
    }

    this->_set_function(this->_device, value);

    this->_current = this->_get_function(this->_device, 
                                         UVC_GET_CUR);
}
