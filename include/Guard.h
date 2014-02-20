#ifndef GUARD_H
#define GUARD_H
#include "Actor.h"
#include <string>
#include "Tile.h"

class Guard : public Actor
{
    public:
        Guard();
        Guard(int x, int y, int speed, std::string direction, sf::Texture& texture);
        void getCollisionTiles(Tile tiles[][10], const int tileSize);
        virtual ~Guard();
    private:
        sf::Vector2i collisionTiles[2];  // The two tiles the guard will collide
                                        // with while patroling
};

#endif // GUARD_H
