/// The player class controls the player sprite within the world.
/// It is repsonsible for getting input from the keyboard in order
/// to manipulate the sprite as well calculating what tiles are visible
/// from it's location on the grid.

#ifndef PLAYER_H
#define PLAYER_H
#include "Actor.h"
#include "Tile.h"

class Player : public Actor
{
    public:
        Player(sf::Texture& texture, int x, int y);
        virtual ~Player();
        void update(Tile tiles[][10], const int tileSize);
        void die(sf::Vector2i spawn);
        void outputVisibleTiles();
    private:
        void peek(Tile tiles[][10], const int tileSize);
        int lives = 3;

};

#endif // PLAYER_H
