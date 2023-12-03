#include "Player.h"
#include "Food.h"
#include "GameMechs.h"

#include "MacUILib.h"

Player::Player(GameMechs* thisGMRef, Food* thisFoodRef)
{
    
    mainGameMechsRef = thisGMRef;
    foodRef = thisFoodRef;
    myDir = STOP;

    // Create player symbol in center of gameboard
    objPos tempPos; 
    tempPos.setObjPos(mainGameMechsRef -> getBoardSizeX() / 2, mainGameMechsRef -> getBoardSizeY() / 2, '*');
    
    // Initialize snake body on the heap
    playerPosList = new objPosArrayList[256];
    playerPosList -> insertHead(tempPos);

    arrayMaxxed = false; 
}


Player::~Player()
{
    delete[] playerPosList; 
}

bool Player::checkFoodConsumption()
{
    // Localized references
    objPos currentHeadPos;
    playerPosList -> getHeadElement(currentHeadPos); 
    objPosArrayList* foodBucket = foodRef -> getFoodBucket();

    // Check if snake head touches any normal food item 'o'
    for(int i = 0; i < foodBucket -> getSize(); ++i)
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

bool Player::checkSpecialFoodConsumption()
{
    // Localized references
    objPos currentHeadPos;
    playerPosList -> getHeadElement(currentHeadPos);
    objPosArrayList* foodBucket = foodRef -> getFoodBucket();

    // Check if snake head touches any special food item 'O'
    for(int i = 0; i < foodBucket -> getSize(); ++i)
    {
        objPos currentFoodPos;
        foodBucket -> getElement(currentFoodPos, i);

        if(currentFoodPos.getSymbolIfPosEqual(&currentHeadPos) == 'O')
        {
            return true;   
        }
    }

    return false;
}

void Player::increasePlayerLength()
{   
    // Add '*' to snake body at head
    playerPosList -> insertHead(currentHead);
}

bool Player::checkSelfCollision() 
{
    objPos currentHeadPos; 
    objPos bodySeg;
    playerPosList-> getHeadElement(currentHeadPos);

    // No need to check self-collision for a 1-unit snake
    if(playerPosList -> getSize() > 1){

    // Check if snake head intersects with any element of snakebody
     for(int i = 1; i < playerPosList->getSize(); i++)
        {
            playerPosList -> getElement(bodySeg, i);
            if(currentHeadPos.isPosEqual(&bodySeg))
            {
                return true; // True if snake self-intersects
                break;
            }
        }
    }
}

objPosArrayList* Player::getPlayerPos()
{
    return playerPosList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic  
    char input = mainGameMechsRef -> getInput();

    switch(input)
    {
        // If w is pressed, set player direction to up                      
        case 'w':
            if(myDir != UP && myDir != DOWN)
            {
                myDir = UP;
            }
            break;

        // If s is pressed, set player direction to down                      
        case 's':
            if(myDir != UP && myDir != DOWN)
            {
                myDir = DOWN;
            }
            break;

        // If a is pressed, set player direction to left                      
        case 'a':
            if(myDir != LEFT && myDir != RIGHT)
            {
                myDir = LEFT;
            }
            break;

        // If d is pressed, set player direction to right                      
        case 'd':
            if(myDir != LEFT && myDir != RIGHT)
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
    // PPA3 finite state machine logic

    playerPosList -> getHeadElement(currentHead); 

    switch(myDir)
    {
        // If player direction is up, move the player symbol up
        case UP:
            currentHead.y--;

            // If the player reaches the border, wrap around
            if(currentHead.y <= 0)
            {
                currentHead.y = mainGameMechsRef -> getBoardSizeY() - 2;
            }   
            break;

        // If player direction is down, move the player symbol down
        case DOWN:
            currentHead.y++;
        
            // If the player reaches the border, wrap around       
            if(currentHead.y == mainGameMechsRef -> getBoardSizeY() - 1) // is it -1 or just that?
            {
                currentHead.y = 1;
            }
            break;

        // If player direction is left, move the player symbol left
        case LEFT:
            currentHead.x--;

            // If the player reaches the border, wrap around
            if(currentHead.x <= 0)
            {
                currentHead.x = mainGameMechsRef -> getBoardSizeX() - 2;
            }
            break;

        // If player direction is right, move the player symbol right
        case RIGHT:
            currentHead.x++;

            // If the player reaches the border, wrap around
            if (currentHead.x == mainGameMechsRef -> getBoardSizeX() - 1)
            {
                currentHead.x = 1;
            }
            break;
    }

    // Player will not move any further if there is self-collision
     if(checkSelfCollision())
    {   
        // Lose flag triggers a program exit and a unique print message
        mainGameMechsRef -> setLoseFlag(); 
        mainGameMechsRef -> setExitTrue();
    }

    else{
        // Player will not move any further if array list reaches capacity
        if(playerPosList -> getSize() == ARRAY_MAX_CAP)                                    
        {   
            // Reaching maximum array capacity triggers a program exit and a unique print message
            mainGameMechsRef -> setExitTrue();
            arrayMaxxed = true;
        }
    
        else
        {   

            increasePlayerLength(); 

            if(checkFoodConsumption())  
            {   
                // Consuming normal food increases score and snake length by 1
                mainGameMechsRef -> incrementScore();
                foodRef -> generateFood(playerPosList);
            }

            else if(checkSpecialFoodConsumption())
            {
                // Consuming special food increases score by 10 while not increasing snake length
                mainGameMechsRef -> specialScore();
                foodRef -> generateFood(playerPosList);
                playerPosList -> removeTail(); 
            }

            else
            {   
                // No overlap with food carries out normal snake motion with no body increase
                playerPosList -> removeTail(); 
            }  
        }
    } 
}




