#include <iostream>
#include "eXpad.h"

int main()
{
    std::list<eXpad::XboxController> controller_list;

    controller_list = eXpad::findXpads();

    while(1) {
        controller_list.begin()->readControllerEvents();
        std::cout << controller_list.begin()->getValue() << std::endl;
        usleep(10000);
    }

    return 0;
}