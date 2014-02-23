/// The Scoreboard class is responsible for collating the scores from each of the
/// levels in the game, applying the bonus modifiers for each level and adding that
/// to a total score.
/// The Scoreboard is also responsible for reading and writing to the Highscores file.

#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#include <string>


class Scoreboard
{
    public:
        Scoreboard();
        virtual ~Scoreboard();
        void addLevelScore(int score, int number, bool stealth, bool pacifist);
        int getTotalScore();
    private:
        int levelScores[5];
        int highscore_scores[5];
        std::string highscore_names[5];
};

#endif // SCOREBOARD_H
