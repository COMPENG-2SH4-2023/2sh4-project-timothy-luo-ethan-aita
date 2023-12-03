#include "Player.h"
#include "Food.h"
#include "GameMechs.h"

#include "MacUILib.h"
// REMOVE SCOTTS TESTING ELEMENTS
Player::Player(GameMechs* thisGMRef, Food* thisFoodRef)
{
    // Creates the player symbol in the center of the gameboard
    mainGameMechsRef = thisGMRef;
    foodRef = thisFoodRef;
    myDir = STOP;

    objPos tempPos; // this can be done in a simpler way?? dwbi.
    tempPos.setObjPos(mainGameMechsRef -> getBoardSizeX() / 2, 
                      mainGameMechsRef -> getBoardSizeY() / 2,
                     '*');

    // no heap member yet b/c haven't used new keyword
    playerPosList = new objPosArrayList[256];
    playerPosList-> insertHead(tempPos);

    arrayMaxxed = false; 


    // more actions to be included
    // for debugging, insertb 4 more segments
}


Player::~Player()
{
    // delete any heap members here
    delete[] playerPosList; 
}

//
bool Player::checkFoodConsumption()//objPos currentHeadPos)
{
    /*objPos currentFoodPos; 
    foodRef->getFoodPos(currentFoodPos);
    objPos currentHeadPos;
    playerPosList->getHeadElement(currentHeadPos);

    if(currentFoodPos.isPosEqual(&currentHeadPos))
    {
        return true;
    }
    else
    {
        return false;
    }*/
    objPos currentHeadPos;
    playerPosList -> getHeadElement(currentHeadPos);

    objPosArrayList* foodBucket = foodRef -> getFoodBucket();

    for (int i = 0; i < foodBucket -> getSize(); ++i)
    {
        objPos currentFoodPos;
        foodBucket -> getElement(currentFoodPos, i);

        if (currentFoodPos.getSymbolIfPosEqual(&currentHeadPos) == 'o')
        {
            return true;
            
        }
    }

    return false;
}

bool Player::checkSpecialFoodConsumption()//objPos currentHeadPos)
{
    objPos currentHeadPos;
    playerPosList -> getHeadElement(currentHeadPos);

    objPosArrayList* foodBucket = foodRef -> getFoodBucket();

    for (int i = 0; i < foodBucket -> getSize(); ++i)
    {
        objPos currentFoodPos;
        foodBucket -> getElement(currentFoodPos, i);

        if (currentFoodPos.getSymbolIfPosEqual(&currentHeadPos) == 'O')
        {
            return true;
            
        }
    }

    return false;
}

void Player::increasePlayerLength()
{
    playerPosList->insertHead(currentHead);
}


bool Player::checkSelfCollision() // this function returns true if self-colliding
{
    objPos currentHeadPos; //change to current head for a second
    objPos bodySegment;
    playerPosList-> getHeadElement(currentHeadPos);
    if(playerPosList -> getSize() != 0){
     for(int i = 1; i < playerPosList->getSize(); i++)
        {
            playerPosList -> getElement(bodySegment, i);
            if(currentHeadPos.isPosEqual(&bodySegment))
            {
                return true;
                break;
            }
        }
    }
}

objPosArrayList* Player::getPlayerPos()
{
    // return the reference to the playerPos arrray list
    //returnPos.setObjPos(playerPos.x, playerPos.y, playerPos.symbol);
    //returnPos = playerPos;
    return playerPosList;
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

    playerPosList -> getHeadElement(currentHead); // currentHead is in public scope

    switch(myDir)
    {
        // If player direction is up, move the player symbol up
        case UP:
            currentHead.y--;
            // If the player reaches the border, wrap around
            if (currentHead.y <= 0)
            {
                currentHead.y = mainGameMechsRef -> getBoardSizeY() - 2;
            }   
            break;

        case DOWN:
            // If player direction is down, move the player symbol down
            currentHead.y++;
            // If the player reaches the border, wrap around       
            if (currentHead.y == mainGameMechsRef -> getBoardSizeY() - 1) // is it -1 or just that?
            {
                currentHead.y = 1;
            }
            break;

        case LEFT:
            // If player direction is left, move the player symbol left
            currentHead.x--;
            // If the player reaches the border, wrap around
            if (currentHead.x <= 0)
            {
                currentHead.x = mainGameMechsRef -> getBoardSizeX() - 2;
            }
            break;

        case RIGHT:
            // If player direction is right, move the player symbol right
            currentHead.x++;
            // If the player reaches the border, wrap around
            if (currentHead.x == mainGameMechsRef -> getBoardSizeX() - 1)
            {
                currentHead.x = 1;
            }
            break;
    }


     if(checkSelfCollision())
    {   
        //MacUILib_printf("collision\n");
        mainGameMechsRef->setLoseFlag(); // sets lose flag true
        mainGameMechsRef->setExitTrue();
    }

    else{
        
    
    //playerPosList->insertHead(currentHead); // 
    // new current head should be inserted to current head of the list
    
    // we end the game with a termination error when it is equal to ARRAY_MAX_CAP b/c if you try increasing the length after this then
    // we will be going out of the array list bound
    if(playerPosList->getSize() == ARRAY_MAX_CAP)
                                                
    {   
        mainGameMechsRef->setExitTrue();
        arrayMaxxed = true;
    }
    
    else
    {   
    increasePlayerLength();

    if(checkFoodConsumption()) // make take no input 
    {   
        mainGameMechsRef->incrementScore();
        foodRef->generateFood(playerPosList);
    }
    else if(checkSpecialFoodConsumption())
    {
        mainGameMechsRef->specialScore();
        foodRef->generateFood(playerPosList);
        //playerPosList->removeHead();
        playerPosList->removeTail(); 
    }
    else
    {   
        playerPosList->removeTail(); // No overlap with food, carry out regular insert + remove
    }  
    
    }
    } 

}




