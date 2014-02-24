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
#include "Scoreboard.h"
#include "InputManager.h"

int main()
{
    // The window that the game will be run in
    sf::RenderWindow window(sf::VideoMode(640, 704), "Maze Game - Reborn");
    window.setFramerateLimit(60);
    ImageManager imageManager;  // for loading in images
    UserInterface ui(imageManager.getImage("TitleImage"), "assets/Anonymous Pro.ttf");
    Scoreboard scoreboard;
    InputManager inputManager;

    scoreboard.aggregateHighscores();
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
        inputManager.update();

        switch(ui.getState())
        {
        case (UserInterface::ScreenState::Title):
            ui.updateTitle();
            break;
        case (UserInterface::ScreenState::Game):
            player.update(levels[currentLevel].getTiles(), levels[currentLevel].getTileSize());
            levels[currentLevel].update(player.getVisibleTiles(), player.getBounds(), player.getWeaponBounds(), player.isAttacking());
            ui.updateGame(player.getLives(), levels[currentLevel].getScore(), currentLevel, levels[currentLevel].getComplete());

            if(levels[currentLevel].getComplete() && currentLevel != 4)
            {
                currentLevel++;
                player.setPosition(levels[currentLevel].getSpawn());
            }

            if (levels[currentLevel].getRubyCollected())
                player.addLife();
            break;
        case (UserInterface::ScreenState::LevelComplete):
            scoreboard.addLevelScore(levels[currentLevel-1].getScore(), currentLevel-1,
                                     levels[currentLevel-1].getStealth(), levels[currentLevel-1].getPacifist());

            ui.updateLevelComplete(levels[currentLevel-1].getScore(), levels[currentLevel-1].getStealth(),
                                   levels[currentLevel-1].getPacifist(), currentLevel - 1, scoreboard.getTotalScore());
            break;
        case (UserInterface::ScreenState::GameOver):
            ui.updateGameOver();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                currentLevel = 0;
                player.reset();
            }
            break;
        case (UserInterface::ScreenState::HighScores):
            ui.updateHighscores(scoreboard.getNames(), scoreboard.getScores(), scoreboard.getHighscore(), inputManager.getInput());
            if (inputManager.getBooleanValues("EnterPressed"))
                scoreboard.addTotalScore(scoreboard.getTotalScore(), inputManager.getInput());
            break;
        }

        if(levels[currentLevel].getGuardCollision())
            player.die(levels[currentLevel].getSpawn());

        inputManager.setPreviousValues();

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

