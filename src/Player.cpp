#include "Player.h"
#include <SFML/Window/Keyboard.hpp>

Player::Player()
{
    //ctor
}

Player::~Player()
{
    //dtor
}

void Player::update(int tileIDs[10][10], const int tileSize)
{
    // Finding the player's location on the grid
    gridLoc = sprite.getPosition() / tileSize;

    // Clearing the list of visible tiles from last time
    visibleTiles.clear();

    // Checking for movement
    if (sf::Keyboard::isKeyPressed(Keyboard::Up))
        sprite.move(0,-5);
    else if (sf::Keyboard::isKeyPressed(Keyboard::Right))
        sprite.move(5,0);
    else if (sf::Keyboard::isKeyPressed(Keyboard::Left))
        sprite.move(5,0);
    else if (sf::Keyboard::isKeyPressed(Keyboard::Down))
        sprite.move(0,5);

    // Populating the list of visible tiles
    for (int i = gridLoc.x; i < 10; i++)
    {
        if (tileIDs[i][gridLoc.y] == 1)
            visibleTiles.push_back(sf::Vector2i(i, gridLoc.y))
    }
    for (int i = gridLoc.x; i >= 0; i--)
    {
        if (tileIDs[i][gridLoc.y] == 1)
            visibleTiles.push)back(sf::Vector2i(i, gridLoc.y))
    }
}
