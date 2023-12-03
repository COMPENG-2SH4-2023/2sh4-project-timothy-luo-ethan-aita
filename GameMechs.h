#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;


class GameMechs
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    private:
        char input;
        bool exitFlag;
        bool loseFlag;
        int score;

        int boardSizeX;
        int boardSizeY;



    public:
        GameMechs();
        GameMechs(int boardX, int boardY);
        
        bool getExitFlagStatus();
        void setExitTrue();
        bool getLoseFlagStatus();
        void setLoseFlag();

        int getScore();
        void incrementScore();
        void specialScore();

        char getInput();
        void setInput(char this_input);
        void clearInput();

        int getBoardSizeX();
        int getBoardSizeY();

        // void generatefood(//objPos blockOff); // upgrade this

        // need to accept the player body array list
        // go through each array list element to make sure they are all
        // blocked off from random food generation



        // void getFoodPos(objPos &returnPos);

      
};

#endif