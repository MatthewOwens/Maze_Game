#include "Player.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

Player::Player(sf::Texture& texture, int x, int y)
    : Actor(texture, x, y)
{
    //ctor
    speed = 3;
    directionFacing = Direction::North;
}

Player::~Player()
{
    //dtor
}

void Player::die(sf::Vector2i spawn)
{
    lives--;
    sprite.setPosition(spawn.x + 32,spawn.y + 32);
}

void Player::update(Tile tiles[][10], const int tileSize)
{
    // Finding the player's location on the grid
    gridLoc = sf::Vector2i(sprite.getPosition().x / tileSize, sprite.getPosition().y / tileSize);

    // Clearing the list of visible tiles from last time
    visibleTiles.clear();

    // Resetting the velocity from last time
    velocity = sf::Vector2i();

    // Checking for movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        velocity.y -= speed;
        directionFacing = Direction::North;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        velocity.x += speed;
        directionFacing = Direction::East;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        velocity.x -= speed;
        directionFacing = Direction::West;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        velocity.y += speed;
        directionFacing = Direction::South;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        peek(tiles, tileSize);

    // Populating the list of visible tiles
    for (int i = gridLoc.x + 1; i < 10; i++)
    {
        if (tiles[i][gridLoc.y].getIdentifier() != 1)
            visibleTiles.push_back(sf::Vector2i(i, gridLoc.y));
        else break;
    }
    for (int i = gridLoc.x - 1; i >= 0; i--)
    {
        if (tiles[i][gridLoc.y].getIdentifier() != 1)
            visibleTiles.push_back(sf::Vector2i(i, gridLoc.y));
        else break;
    }
    for (int i = gridLoc.y + 1; i < 10; i++)
    {
        if (tiles[gridLoc.x][i].getIdentifier() != 1)
            visibleTiles.push_back(sf::Vector2i(gridLoc.x, i));
        else break;
    }
    for (int i = gridLoc.y - 1; i >= 0; i--)
    {
        if (tiles[gridLoc.x][i].getIdentifier() != 1)
            visibleTiles.push_back(sf::Vector2i(gridLoc.x, i));
        else break;
    }

    // The player's current tile will always be visible
    visibleTiles.push_back(gridLoc);

    // Checking for collision with the walls
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            //std::cout << tiles[gridLoc.x][gridLoc.y].getIdentifier();
            if (tiles[i][j].getIdentifier() == 1
                && sprite.getGlobalBounds().intersects(tiles[i][j].getBounds()))
            {
                // Moving the sprite back
                sprite.setPosition(previousLocation.x, previousLocation.y);

                //velocity = sf::Vector2i();
                // ^^ Doesn't work, possibly because SFML is getting keyboard input at a
                // faster rate than the window framerate??
            }
        }
        //std::cout << std::endl;
    }

    // Keeping the player within the game region
    if (sprite.getGlobalBounds().left < 0 || sprite.getGlobalBounds().top < 0
        || sprite.getGlobalBounds().left + sprite.getGlobalBounds().width > 10 * tileSize
        || sprite.getGlobalBounds().top + sprite.getGlobalBounds().height > 10 * tileSize)
    {
        sprite.setPosition(previousLocation.x, previousLocation.y);
    }

    // Moving the sprite
    //std::cout << velocity.x << "," << velocity.y << std::endl;
    previousLocation = sf::Vector2i(sprite.getPosition());
    sprite.move(velocity.x, velocity.y);
}

// The peek method allows the player to peek around corners by adding more
// values to the visible tiles array based on the direction that the player's
// facing as well as the player's position within the current tile.
void Player::peek(Tile tiles[][10], const int tileSize)
{
    // The player's position within this tile.
    sf::Vector2i localPos(sprite.getPosition().x - (gridLoc.x * tileSize),
                          sprite.getPosition().y - (gridLoc.y * tileSize));

    // Determining where to peek based on what direction the player is facing.
    switch(directionFacing)
    {
    case East:
        if (tiles[gridLoc.x + 1][gridLoc.y].getIdentifier() != 1)
            break;

        for(int i = gridLoc.x + 1; i < 10; i++)
        {
            if (localPos.y >= 32)
            {
                if (tiles[i][gridLoc.y + 1].getIdentifier() != 1
                    && gridLoc.y + 1 < 10)
                {
                    visibleTiles.push_back(sf::Vector2i(i, gridLoc.y + 1));
                }
                else break;
            }
            else
            {
                if (tiles[i][gridLoc.y - 1].getIdentifier() != 1
                    && gridLoc.y - 1 >= 0)
                    visibleTiles.push_back(sf::Vector2i(i, gridLoc.y - 1));
                else break;
            }
        }
        break;
    case West:
        if (tiles[gridLoc.x - 1][gridLoc.y].getIdentifier() != 1)
            break;

        for (int i = gridLoc.x - 1; i >= 0; i--)
        {
            if (localPos.y >= 32)
            {
                if (tiles[i][gridLoc.y + 1].getIdentifier() != 1
                    && gridLoc.y + 1 < 10)
                    visibleTiles.push_back(sf::Vector2i(i, gridLoc.y + 1));
                else break;
            }
            else
            {
                if (tiles[i][gridLoc.y - 1].getIdentifier() != 1
                    && gridLoc.y - 1 >= 0)
                    visibleTiles.push_back(sf::Vector2i(i, gridLoc.y - 1));
                else break;
            }
        }
        break;
    case South:
        if (tiles[gridLoc.x][gridLoc.y + 1].getIdentifier() != 1)
            break;

        for (int i = gridLoc.y + 1; i < 10; i++)
        {
            if (localPos.x >= 32)
            {
                if (tiles[gridLoc.x + 1][i].getIdentifier() != 1
                    && gridLoc.x + 1 < 10)
                    visibleTiles.push_back(sf::Vector2i(gridLoc.x + 1, i));
                else break;
            }
            else
            {
                if (tiles[gridLoc.x - 1][i].getIdentifier() != 1
                    && gridLoc.x - 1 >= 0)
                    visibleTiles.push_back(sf::Vector2i(gridLoc.x - 1, i));
                else break;
            }
        }
        break;
    case North:
        if (tiles[gridLoc.x][gridLoc.y - 1].getIdentifier() != 1)
            break;

        for (int i = gridLoc.y - 1; i >= 0; i--)
        {
            if (localPos.x >= 32)
            {
                if (tiles[gridLoc.x + 1][i].getIdentifier() != 1
                    && gridLoc.x + 1 < 10)
                    visibleTiles.push_back(sf::Vector2i(gridLoc.x + 1, i));
                else break;
            }
            else
            {
                if (tiles[gridLoc.x - 1][i].getIdentifier() != 1
                    && gridLoc.x - 1 >= 0)
                    visibleTiles.push_back(sf::Vector2i(gridLoc.x - 1, i));
                else break;
            }
        }
        break;
    }
}

void Player::outputVisibleTiles()
{
    std::list<sf::Vector2i>::iterator itr;
    std::cout << "I can see " << visibleTiles.size() << " tiles" << std::endl;
    for(itr = visibleTiles.begin(); itr != visibleTiles.end(); ++itr)
    {
        std::cout << "I can see (" << itr->x << "," << itr->y << ")" << std::endl;
    }
}
