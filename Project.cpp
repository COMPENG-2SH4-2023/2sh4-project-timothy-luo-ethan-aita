#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "objPosArrayList.h"
#include "Player.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs* myGM;
Player* myPlayer;
Food* myFood;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM -> getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    // Make game board size with dimensions 30x15
    myGM = new GameMechs(30, 15);
    myFood = new Food(myGM);
    myPlayer = new Player(myGM, myFood);
    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    
    myFood->generateFood(playerBody); 
}

void GetInput(void)
{
    myGM -> getInput();
}

void RunLogic(void)
{
    myPlayer -> updatePlayerDir();
    myPlayer -> movePlayer();
    myGM -> clearInput();  
}

void DrawScreen(void)
{   
    MacUILib_clearScreen();
    bool drawn, foodDrawn;

    objPosArrayList* playerBody = myPlayer -> getPlayerPos();
    objPos bodySeg; // declaring body segments

    objPosArrayList* foodBucket = myFood -> getFoodBucket();
    objPos foodBucketPos; // the current item food Pos

    for(int i = 0; i < myGM -> getBoardSizeY(); i++)
    {
        for(int j = 0; j < myGM -> getBoardSizeX(); j++)
        {   
            drawn = false;
            // Iterate through every element in the array list
            for(int k = 0; k < playerBody -> getSize(); k++)
            {
                playerBody -> getElement(bodySeg, k); // accessing body segments
                if(bodySeg.x == j && bodySeg.y == i)
                {
                    MacUILib_printf("%c", bodySeg.symbol);
                    drawn = true;
                    break;
                }
            }

            foodDrawn = false;
            // Iterate through every element of the food bucket and draw them
            for(int h = 0; h < foodBucket -> getSize(); h++)
            {
                // Access the foodbucket coords
                foodBucket -> getElement(foodBucketPos, h);
                if (foodBucketPos.x == j && foodBucketPos.y == i)
                {
                    MacUILib_printf("%c", foodBucketPos.symbol);
                    foodDrawn = true;
                    break;
                }
            }

            if(drawn || foodDrawn) continue; // don't draw anything below if player body was drawn

            // draw border
            if (i == 0 || i == myGM -> getBoardSizeY() - 1 || j == 0 || j == myGM -> getBoardSizeX() - 1)
            {
                MacUILib_printf("%c", '#');
            }
            // Empty spaces
            else
            {
                MacUILib_printf("%c", ' ');
            }
        }
        MacUILib_printf("\n");
    }

    // Print the board size and game score
    MacUILib_printf("BoardSize: %dx%d, Score: %d", myGM -> getBoardSizeX(), myGM -> getBoardSizeY(),
    myGM -> getScore()); 

    // Print the coords of the snake body
    MacUILib_printf("\nPlayer Positions: ");
    for(int l = 0; l < playerBody -> getSize(); l++)
    {
        playerBody -> getElement(bodySeg, l);
        MacUILib_printf("<%d, %d> ", bodySeg.x, bodySeg.y);
    }

    // Print the coords of the food
    MacUILib_printf("\nFood Bucket: ");
    for(int l = 0; l < foodBucket -> getSize(); l++)
    {
        foodBucket -> getElement(foodBucketPos, l);
        MacUILib_printf("<%d, %d> ", foodBucketPos.x, foodBucketPos.y);
    }

    MacUILib_printf("\n");

    // Game end conditions below
    if(myGM->getExitFlagStatus() )
    {
        MacUILib_clearScreen();
    }

    if(myGM->getLoseFlagStatus())
    {   
        MacUILib_printf("You lose! Your final score is %d.\n", myGM->getScore());
    } 

    if(!myGM->getLoseFlagStatus() && !myPlayer->arrayMaxxed && myGM->getExitFlagStatus())
    {
        MacUILib_printf("Game Ended.\n");
    }

    if(myPlayer->arrayMaxxed && myGM->getExitFlagStatus())
    {
        MacUILib_printf("TERMINATION ERROR: Array list has reached maximum capacity.\n");
    }
}


void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    //MacUILib_clearScreen();    
  
    MacUILib_uninit();

    delete myGM;
    delete myPlayer;
    delete myFood;
}
