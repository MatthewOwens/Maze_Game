/// The Actor class is an abstract class to be inherited by the Player and
/// Guard classes.

#ifndef ACTOR_H
#define ACTOR_H
#include <SFML/Graphics.hpp>
#include <list>

class Actor
{
    public:
        Actor(sf::Texture& texture, int x, int y);
        virtual ~Actor() = 0;
        void draw(sf::RenderWindow& window);

        // Accessor functions
        sf::FloatRect getBounds();
        std::list<sf::Vector2i> getVisibleTiles();
    protected:
        sf::Sprite sprite;      // The sprite to draw to the screen
        sf::IntRect sourceRect; // The portion of the texture to draw from
        sf::Vector2i gridLoc;
        sf::Vector2i velocity;
        sf::Vector2i previousLocation;
        int speed;              // How far to move the sprite by each loop
        int currentFrame;       // The current animation frame, determines
                                // what part of the texture to draw

        std::list<sf::Vector2i> visibleTiles;   // The tiles that the actor can
                                                // currently see.

};

#endif // ACTOR_H
