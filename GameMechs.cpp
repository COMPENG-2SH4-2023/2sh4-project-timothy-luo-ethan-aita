#include "GameMechs.h"
#include "MacUILib.h"



using namespace std;

GameMechs::GameMechs()
{
    // Initializes game parameters with default board dimensions of (30x15)
    input = 0;
    score = 0;
    exitFlag = false;
    loseFlag = false;    
    boardSizeX = 30;
    boardSizeY = 15;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    //Initializes game parameters with board dimensions of (boardX x boardY) 
    input = 0;
    score = 0;
    exitFlag = false;
    loseFlag = false;
    boardSizeX = boardX;
    boardSizeY = boardY;
}

// do you need a destructor?
/*GameMechs::~GameMechs()
{

}*/

bool GameMechs::getExitFlagStatus()
{
    // Returns exitFlag value
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus()
{
    // Returns loseFlag value
    return loseFlag;
}

char GameMechs::getInput()
{
    // Returns last keyboard input
    if (MacUILib_hasChar())
    {
        input = MacUILib_getChar();
        if (input == 27)
        {
            exitFlag = true;
        }
    }

    return input;
}

int GameMechs::getBoardSizeX()
{
    // Returns the width of the gameboard
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    // Returns the height of the gameboard
    return boardSizeY;
}

int GameMechs::getScore()
{
    // Returns the current score of the game
    return score;
}

void GameMechs::setExitTrue()
{
    // Sets exitFlag to true
    exitFlag = true;
}

void GameMechs::setLoseFLag()
{
    // Sets loseFlag to true
    loseFlag = true;
}


void GameMechs::setInput(char this_input)
{
    // Sets input to the value of this_input parameter
    input = this_input;
}

void GameMechs::clearInput()
{
    // Clears the input
    input = 0;
}

void GameMechs::incrementScore()
{
    // Increments the score
    score++;

    // Add different scoring methods
    /*
    if ()
    {

    }...
    */    
}



