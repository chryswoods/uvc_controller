#ifndef UVC_OPTIONS_H
#define UVC_OPTIONS_H

#include <map>

#include "controller.h"

namespace UVC
{
    class UVCDevice;

    class Options
    {
    public:
        Options();
        Options(UVCDevice device);
        ~Options();

        std::string toString() const;

    private:
        void populate(UVCDevice device);

        std::map<std::string, Controller> opts;
    };
}

#endif
