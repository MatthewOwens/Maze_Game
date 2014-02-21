#ifndef GUARD_H
#define GUARD_H
#include "Actor.h"
#include <string>
#include "Tile.h"

class Guard : public Actor
{
    //friend class Level;

    public:
        Guard(int x, int y, int speed, std::string direction, sf::Texture& texture);
        void initCollisionTiles(Tile tiles[][10], const int tileSize);
        bool update(Tile l_tiles[][10], sf::FloatRect p_bounds, const int tileSize);
        void reset();
        virtual ~Guard();

        // Accessor methods
        sf::Sprite getSprite();
        bool getAlive();
        bool getVisible();
        void setAlive(bool value);
        void setVisible(bool value);
        sf::Vector2i getGridLoc(const int tileSize);
    private:
        sf::Vector2f initialLocation;   // The initial location of the guard
        sf::Vector2i initialVelocity;   // The initial velocity of the guard
        bool alive;
        bool visible;
        sf::Vector2i collisionTiles[2];  // The two tiles the guard will collide
                                         // with while patroling
};

#endif // GUARD_H
