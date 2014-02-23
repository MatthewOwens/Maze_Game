#include "Scoreboard.h"
#include <iostream>
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
