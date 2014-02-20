#include "Item.h"
#include <iostream>

Item::Item(std::string identifier, int x, int y, const int tileSize)
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
    {
        std::cout << "Item identifier unknown, check your params mate." << std::endl;
        std::cout << "The nonsense you typed was: " << identifier << std::endl;
    }

    sprite.setPosition((x * tileSize) + 16
                      ,(y * tileSize) + 16);
}

void Item::setTexture(sf::Texture& texture)
{
    sprite.setTexture(texture);
}

sf::Vector2i Item::getGridLoc(const int tileSize)
{
    return sf::Vector2i(sprite.getPosition().x / tileSize,
                        sprite.getPosition().y / tileSize);
}

void Item::reset()
{
    seen = false;
    collected = false;
    visible = false;
    sprite.setColor(sf::Color::White);
}

Item::Item()
{
    id = "Oops, you didn't initilize this item correctly.\nCheck the Level class methods";
}

Item::~Item()
{
    //dtor
}
