
#include "uvcdevice.h"
#include "options.h"

#include <iostream>
#include <sstream>

using namespace UVC;

int main(int argc, char **argv) 
{
  UVCDevice device;

  device.open();

  if (not device.isOpen())
  {
      std::cout << "Could not open the device. Sorry.\n";
      return 0;
  }

  Options options(device);

  if (argc >= 2)
  {
      //load the file from the command line
      std::string filename(argv[1]);
      std::cout << "Loading from file " << filename << "\n";

      try
      {
          options.loadFromFile(filename);
      }
      catch(const std::exception& e)
      {
          std::cout << "Problem loading from file?\n";
      }

      std::cout << options.toString();
      
      return 0;
  }

  int opt = 0;
  while (true)
  {
      std::string cmd, arg;
      std::cout << "Enter 'q', 's filename', 'l filename' or 'X V' to set X-th parameter to V\n";
      std::cout << options.toString(opt);
      std::cout << "?> ";
      std::cin >> cmd;

      if ( cmd.size() < 1 )
          continue;
      if ( cmd == "q" )
          break;
      if ( cmd == "s" )
      {
          try {
              std::cin >> arg;
              options.saveToFile(arg);
              std::cout << "Saved to `"+arg+"`\n";
              opt = 0;
          }
          catch (const std::exception &e) {
              std::cout << "Could not save to file!\n";
          }
      }
      if ( cmd == "l" )
      {
          try {
              std::cin >> arg;
              options.loadFromFile(arg);
              std::cout << "Loaded from `"+arg+"`\n";
              opt = 0;
          }
          catch(const std::exception& e) {
              std::cout << "Could not load from file!\n";
          }
      }
      if ( isdigit(cmd[0]) )
      {
          int val = 0;
          try
          {
              std::cin >> arg;
              opt = std::stoi(cmd);
              val = std::stoi(arg);
              auto o = options.getOption(opt);
              o.setCurrent(val);
          }
          catch(const std::exception &e)
          {
              std::cout << "Cannot set [" << opt << "] <- " << val << "\n";
              continue;
          }
      }
      options.rescan();
  }

  std::cout << "Goodbye :-)\n";
  device.close();
  return 0;
}
