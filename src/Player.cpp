#include "Player.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

Player::Player(sf::Texture& texture, int x, int y)
    : Actor(texture, x, y)
{
    //ctor
    speed = 3;
}

Player::~Player()
{
    //dtor
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
        velocity.y -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        velocity.x += speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        velocity.x -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        velocity.y += speed;

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

void Player::outputVisibleTiles()
{
    std::list<sf::Vector2i>::iterator itr;
    std::cout << "I can see " << visibleTiles.size() << " tiles" << std::endl;
    for(itr = visibleTiles.begin(); itr != visibleTiles.end(); ++itr)
    {
        std::cout << "I can see (" << itr->x << "," << itr->y << ")" << std::endl;
    }
}
