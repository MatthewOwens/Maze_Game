/// The tile class is used by the Level class to populate
/// the map that will be played on by the user.

#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>


class Tile
{
    friend class Level;

    public:
        Tile(sf::Texture& tileSheet, const int tileSize, int id, int x, int y);
        Tile(); // Default constructor
        virtual ~Tile();
        sf::FloatRect getBounds();
        sf::Vector2i getGridLoc();
        sf::Sprite getSprite();
        int getIdentifier();
    private:
        sf::Sprite sprite;
        sf::Vector2i gridLoc;
        int identifier;

};

#endif // TILE_H
