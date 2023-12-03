#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"

class Player
{
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        ~Player();
        Player(GameMechs* thisGMRef, Food* thisFoodRef);
        objPosArrayList* getPlayerPos(); 
        void updatePlayerDir();
        void movePlayer(); 
        bool checkFoodConsumption();
        bool checkSpecialFoodConsumption();
        void increasePlayerLength();
        bool checkSelfCollision();

        objPos currentHead; // Written in public scope because multiple methods use it and can modify it
        bool arrayMaxxed; // Flag signifying the array list capacity being reached

    private:
        objPosArrayList* playerPosList;   
        Food* foodRef;
        GameMechs* mainGameMechsRef;
        enum Dir myDir;
};

#endif