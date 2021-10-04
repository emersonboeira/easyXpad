#include "eXpad.h"

void eXpad::findXpads()
{
    for(auto const& dir_entry: std::filesystem::directory_iterator(EXPAD_PATH))
    {
        std::string dirpath = (dir_entry.path()).u8string();
        if(!dirpath.find(JOYSTICK_PATH))
        {
            char eXpad_name[128];
            int eXpad_fd = open(dirpath.c_str(), O_RDONLY | O_NONBLOCK);
            ioctl(eXpad_fd, JSIOCGNAME(sizeof(eXpad_name)), &eXpad_name);
            if(!((std::string)eXpad_name).find(XBOX_ONE_CONTROLLER) 
            || !((std::string)eXpad_name).find(XBOX_360_CONTROLLER))
                std::cout << eXpad_name << std::endl;
        }
    }    
}

eXpad::Xbox_controller::Xbox_controller()
{
}

eXpad::Xbox_controller::~Xbox_controller()
{
}