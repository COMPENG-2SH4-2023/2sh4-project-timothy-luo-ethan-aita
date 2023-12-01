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
    
    myFood->generateFood(playerBody); // how do I turn this into array list operation?
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

    bool drawn;

    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    objPos bodySeg; // declaring body segments

    objPos foodItemPos; // the current item food Pos
    myFood->getFoodPos(foodItemPos);

    for(int i = 0; i < myGM -> getBoardSizeY(); i++)
    {
        for(int j = 0; j < myGM -> getBoardSizeX(); j++)
        {   
            drawn = false;
            // iterate through every element in the array list
            for(int k = 0; k < playerBody->getSize(); k++)
            {
                playerBody->getElement(bodySeg, k); // accessing body segments
                if(bodySeg.x == j && bodySeg.y == i)
                {
                    MacUILib_printf("%c", bodySeg.symbol);
                    drawn = true;
                    break;
                }
            }

            if(drawn) continue; // don't draw anything below if player body was drawn

            // draw border
            if (i == 0 || i == myGM -> getBoardSizeY() - 1 || j == 0 || j == myGM -> getBoardSizeX() - 1)
            {
                MacUILib_printf("%c", '#');
            }
            else if (i == foodItemPos.y && j == foodItemPos.x)
            {
                MacUILib_printf("%c", foodItemPos.symbol);
            }
            else
            {
                MacUILib_printf("%c", ' ');
            }
        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("BoardSize: %dx%d, Score: %d", myGM -> getBoardSizeX(), myGM -> getBoardSizeY(),
myGM -> getScore()); 
//change tempPos to temp Body
MacUILib_printf("\nPlayer Positions:");
for(int l = 0; l < playerBody->getSize(); l++)
{
    playerBody->getElement(bodySeg, l);
    MacUILib_printf("<%d, %d> ", bodySeg.x, bodySeg.y);
}
MacUILib_printf("\nFood Pos: <%d, %d> \n", foodItemPos.x, foodItemPos.y);

if(myGM->getLoseFlagStatus())
{
    MacUILib_printf("You lose!\n");
} 

if(!myGM->getLoseFlagStatus() && myGM->getExitFlagStatus())
{
    MacUILib_printf("Game Ended.\n");
}

}

//MacUILib_printf("%s\n", myGM->getExitFlagStatus());
//MacUILib_printf("%s\n", myGM->getLoseFlagStatus());


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
