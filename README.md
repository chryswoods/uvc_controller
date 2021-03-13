# UVC Controller

This is a *very simple* program that can be used to query and set
webcam parameters that are exposed via the UVC webcam interface.

What you can set will depend on your make and model of camera,
and how much it follows the UVC standard.

## Compilation

This program uses [libuvc](https://github.com/libuvc/libuvc) to
get and set webcam options. You need to install libuvc first if you
want to compile and install this program. Otherwise, UVC Controller
has no other dependencies (I want to keep this simple and easy to
install).

To keep things simple, I've made a very basic makefile that should
work on most systems. To compile you need a C++ compiler that supports
the C++ 17 standard, and type;

```
make
```

This should output

```
# A very simple build :-)
g++ -std=c++17 -O2 -I/usr/local/include main.cpp controller.cpp options.cpp uvcdevice.cpp -L/usr/local/lib -luvc -o uvc_controller
```

and will create the program `uvc_controller`.

This assumes that your `libuvc` is installed in `/usr/local`. If it isn't
then edit `Makefile` and change `INCLUDE_DIR` and `LIB_DIR` to the 
right paths.

## Usage

Running the program will enter a simple text interface, e.g.

```
./uvc_controller

[1]: backlight compensation : 0 <= 6 <= 6 : default 2
[2]: brightness : -64 <= 30 <= 64 : default 0
[3]: contrast : 0 <= 48 <= 64 : default 32
[4]: exposure_abs : 1 <= 500 <= 5000 : default 157
[5]: focus_abs : 1 <= 240 <= 1023 : default 240
[6]: gain : 0 <= 1 <= 1 : default 0
[7]: gamma : 72 <= 250 <= 500 : default 100
[8]: hue : -40 <= 0 <= 40 : default 0
[9]: power_line_frequency : 0 <= 1 <= 2 : default 1
[10]: saturation : 0 <= 110 <= 128 : default 56
[11]: sharpness : 0 <= 3 <= 6 : default 3
[12]: white_balance_temperature : 2800 <= 5000 <= 6500 : default 4600

Choose an option... (use q to quit, s to save, l to load)
```

Only options that can be set on your camera will be displayed. 
Type the number of the option you want to set and press return,
e.g. for me, to change gamma I would press;

```
7

You have chosen 7

gamma : 72 <= 250 <= 500 : default 100
Set the value
```

This then shows the valid range of values (here from 72 to 500), 
the current value (here 250) and the default value for the 
camera (here 100). Type in the number you want to set it to,
and press return. For example, to change to 200, I'd type;

```
200

Setting value to 200

gamma : 72 <= 200 <= 500 : default 100
Set the value
```

This will set to 200, and will now let you set the value again.
To exit back to the menu, type `q` and press return;

```
q

[1]: backlight compensation : 0 <= 6 <= 6 : default 2
[2]: brightness : -64 <= 30 <= 64 : default 0
[3]: contrast : 0 <= 48 <= 64 : default 32
[4]: exposure_abs : 1 <= 500 <= 5000 : default 157
[5]: focus_abs : 1 <= 240 <= 1023 : default 240
[6]: gain : 0 <= 1 <= 1 : default 0
[7]: gamma : 72 <= 250 <= 500 : default 100
[8]: hue : -40 <= 0 <= 40 : default 0
[9]: power_line_frequency : 0 <= 1 <= 2 : default 1
[10]: saturation : 0 <= 110 <= 128 : default 56
[11]: sharpness : 0 <= 3 <= 6 : default 3
[12]: white_balance_temperature : 2800 <= 5000 <= 6500 : default 4600

Choose an option... (use q to quit, s to save, l to load)
```

You can save the current values of your options to a file by typing
`s` and pressing return;

```
You have chosen s
Save to file - what filename?
```

Type in the filename that you want to use. Be careful as this will overwrite
the file. For example, to save to `options.txt` you can type;

```
options.txt

options.txt
Writing to file options.txt

[1]: backlight compensation : 0 <= 6 <= 6 : default 2
[2]: brightness : -64 <= 30 <= 64 : default 0
[3]: contrast : 0 <= 48 <= 64 : default 32
[4]: exposure_abs : 1 <= 500 <= 5000 : default 157
[5]: focus_abs : 1 <= 240 <= 1023 : default 240
[6]: gain : 0 <= 1 <= 1 : default 0
[7]: gamma : 72 <= 250 <= 500 : default 100
[8]: hue : -40 <= 0 <= 40 : default 0
[9]: power_line_frequency : 0 <= 1 <= 2 : default 1
[10]: saturation : 0 <= 110 <= 128 : default 56
[11]: sharpness : 0 <= 3 <= 6 : default 3
[12]: white_balance_temperature : 2800 <= 5000 <= 6500 : default 4600

Choose an option... (use q to quit, s to save, l to load)
```

Next, you can load from a file be pressing `l` then return

```
You have chosen l
Load from file - what filename?
```

We can load from `options.txt` by typing in its name, e.g.

```
options.txt

Reading file options.txt
Set backlight compensation to 6
Set brightness to 30
Set contrast to 48
Set exposure_abs to 500
Set focus_abs to 240
Set gain to 1
Set gamma to 250
Set hue to 0
Set power_line_frequency to 1
Set saturation to 110
Set sharpness to 3
Set white_balance_temperature to 5000

[1]: backlight compensation : 0 <= 6 <= 6 : default 2
[2]: brightness : -64 <= 30 <= 64 : default 0
[3]: contrast : 0 <= 48 <= 64 : default 32
[4]: exposure_abs : 1 <= 500 <= 5000 : default 157
[5]: focus_abs : 1 <= 240 <= 1023 : default 240
[6]: gain : 0 <= 1 <= 1 : default 0
[7]: gamma : 72 <= 250 <= 500 : default 100
[8]: hue : -40 <= 0 <= 40 : default 0
[9]: power_line_frequency : 0 <= 1 <= 2 : default 1
[10]: saturation : 0 <= 110 <= 128 : default 56
[11]: sharpness : 0 <= 3 <= 6 : default 3
[12]: white_balance_temperature : 2800 <= 5000 <= 6500 : default 4600

Choose an option... (use q to quit, s to save, l to load)
```

Next, you can quit the program by pressing `q` and then return.

```
You have chosen q
Quit :-)
```

## Loading a file from the command line

You can also just use the program to load an existing parameter file
by passing this as a command line argument. If we want to load 
the `options.txt` from above, we could type

```
./uvc_controller options.txt

Loading from file options.txt
Set backlight compensation to 6
Set brightness to 30
Set contrast to 48
Set exposure_abs to 500
Set focus_abs to 240
Set gain to 1
Set gamma to 250
Set hue to 0
Set power_line_frequency to 1
Set saturation to 110
Set sharpness to 3
Set white_balance_temperature to 5000
[1]: backlight compensation : 0 <= 6 <= 6 : default 2
[2]: brightness : -64 <= 30 <= 64 : default 0
[3]: contrast : 0 <= 48 <= 64 : default 32
[4]: exposure_abs : 1 <= 500 <= 5000 : default 157
[5]: focus_abs : 1 <= 240 <= 1023 : default 240
[6]: gain : 0 <= 1 <= 1 : default 0
[7]: gamma : 72 <= 250 <= 500 : default 100
[8]: hue : -40 <= 0 <= 40 : default 0
[9]: power_line_frequency : 0 <= 1 <= 2 : default 1
[10]: saturation : 0 <= 110 <= 128 : default 56
[11]: sharpness : 0 <= 3 <= 6 : default 3
[12]: white_balance_temperature : 2800 <= 5000 <= 6500 : default 4600
```

## Extensions

This is deliberately a very simple program that I put together on one
day to set the options of my webcam. Please feel free to fork this project
and give it a better interface or more options :-)
