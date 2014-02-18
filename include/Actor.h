/// The Actor class is an abstract class to be inherited by the Player and
/// Guard classes.

#ifndef ACTOR_H
#define ACTOR_H
#include <SFML/Graphics.hpp>

class Actor
{
    public:
        Actor(sf::Texture texture);
        virtual ~Actor() = 0;
        sf::FloatRect getBounds();
    protected:
        sf::Sprite sprite;      // The sprite to draw to the screen
        sf::IntRect sourceRect; // The portion of the texture to draw from
        int currentFrame;       // The current animation frame, determines
                                // what part of the texture to draw

};

#endif // ACTOR_H
