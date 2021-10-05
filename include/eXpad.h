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

    #define INPUTS_PATH          "/dev/input/"
    #define JOYSTICK_PATH       "/dev/input/js"
    #define XBOX_ONE_CONTROLLER "Microsoft X-Box One pad"
    #define XBOX_360_CONTROLLER "Microsoft X-Box 360 pad"

    enum ControllerType{
        kXbox360_Controller,
        kXboxOne_Controller,
    };

    struct Button {
        std::string name;
        int address;
        bool value =0;
    };

    struct Axis {
        std::string name;
        int address;
        float x=0 , y=0, r=0, tht=0;
    };

    struct DPAD {
        std::string name="DPAD";
        std::string direction;
    };
        
    class Xbox_controller
    {
    private:
        std::string controller_name;
        std::string controller_path;
        int buttons_number, axis_number;
        eXpad::ControllerType controller_type;

        std::list<Button> controller_buttons;
        std::list<Axis> controller_axis;
        DPAD controller_dpad;

    public:
        Xbox_controller(char* cont_name, std::string path, int nb, int na);
        ~Xbox_controller();
    };
    //Nonmember functions
    std::list<Xbox_controller> findXpads();
};

#endif