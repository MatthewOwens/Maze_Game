#include "UserInterface.h"
#include <SFML/Window/Keyboard.hpp>
#include <sstream>

UserInterface::UserInterface(sf::Texture &titleTexture, const std::string &fontPath)
{
    font.loadFromFile(fontPath);
    titleImage.setTexture(titleTexture);
    state = ScreenState::Title;
    previousState = ScreenState::None;
}

UserInterface::~UserInterface()
{
    //dtor
}

void UserInterface::updatePreviousState()
{
    previousState = state;
}

void UserInterface::updateTitle()
{
    // Updating the text items
    textObjects.clear();

    textObjects.push_back(sf::Text("Diamond Thief", font));
    textObjects.back().setPosition(320 - textObjects.back().getGlobalBounds().width / 2, 64);

    textObjects.push_back(sf::Text("Press space to begin", font));
    textObjects.back().setPosition(320 - textObjects.back().getGlobalBounds().width / 2, 640);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        state = ScreenState::Game;
}

void UserInterface::updateGame(int p_lives, int l_score, bool l_complete)
{
    std::stringstream convert;

    // Updating the text items
    textObjects.clear();

    convert << p_lives;
    textObjects.push_back(sf::Text("Lives: " + convert.str(), font));
    textObjects.back().setPosition(5, 640);
    convert.str(std::string());
    convert.clear();

    convert << l_score;
    textObjects.push_back(sf::Text("Score: " + convert.str(), font));
    textObjects.back().setPosition(576 - textObjects.back().getGlobalBounds().width / 1.5, 640);
    convert.str(std::string());
    convert.clear();

    if (l_complete)
        state = ScreenState::LevelComplete;
    else if (p_lives == 0)
        state = ScreenState::GameOver;
}

void UserInterface::updateLevelComplete(int l_score, bool l_stealth, bool l_pacifist, int l_count, int s_totalScore)
{
    // Updating the text items
    textObjects.clear();
    std::list<sf::Text>::iterator text_itr;
    int counter = 0;

    textObjects.push_back(sf::Text("Level Score: " + l_score, font));
    textObjects.push_back(sf::Text("Stealth Bonus:  3x", font));
    textObjects.push_back(sf::Text("Pacifist Bonus: 2x", font));
    textObjects.push_back(sf::Text("Total Score: " + s_totalScore, font));

    for(text_itr = textObjects.begin(); text_itr != textObjects.end(); ++text_itr)
    {
        text_itr->setPosition(320 - text_itr->getGlobalBounds().width / 2, 64 + (64 * counter));

        if (counter == 1 && !l_stealth)
            text_itr->setColor(sf::Color::Transparent);
        else if (counter == 2 && !l_pacifist)
            text_itr->setColor(sf::Color::Transparent);
        counter++;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        if (l_count < 4)
            state = ScreenState::Game;
        else state = ScreenState::HighScores;
    }

}

void UserInterface::updateGameOver()
{
    textObjects.clear();

    textObjects.push_back(sf::Text("Game Over!", font));
    textObjects.back().setPosition(64, 320 - textObjects.back().getGlobalBounds().width / 2);

    textObjects.push_back(sf::Text("Press 'Space' to restart", font));
    textObjects.back().setPosition(640, 320 - textObjects.back().getGlobalBounds().width / 2);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        state = ScreenState::Title;
}

void UserInterface::updateHighscores(std::list<std::string> names, std::list<int>scores, bool highscore, std::string newName)
{
    std::list<std::string>::iterator itr_string;
    std::list<int>::iterator itr_int;
    int counter = 0;
    std::stringstream convert;

    textObjects.clear();
    itr_int = scores.begin();

    for(itr_string = names.begin(); itr_string != names.end(); ++itr_string)
    {
        convert << *itr_int;
        textObjects.push_back(sf::Text(*itr_string + ":\t" + convert.str(), font));
        textObjects.back().setPosition(320 - textObjects.back().getGlobalBounds().width / 2,
                                       64 + (64 * counter));
        counter++;
        convert.clear();
        convert.str(std::string());
    }

    if(highscore)
    {
        textObjects.push_back(sf::Text("Name: " + newName, font));
        textObjects.back().setPosition(64, 640);
    }
}

void UserInterface::draw(sf::RenderWindow &window)
{
    std::list<sf::Text>::iterator itr_text;
    if(state == ScreenState::Title)
        window.draw(titleImage);

    for(itr_text = textObjects.begin(); itr_text != textObjects.end(); itr_text++)
    {
        window.draw(*itr_text);
    }
}

// Accessor methods
UserInterface::ScreenState UserInterface::getState(){ return state; }
