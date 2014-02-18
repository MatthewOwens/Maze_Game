/// This entire game was re-written in under 72 hours due to an external hard
/// drive dying on me. Now you know why this code is barely functional.
///
/// Why didn't I back the damn thing up?

#include <iostream>
#include <SFML/Graphics.hpp>
#include "ImageManager.h"

int main()
{
    std::cout << "hello, there" << std::endl;
    // The window that the game will be run in
    sf::RenderWindow window(sf::VideoMode(640, 704), "Maze Game - Reborn");
    sf::Sprite sprite;
    ImageManager imageManager;

    imageManager.loadImage("feels.png");
    sprite.setTexture(imageManager.getImage("feels.png"));

    // Run as long as the window is open
    while (window.isOpen())
    {
        // Check that all the window events were triggered since the last
        // iteration of the loop.
        sf::Event event;

        while (window.pollEvent(event))
        {
            // Closing the window
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

        // Update Malarky
        // Draw Malarky
        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}

