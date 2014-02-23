/// This entire game was re-written in under 72 hours due to an external hard
/// drive dying on me. Now you know why this code is barely functional.
///
/// Why didn't I back the damn thing up?

#include <iostream>
#include <SFML/Graphics.hpp>
#include "ImageManager.h"
#include "Level.h"
#include "Player.h"
#include "UserInterface.h"

int main()
{
    // The window that the game will be run in
    sf::RenderWindow window(sf::VideoMode(640, 704), "Maze Game - Reborn");
    window.setFramerateLimit(60);
    ImageManager imageManager;  // for loading in images
    UserInterface ui(imageManager.getImage("TitleImage"), "assets/Anonymous Pro.ttf");
    int currentLevel = 0;
    Level levels[] ={Level("levels/level0", imageManager),
                     Level("levels/level1", imageManager),
                     Level("levels/level2", imageManager),
                     Level("levels/level3", imageManager),
                     Level("levels/level4", imageManager)};

    Player player(imageManager.getImage("playerSprite"), imageManager.getImage("weaponSprite"), levels[currentLevel].getSpawn().x, levels[currentLevel].getSpawn().y);

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
        switch(ui.getState())
        {
        case (UserInterface::ScreenState::Title):
            ui.updateTitle();
            break;
        case (UserInterface::ScreenState::Game):
            player.update(levels[currentLevel].getTiles(), levels[currentLevel].getTileSize());
            levels[currentLevel].update(player.getVisibleTiles(), player.getBounds(), player.getWeaponBounds(), player.isAttacking());
            ui.updateGame(player.getLives(), levels[currentLevel].getScore(), levels[currentLevel].getComplete());

            if(levels[currentLevel].getComplete())
                currentLevel++;
            break;
        case (UserInterface::ScreenState::LevelComplete):
            ui.updateLevelComplete(levels[currentLevel].getScore(), levels[currentLevel].getStealth(),
                                   levels[currentLevel].getPacifist(), currentLevel, 0);
            break;
        case (UserInterface::ScreenState::GameOver):
            ui.updateGameOver();
        }


        if(levels[currentLevel].getGuardCollision())
            player.die(levels[currentLevel].getSpawn());

        // Draw Malarky
        window.clear();
        if (ui.getState() == UserInterface::ScreenState::Game)
        {
            levels[currentLevel].draw(window);
            player.draw(window);
        }
        ui.draw(window);
        window.display();
    }

    return 0;
}

