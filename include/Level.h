#ifndef LEVEL_H
#define LEVEL_H
#include "Tile.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "ImageManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>


class Level
{
    typedef Tile (*TilePtr)[10];

    public:
        Level(const std::string& filepath, ImageManager &imageManager);
        virtual ~Level();
        void draw(sf::RenderWindow& window);

        // Accessor methods
        TilePtr getTiles();
        Tile getTile(int x, int y);
        sf::Vector2i getSpawn();
        const int getTileSize();
        void update(std::list<sf::Vector2i> p_visibleTiles);
    private:
        Tile tiles[10][10];         // The tiles that will make the level map
        sf::Vector2i playerSpawn;   // The player's spawn location on this level
        const int tileSize = 64;
};

#endif // LEVEL_H
