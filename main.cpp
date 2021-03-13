
#include "uvcdevice.h"
#include "options.h"

#include <iostream>

using namespace UVC;

int main(int argc, char **argv) 
{
  UVCDevice device;

  device.open();

  Options options(device);

  while (true)
  {
      std::cout << "\n" << options.toString();

      std::cout << "\nChoose an option... (use q to quit)\n";

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
