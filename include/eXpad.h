#ifndef EASYXPAD_H
#define EASYXPAD_H

// C system headers
#include <fcntl.h>
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
        
    class XboxController
    {
    private:
        std::string controllerName;
        std::string controllerPath;
        int number_of_buttons, number_of_axis;
        int controller_fd;

        std::list<Button> controllerButtons;
        std::list<Axis> controllerAxis;

        void setButtonValue(unsigned char number, signed short value);
        void setAxisValue(unsigned char number, signed short value);

    public:
        XboxController(char* cont_name, std::string path, int nb, int na);
        void readControllerEvents();
        ~XboxController();
    };

    std::list<XboxController> findXpads();
};

#endif