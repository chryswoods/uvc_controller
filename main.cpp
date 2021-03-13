
#include "uvcdevice.h"
#include "options.h"

#include <iostream>

using namespace UVC;

int main(int argc, char **argv) 
{
  UVCDevice device;

  device.open();

  Options options(device);

  std::cout << options.toString();

  device.close();

  return 0;
}
