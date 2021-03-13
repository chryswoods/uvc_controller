
#include "uvcdevice.h"
#include "options.h"

#include <iostream>

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

  while (true)
  {
      std::cout << "\n" << options.toString();

      std::cout << "\nChoose an option... (use q to quit, s to save, l to load)\n";

      std::string option;

      std::cin >> option;

      std::cout << "You have chosen " << option << std::endl;

      if (option == "q"){
        std::cout << "Quit :-)\n";
        break;
      }
      else if (option == "s"){
        std::cout << "Save to file - what filename?\n";

        std::string filename;
        std::cin >> filename;

        std::cout << "Writing to file " + filename + "\n";

        try
        {
            options.saveToFile(filename);
        }
        catch (const std::exception &e)
        {
            std::cout << "Could not write the file!\n";
        }

        continue;
      }
      else if (option == "l") {
        std::cout << "Load from file - what filename?\n";

        std::string filename;
        std::cin >> filename;

        std::cout << "Reading file " << filename << "\n";

        try
        {
          options.loadFromFile(filename);
        }
        catch(const std::exception& e)
        {
          std::cout << "Could not read from the file\n";
        }

        continue;
      }

      try
      {
          auto o = options.getOption(std::stoi(option));

          while (true)
          {
              std::cout << "\n" + o.toString() << "\n";
              std::cout << "Set the value\n";
              
              std::string value;
              std::cin >> value;

              if (value == "q"){
                break;
              }

              try
              {
                  std::cout << "Setting value to " << value << "\n";
                  o.setCurrent(std::stoi(value));
              }
              catch(const std::exception &e)
              {
                  std::cout << "Cannot set the value!\n";
                  break;
              }
          }

          options.rescan();
          continue;
      }
      catch(const std::exception& e)
      {
          std::cout << "Invalid option!\n";
      }
  }

  device.close();

  return 0;
}
