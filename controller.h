#ifndef UVC_CONTROLLER_H
#define UVC_CONTROLLER_H

#include "libuvc/libuvc.h"

#include <functional>
#include <string>

#include "uvcdevice.h"

namespace UVC
{
    typedef std::function<int(UVCDevice device,
                              uvc_req_code code)> uvc_get_function_t;

    typedef std::function<void(UVCDevice device,
                               int value)> uvc_set_function_t;

    class Controller
    {
    public:
        Controller();
        Controller(const std::string &name,
                   UVCDevice device,
                   uvc_get_function_t get_function,
                   uvc_set_function_t set_function);
        Controller(const Controller &other);

        ~Controller();

        Controller& operator=(const Controller &other);

        const std::string& getName() const;
        
        int getCurrent() const;
        int getDefault() const;
        int getMinimum() const;
        int getMaximum() const;

        void setCurrent(int value);

    private:
        void populate();

        std::string _name;
        UVCDevice _device;
        uvc_get_function_t _get_function;
        uvc_set_function_t _set_function;
        int _current;
        int _minimum;
        int _maximum;
        int _default;
    };
}

#endif
