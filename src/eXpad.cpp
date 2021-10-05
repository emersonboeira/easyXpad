#include "eXpad.h"

eXpad::Xbox_controller::Xbox_controller(char* name, std::string path,
                                        int nb, int na)
{
    this->controller_name = (std::string)name;
    this->controller_path = path;
    this->buttons_number = nb;
    this->axis_number = na;

    if (this->controller_name == XBOX_360_CONTROLLER) {
        this->controller_type = kXbox360_Controller;
    }
    else if (this->controller_name == XBOX_ONE_CONTROLLER) {
        this->controller_type = kXboxOne_Controller;
    }
}

eXpad::Xbox_controller::~Xbox_controller()
{
}

std::list<eXpad::Xbox_controller> eXpad::findXpads()
{
    std::list<eXpad::Xbox_controller> c_list;
    for (auto const& dir_entry: std::filesystem::directory_iterator(INPUTS_PATH))
    {
        std::string dirpath = (dir_entry.path()).u8string();
        if (!dirpath.find(JOYSTICK_PATH))
        {
            char eXpad_name[128];
            int eXpad_fd = open(dirpath.c_str(), O_RDONLY | O_NONBLOCK);
            ioctl(eXpad_fd, JSIOCGNAME(sizeof(eXpad_name)), &eXpad_name);
            if (!((std::string)eXpad_name).find(XBOX_ONE_CONTROLLER) 
            || !((std::string)eXpad_name).find(XBOX_360_CONTROLLER))                
            {
                int eXpad_nb=0, eXpad_na=0;
                ioctl(eXpad_fd, JSIOCGBUTTONS, &eXpad_nb);
                ioctl(eXpad_fd, JSIOCGAXES, &eXpad_na);
                eXpad::Xbox_controller controller_read = eXpad::Xbox_controller(eXpad_name, dirpath, 
                                                                                eXpad_nb, eXpad_na);
                c_list.push_back(controller_read);
            }
            
        }
    }
    if (c_list.empty())
    {
        std::cout << "Unable to find any X-Box controller on your device!" << std::endl;
    }
    else
    {
        std::cout << "Found " << c_list.size() << " X-Box controllers on our device!"  << std::endl;
    }
    return c_list;
}