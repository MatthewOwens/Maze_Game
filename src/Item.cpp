#include "Item.h"

Item::Item(std::string identifier)
{
    id = identifier;
    collected = false;
    seen = false;
    visible = false;

    // Have to use a bunch of if statments here because non-primative
    // values can't be used in a switch in c++
    // q_q
    if (identifier == "diamond" || identifier == "ruby")
        value = 0;
    else if (identifier == "ingot")
        value = 100;
    else if (identifier == "necklace")
        value = 50;
    else
        std::cout << "Item identifier unknown, check your params mate." << std::endl;
}

Item::Item()
{
    id = "Oops, you didn't initilize this item correctly.\nCheck the Level class methods";
}

Item::~Item()
{
    //dtor
}
