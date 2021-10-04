#ifndef EASYXPAD_H
#define EASYXPAD_H

// C system headers
#include <fcntl.h> // to use open()
#include <stdio.h> // to print and test - REMOVE
#include <linux/joystick.h>

// C++ standard library headers
#include <string>
#include <list>
#include <filesystem>
#include <iostream>

namespace eXpad{

    #define EXPAD_PATH          "/dev/input/"
    #define JOYSTICK_PATH       "/dev/input/js"
    #define XBOX_ONE_CONTROLLER "Microsoft X-Box One pad"
    #define XBOX_360_CONTROLLER "Microsoft X-Box 360 pad"

    enum ControllerType{
        kXbox360_Controller,
        kXboxOne_Controller,
    };
    
    //Nonmember functions
    void findXpads();
    
    class Xbox_controller
    {
    private:
        std::string controller_name;
        std::string controller_path;
        eXpad::ControllerType controller_type;

    public:
        Xbox_controller(/* args */);
        ~Xbox_controller();
    };
};

#endif