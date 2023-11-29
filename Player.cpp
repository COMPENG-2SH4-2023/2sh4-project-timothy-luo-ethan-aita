#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    // Creates the player symbol in the center of the gameboard
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPos.setObjPos(mainGameMechsRef -> getBoardSizeX() / 2, 
                        mainGameMechsRef -> getBoardSizeY() / 2,
                        '*');

    // more actions to be included
}


Player::~Player()
{
    // delete any heap members here
}

void Player::getPlayerPos(objPos &returnPos)
{
    // return the reference to the playerPos arrray list
    returnPos.setObjPos(playerPos.x, playerPos.y, playerPos.symbol);
}

void Player::updatePlayerDir()
{

    char input = mainGameMechsRef -> getInput();
    // PPA3 input processing logic  
    switch(input)
    {
        // If w is pressed, set player direction to up                      
        case 'w':
            if (myDir != UP && myDir != DOWN)
            {
                myDir = UP;
            }
            break;

        // If s is pressed, set player direction to down                      
        case 's':
            if (myDir != UP && myDir != DOWN)
            {
                myDir = DOWN;
            }
            break;

        // If a is pressed, set player direction to left                      
        case 'a':
            if (myDir != LEFT && myDir != RIGHT)
            {
                myDir = LEFT;
            }
            break;

        // If d is pressed, set player direction to right                      
        case 'd':
            if (myDir != LEFT && myDir != RIGHT)
            {
                myDir = RIGHT;
            }
            break;

        default:
            break;
    }  
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    switch(myDir)
    {
<<<<<<< HEAD
        // If player direction is up, move the player symbol up
        case UP:
            playerPos.y--;
            // If the player reaches the border, wrap around
            if (playerPos.y <= 0)
            {
                playerPos.y = mainGameMechsRef -> getBoardSizeX() - 2;
            }   
        case DOWN:
            // If player direction is down, move the player symbol down
            playerPos.y++;
            // If the player reaches the border, wrap around       
            if (playerPos.y == mainGameMechsRef -> getBoardSizeX() - 1)
            {
                playerPos.y = 1;
            }
        case LEFT:
            // If player direction is left, move the player symbol left
            playerPos.x--;
            // If the player reaches the border, wrap around
            if (playerPos.x <= 0)
            {
                playerPos.x = mainGameMechsRef -> getBoardSizeY() - 2;
            }
        case RIGHT:
            // If player direction is right, move the player symbol right
            playerPos.x++;
            // If the player reaches the border, wrap around
            if (playerPos.x == mainGameMechsRef -> getBoardSizeY() - 1)
            {
=======
        playerPos.y--;
        // If the player reaches the border, wrap around
        if (playerPos.y <= 0)
        {
            playerPos.y = mainGameMechsRef -> getBoardSizeY() - 2;
        }   
    }

    // If player direction is down, move the player symbol down
    else if (myDir == DOWN)
    {
        playerPos.y++;
        // If the player reaches the border, wrap around       
        if (playerPos.y == mainGameMechsRef -> getBoardSizeY() - 1)
        {
            playerPos.y = 1;
        }
    }

    // If player direction is left, move the player symbol left
    else if (myDir == LEFT)
    {
        playerPos.x--;
        // If the player reaches the border, wrap around
        if (playerPos.x <= 0)
        {
            playerPos.x = mainGameMechsRef -> getBoardSizeX() - 2;
        }
    }
    
    // If player direction is right, move the player symbol right
    else if (myDir == RIGHT)
    {
        playerPos.x++;
        // If the player reaches the border, wrap around
        if (playerPos.x == mainGameMechsRef -> getBoardSizeX() - 1)
        {
>>>>>>> 10f13b07612a674288cafdb73befeb71b5bba232
            playerPos.x = 1;
            }
    }
}

