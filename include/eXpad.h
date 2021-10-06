#ifndef EASYXPAD_H
#define EASYXPAD_H

// C system headers
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/joystick.h>

// C++ standard library headers
#include <string>
#include <list>
#include <filesystem>
#include <iostream>

namespace eXpad{

    #define INPUT_PATH          "/dev/input/"
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
        float value;
    };

    struct Thumbstick {
        std::string name;
        eXpad::Axis x, y;
        float r = 0, tht = 0;
    };

    struct Dpad {
        std::string name="DPAD";
        eXpad::Axis x, y;
    };
        
    class XboxController
    {
    private:
        std::string controllerName;
        std::string controllerPath;
        int number_of_buttons, number_of_axis;
        int controller_fd;
        eXpad::ControllerType controllerType;

        std::list<Button> controllerButtons;
        std::list<Axis> controllerTriggers;
        std::list<Thumbstick> controllerThumbsticks;
        Dpad controllerDpad;

    public:
        XboxController(char* cont_name, std::string path, int nb, int na);
        void readEvents();
        ~XboxController();
    };

    std::list<XboxController> findXpads();
};

#endif