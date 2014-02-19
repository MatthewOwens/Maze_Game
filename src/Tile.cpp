#include "Tile.h"


// Default Constructor
Tile::Tile() {}

Tile::Tile(sf::Texture& tileSheet, const int tileSize, int id, int x, int y)
{
    gridLoc.x = x;
    gridLoc.y = y;
    sprite.setTexture(tileSheet);
    sprite.setTextureRect(sf::IntRect(id * tileSize, 0, tileSize, tileSize));
    sprite.setPosition(x * tileSize, y * tileSize);
    gridLoc = sf::Vector2i(x * tileSize, y * tileSize);
    identifier = id;
}

sf::FloatRect Tile::getBounds() { return sprite.getGlobalBounds(); }
sf::Vector2i Tile::getGridLoc() { return gridLoc; }
int Tile::getIdentifier() { return identifier; }
sf::Sprite Tile::getSprite() { return sprite; }

Tile::~Tile()
{
    //dtor
}
