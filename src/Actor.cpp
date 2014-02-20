#include "Actor.h"

// Constructor, sets values that are shared between the Player and Actor classes
Actor::Actor(sf::Texture& texture, int x, int y)
{
    // Assigning a texture to the sprite
    sprite.setTexture(texture);

    // Ensuring that only a portion of the texture is drawn
    sourceRect.left = 0;
    sourceRect.top = 0;
    sourceRect.width = 32;
    sourceRect.height = 32;
    sprite.setTextureRect(sourceRect);

    // Setting the origin of the sprite to the center of the sprite
    sprite.setOrigin(16, 16);

    // Setting the location of the sprite, offset by the origin.
    sprite.setPosition(x + 32, y + 32);

    // Defaulting the speed to zero, should be defined in child constructor
    speed = 0;
}

// Draw function
void Actor::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

// Accessor functions
sf::FloatRect Actor::getBounds() {return sprite.getGlobalBounds();}
std::list<sf::Vector2i> Actor::getVisibleTiles() {return visibleTiles;}

Actor::~Actor()
{
    //dtor
}
