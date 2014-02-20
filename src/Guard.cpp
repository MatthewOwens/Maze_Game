#include "Guard.h"
#include <iostream>

Guard::Guard(int x, int y, int _speed, std::string direction, sf::Texture& texture)
    : Actor(texture, x, y)
{
    // Setting the speed
    speed = _speed;

    // Parsing the direction string
    if(direction == "north")
    {
        directionFacing = Direction::North;
        velocity = sf::Vector2i(0, -speed);
    }
    else if (direction == "south")
    {
        directionFacing = Direction::South;
        velocity = sf::Vector2i(0, speed);
    }
    else if (direction == "west")
    {
        directionFacing = Direction::West;
        velocity = sf::Vector2i(-speed, 0);
    }
    else if (direction == "east")
    {
        directionFacing = Direction::East;
        velocity = sf::Vector2i(speed, 0);
    }
    else std::cout << "Invalid direction passed to guard, you input: " << direction << std::endl;
}

void Guard::getCollisionTiles(Tile tiles[][10], const int tileSize)
{
    bool searchingHighs = true;
    bool searchingLows = true;
    int counter = 0;

    // Getting the current gridLocation
    gridLoc = sf::Vector2i(sprite.getPosition().x / tileSize,
                           sprite.getPosition().y / tileSize);

    // Starting the search from the guard's grid location
    collisionTiles[0].x = gridLoc.x;
    collisionTiles[0].y = gridLoc.y;
    collisionTiles[1].x = gridLoc.x;
    collisionTiles[1].y = gridLoc.y;


    // Finding the collision tiles
    while(searchingHighs || searchingLows)
    {
        if (searchingHighs)
        {
            // If the guard is moving horizontally
            if(directionFacing == Direction::East || directionFacing == Direction::West)
            {
                if(tiles[gridLoc.x + counter][gridLoc.y].getIdentifier() != 1)
                    collisionTiles[0].x++;
                else searchingHighs = false;
            }
            else
            {
                if(tiles[gridLoc.x][gridLoc.y + counter].getIdentifier() != 1)
                    collisionTiles[0].y++;
                else searchingHighs = false;
            }
        }
        if (searchingLows)
        {
            // If the guard is moving horizontally
            if(directionFacing == Direction::East || directionFacing == Direction::West)
            {
                if(tiles[gridLoc.x + counter][gridLoc.y].getIdentifier() != 1)
                    collisionTiles[1].x--;
                else searchingLows = false;
            }
            else
            {
                if(tiles[gridLoc.x][gridLoc.y + counter].getIdentifier() != 1)
                    collisionTiles[1].y--;
                else searchingLows = false;
            }
        }
    }
    std::cout << "Guard collision tile 0: " << collisionTiles[0].x << " " << collisionTiles[0].y << std::endl;
    std::cout << "Guard collision tile 1: " << collisionTiles[1].x << " " << collisionTiles[1].y << std::endl;
}

Guard::~Guard()
{
    //dtor
}
