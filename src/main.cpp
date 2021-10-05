#include <iostream>
#include "eXpad.h"

int main()
{
    std::list<eXpad::Xbox_controller> controller_list;

    controller_list = eXpad::findXpads();

    return 0;
}