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

        Controller getOption(int i) const;

        void saveToFile(const std::string &filename) const;
        void loadFromFile(const std::string &filename);

    private:
        void populate(UVCDevice device);
        void add(Controller c);

        std::map<std::string, Controller> opts;
    };
}

#endif
