#include "Actor.h"

Actor::Actor(sf::Texture& texture)
{
    // Assigning a texture to the sprite
    sprite.setTexture(texture);

    // Ensuring that only a portion of the texture is drawn
    sourceRect.left = 0;
    sourceRect.top = 0;
    sourceRect.width = 32;
    sourceRect.height = 32;
    sprite.setTextureRect(sourceRect);
}

// Accessor functions
sf::FloatRect Actor::getBounds() {return sprite.getGlobalBounds();}

Actor::~Actor()
{
    //dtor
}
