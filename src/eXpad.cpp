#include "eXpad.h"

eXpad::XboxController::XboxController(char* name, std::string path, int nb, int na)
{
    this->controllerName = (std::string)name;
    this->controllerPath = path;
    this->number_of_buttons = nb;
    this->number_of_axis = na;

    this->controller_fd = open(this->controllerPath.c_str(), O_RDONLY | O_NONBLOCK);

    eXpad::Button A, B, X, Y;
    A.name = "A"; A.address = 0; this->controllerButtons.push_back(A);
    B.name = "B"; B.address = 1; this->controllerButtons.push_back(B);
    X.name = "X"; X.address = 2; this->controllerButtons.push_back(X);
    Y.name = "Y"; Y.address = 3; this->controllerButtons.push_back(Y);

    eXpad::Button LB, RB;
    LB.name = "LB"; LB.address = 4; this->controllerButtons.push_back(LB);
    RB.name = "RB"; RB.address = 5; this->controllerButtons.push_back(RB);
    
    eXpad::Button Back, Start, Guide;
    Back.name = "Back"; Back.address = 6; this->controllerButtons.push_back(Back);
    Start.name = "Start"; Start.address = 7; this->controllerButtons.push_back(Start);
    Guide.name = "Guide"; Guide.address = 8; this->controllerButtons.push_back(Guide);

    eXpad::Button LSB, RSB;
    LSB.name = "LSB"; LSB.address = 9; this->controllerButtons.push_back(LSB);
    RSB.name = "RSB"; RSB.address = 10; this->controllerButtons.push_back(RSB);

    eXpad::Axis LSB_x, LSB_y, LT;
    LSB_x.name = "LSB_x"; LSB_x.address = 0; this->controllerAxis.push_back(LSB_x);
    LSB_y.name = "LSB_y"; LSB_y.address = 1; this->controllerAxis.push_back(LSB_y);
    LT.name = "LT"; LT.address = 2;

    eXpad::Axis RSB_x, RSB_y, RT;
    RSB_x.name = "RSB_x"; RSB_x.address = 3;
    RSB_y.name = "RSB_y"; RSB_y.address = 4;
    RT.name = "RT"; RT.address = 5;

    eXpad::Axis DPAD_x, DPAD_y;
    DPAD_x.name = "DPAD_x"; DPAD_x.address = 6;
    DPAD_y.name = "DPAD_y"; DPAD_y.address = 7;

}

void eXpad::XboxController::setButtonValue(unsigned char number, signed short value)
{
    std::list<eXpad::Button>::iterator buttonsIterator;
    for (buttonsIterator = this->controllerButtons.begin(); buttonsIterator != this->controllerButtons.end(); buttonsIterator++)
    {
        if (buttonsIterator->address == number)
            {
                buttonsIterator->value = value;
            }   
    }
}

void eXpad::XboxController::setAxisValue(unsigned char number, signed short value)
{
    std::list<eXpad::Axis>::iterator axisIterator;
    for (axisIterator = this->controllerAxis.begin(); axisIterator != this->controllerAxis.end(); axisIterator++)
    {
        if (axisIterator->address == number)
            {
                axisIterator->value = value;
            }   
    }
}

void eXpad::XboxController::readControllerEvents()
{
    struct js_event controller_event;
    if ( read(this->controller_fd, &controller_event, sizeof(controller_event)) > 0 )
    {
        switch (controller_event.type)
        {
        case 1:
            this->setButtonValue(controller_event.number, controller_event.value);
            break;
        case 2:
            this->setAxisValue(controller_event.number, controller_event.value);
            break;
        default:
            break;
        }
    }
}

eXpad::XboxController::~XboxController()
{
}

std::list<eXpad::XboxController> eXpad::findXpads()
{
    std::list<eXpad::XboxController> c_list;
    for (auto const& dir_entry: std::filesystem::directory_iterator(INPUT_PATH))
    {
        std::string dirpath = (dir_entry.path()).u8string();
        if (!dirpath.find(JOYSTICK_PATH))
        {
            char eXpad_name[128];
            int eXpad_fd = open(dirpath.c_str(), O_RDONLY | O_NONBLOCK);
            ioctl(eXpad_fd, JSIOCGNAME(sizeof(eXpad_name)), &eXpad_name);
            if (!((std::string)eXpad_name).find(XBOX_ONE_CONTROLLER) || !((std::string)eXpad_name).find(XBOX_360_CONTROLLER))                
            {
                int eXpad_nb=0, eXpad_na=0;
                ioctl(eXpad_fd, JSIOCGBUTTONS, &eXpad_nb);
                ioctl(eXpad_fd, JSIOCGAXES, &eXpad_na);

                eXpad::XboxController controller_read = eXpad::XboxController(eXpad_name, dirpath, eXpad_nb, eXpad_na);
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