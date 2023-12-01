#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        ~Player();
        Player(GameMechs* thisGMRef, Food* thisFoodRef);
        objPosArrayList* getPlayerPos(); // ??(done) Upgrade this in iteration 3.
        //(objPos &returnPos) inside getPlayerPos???
        void updatePlayerDir();
        void movePlayer(); // need more actions in here:
        
        bool checkFoodConsumption();
        //void increasePlayerLength();
        bool checkSelfCollision();
        objPos currentHead;

        // after inserting the head but before removing the tail:
        // - check if new head position collides with food
        // - if yes, increment score in GM, generate new food don't remove tail
        // - otherwise, remove tail and move on

        // lastly, add self-collision check
        // if self-collided, set loseFlag and exitFlag both to true
        // this will end program loop and game

        // differentiate lost (with lost message) vs. exit (end game message)

        // bool checkSelfCollision();

    private:
        objPosArrayList* playerPosList;   // (done) Upgrade this in iteration 3 to below. 
        Food* foodRef;
        enum Dir myDir;

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;

        //Reference to Object Pos Array List:
        //objPosArrayList* playerPosList;
};

#endif