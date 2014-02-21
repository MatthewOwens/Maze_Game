#include "Guard.h"
#include <iostream>

Guard::Guard(int x, int y, int _speed, std::string direction, sf::Texture& texture)
    : Actor(texture, x, y)
{
    // Setting flags
    alive = true;
    visible = false;

    // Setting the speed
    speed = _speed;

    // Setting the inital location
    initialLocation = sprite.getPosition();

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

    // Setting the initial velocity
    initialVelocity = velocity;
}

void Guard::initCollisionTiles(Tile tiles[][10], const int tileSize)
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
                if(tiles[gridLoc.x - counter][gridLoc.y].getIdentifier() != 1)
                    collisionTiles[1].x--;
                else searchingLows = false;
            }
            else
            {
                if(tiles[gridLoc.x][gridLoc.y - counter].getIdentifier() != 1)
                    collisionTiles[1].y--;
                else searchingLows = false;
            }
        }
        counter++;
    }
    std::cout << "Guard collision tile 0: " << collisionTiles[0].x << " " << collisionTiles[0].y << std::endl;
    std::cout << "Guard collision tile 1: " << collisionTiles[1].x << " " << collisionTiles[1].y << std::endl;
}

bool Guard::update(Tile l_tiles[][10], sf::FloatRect p_bounds, const int tileSize)
{
    bool playerCollision = false;
    visibleTiles.clear();

    // Finding the guard's location on the grid
    gridLoc = sf::Vector2i(sprite.getPosition().x / tileSize, sprite.getPosition().y / tileSize);

    // Checking for collision with tiles
    if ( sprite.getGlobalBounds().intersects(l_tiles[collisionTiles[0].x][collisionTiles[0].y].getBounds())
       ||sprite.getGlobalBounds().intersects(l_tiles[collisionTiles[1].x][collisionTiles[1].y].getBounds()))
    {
        velocity *= -1;
    }

    // Updating the tiles that the guards can see
    if (velocity.x > 0)
    {
        for(int i = gridLoc.x; i < 10; i++)
            visibleTiles.push_back(sf::Vector2i(i, gridLoc.y));
    }
    else
    {
        for(int i = gridLoc.x; i >= 0; i--)
            visibleTiles.push_back(sf::Vector2i(i, gridLoc.y));
    }
    if (velocity.y > 0)
    {
        for(int i = gridLoc.y; i < 10; i++)
            visibleTiles.push_back(sf::Vector2i(gridLoc.x, i));
    }
    else
    {
        for(int i = gridLoc.y; i >= 0; i--)
            visibleTiles.push_back(sf::Vector2i(gridLoc.x, i));
    }


    sprite.move(velocity.x, velocity.y);

    if(sprite.getGlobalBounds().intersects(p_bounds))
       playerCollision = true;

    return playerCollision;
}

void Guard::reset()
{
    alive = true;
    visible = false;
    sprite.setPosition(initialLocation);
}

// Accessor methods
sf::Sprite Guard::getSprite() { return sprite; }
bool Guard::getAlive() { return alive; }
bool Guard::getVisible() { return visible; }
void Guard::setVisible(bool value) { visible = value; }
void Guard::setAlive(bool value) { alive = value; }
sf::Vector2i Guard::getGridLoc(const int tileSize)
{
    return sf::Vector2i(sprite.getPosition().x / tileSize,
                        sprite.getPosition().y / tileSize);
}

Guard::~Guard()
{
    //dtor
}
