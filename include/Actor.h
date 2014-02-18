/// The Actor class is an abstract class to be inherited by the Player and
/// Guard classes.

#ifndef ACTOR_H
#define ACTOR_H
#include <SFML/Graphics.hpp>
#include <list>

class Actor
{
    public:
        Actor(sf::Texture& texture);
        virtual ~Actor() = 0;
        sf::FloatRect getBounds();

    protected:
        sf::Sprite sprite;      // The sprite to draw to the screen
        sf::IntRect sourceRect; // The portion of the texture to draw from
        sf::Vector2i gridLoc;
        int currentFrame;       // The current animation frame, determines
                                // what part of the texture to draw

        std::list<sf::Vector2i> visibleTiles;   // The tiles that the actor can
                                                // currently see.

};

#endif // ACTOR_H
