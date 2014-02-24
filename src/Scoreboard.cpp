#include "Scoreboard.h"
#include <iostream>
#include <sstream>
#include <fstream>
Scoreboard::Scoreboard()
{
    for(int i = 0; i < 5; i++)
    {
        levelScores[i] = 0;
        highscore_scores[i] = 0;
        highscore_names[i] = std::string();
    }
}

Scoreboard::~Scoreboard()
{
    //dtor
}

void Scoreboard::addLevelScore(int score, int number, bool stealth, bool pacifist)
{
    if(levelScores[number] == 0)
    {
        if(stealth)
            score *= 3;
        if(pacifist)
            score *= 2;

        levelScores[number] = score;
    }
}

int Scoreboard::getTotalScore()
{
    int val;

    for(int i = 0; i < 5; i++)
    {
        val += levelScores[i];
    }
    std::cout << val << std::endl;

    return val;
}

void Scoreboard::aggregateHighscores()
{
    std::ifstream file("highscores/highscores.txt");
    std::string line;
    std::string subString;
    std::istringstream convert;
    std::stringstream ss;
    int i = 0;
    int j = 0;

    if (file.good())
    {
        while(std::getline(file, line))
        {
            ss.clear();
            ss.str(line);
            while(std::getline(ss, subString, ','))
            {
                switch(i)
                {
                case 0:
                    convert.str(subString);
                    convert >> highscore_names[j];
                    convert.clear();
                    convert.str(std::string());
                    break;
                case 1:
                    convert.str(subString);
                    convert >> highscore_scores[j];
                    convert.clear();
                    convert.str(std::string());
                }
                i++;
            }
            //std::cout << highscore_names[j] << "," << highscore_scores[j] << std::endl;
            i = 0;
            j++;
        }
    }
}

void Scoreboard::addTotalScore(int score, std::string name)
{
    bool sortFlag = false;
    int tempScore;
    std::string tempName;

    // Checking if the score is a highscore
    for(int i = 0; i < 5; i++)
    {
        if (score > highscore_scores[i])
            sortFlag = true;

        if (sortFlag)
        {
            // Storing the highscore in temp vars
            tempScore = highscore_scores[i];
            tempName = highscore_names[i];

            // Replacing the highscore
            highscore_scores[i] = score;
            highscore_names[i] = name;

            // Remplacing the input
            score = tempScore;
            name = tempName;
        }
    }

    for(int i = 0; i < 5; i++)
        std::cout << highscore_names[i] << "," << highscore_scores[i] << std::endl;
}

bool Scoreboard::getHighscore()
{
    for(int i = 0; i < 5; i++)
    {
        if(getTotalScore() > highscore_scores[i])
            return true;
    }
    return false;
}

int* Scoreboard::getScores() {return highscore_scores; }
std::string* Scoreboard::getNames() {return highscore_names; }
