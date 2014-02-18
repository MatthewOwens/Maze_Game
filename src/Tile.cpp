#include "Tile.h"

Tile::Tile(sf::Texture& tileSheet, const int tileSize, int id, int x, int y)
{
    gridLoc.x = x;
    gridLoc.y = y;
    sprite.setTexture(tileSheet);
    sprite.setTextureRect(sf::IntRect(id * tileSize, 0, tileSize, tileSize));
    sprite.setPosition(x * tileSize, y * tileSize);
}

Tile::getBounds() { return sprite.getGlobalBounds(); }
Tile::getGridLoc() { return gridLoc; }
Tile::getIdentifier() { return identifier; }

Tile::~Tile()
{
    //dtor
}
