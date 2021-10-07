#include <iostream>
#include <iomanip>
#include "eXpad.h"

int main()
{
    std::list<eXpad::XboxController> controller_list = eXpad::findXpads();

    std::list<eXpad::Button> controllerButtons;
    std::list<eXpad::Button>::iterator buttonsIterator;

    std::list<eXpad::Axis> controllerAxis;
    std::list<eXpad::Axis>::iterator axisIterator;

    while(1) {
        
        controller_list.begin()->readControllerEvents();
        controllerButtons = controller_list.begin()->getButtons();
        controllerAxis = controller_list.begin()->getAxis();

        for (buttonsIterator = controllerButtons.begin(); buttonsIterator != controllerButtons.end(); buttonsIterator++)
            std::cout << "(" << buttonsIterator->name+": " << buttonsIterator->value << ")";
        std::cout << "  ";
        for (axisIterator = controllerAxis.begin(); axisIterator != controllerAxis.end(); axisIterator++)
            std::cout << "(" <<  axisIterator->name+": " << std::setw(6) << axisIterator->value << ")";
        std::cout << std::endl;

    }

    return 0;
}