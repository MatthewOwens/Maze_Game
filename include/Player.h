/// The player class controls the player sprite within the world.
/// It is repsonsible for getting input from the keyboard in order.
/// to manipulate the sprite as well as combat between the player
/// and the 'Guard' characters.

#ifndef PLAYER_H
#define PLAYER_H
#include "Actor.h"

class Player : public Actor
{
    public:
        Player();
        virtual ~Player();
        void update(int tileIDs[10][10]);
    private:
};

#endif // PLAYER_H
