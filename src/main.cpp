/// This entire game was re-written in under 72 hours due to an external hard
/// drive dying on me. Now you know why this code is barely functional.
///
/// Why didn't I back the damn thing up?

#include <iostream>
#include <SFML/Graphics.hpp>
#include "ImageManager.h"
#include "Level.h"
#include "Player.h"
#include "Tile.h"

int main()
{
    // The window that the game will be run in
    sf::RenderWindow window(sf::VideoMode(640, 704), "Maze Game - Reborn");
    window.setFramerateLimit(60);
    ImageManager imageManager;  // for loading in images
    imageManager.loadImage("assets/playerSprite.png", "playerSprite");
    imageManager.loadImage("assets/diamondSprite.png", "diamond");
    imageManager.loadImage("assets/rubySprite.png", "ruby");
    imageManager.loadImage("assets/necklaceSprite.png", "necklace");
    imageManager.loadImage("assets/ingotSprite.png", "ingot");
    Level testLevel("levels/level0", imageManager);

    Player player(imageManager.getImage("playerSprite"), testLevel.getSpawn().x, testLevel.getSpawn().y);

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
        player.update(testLevel.getTiles(), testLevel.getTileSize());
        testLevel.update(player.getVisibleTiles(), player.getBounds());

        // Draw Malarky
        window.clear();
        testLevel.draw(window);
        player.draw(window);
        window.display();
    }

    return 0;
}

