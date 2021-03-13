# This is deliberately a very simple makefile as I want to 
# make this program as easy to install as possible. All
# you need to set is the C++ compiler to use (g++ is nearly
# always available) and the directories that contain 
# the libuvc header file and library

# Choose your C++ compiler here
CXX=g++

# Set the flags needed to compile (C++ 17)
CFLAGS=-std=c++17 -O2

# Set the path to the directory that contains
# the libuvc directory
INCLUDE_DIR=/usr/local/include

# Set the path to the directory that contains
# the libuvc library
LIB_DIR=/usr/local/lib

build:
	# A very simple build :-)
	$(CXX) ${CFLAGS} -I${INCLUDE_DIR} main.cpp controller.cpp options.cpp uvcdevice.cpp -L${LIB_DIR} -luvc -o uvc_controller
