#include "GameMechs.h"
#include "MacUILib.h"
#include "Food.h"


using namespace std;

//Default Constructor
Food::Food(GameMechs* thisGM)
{
    // Initialize foodPos outside board so it isn't displayed
    //foodPos.setObjPos(-1, -1, 'o'); 
    foodGameMechsRef = thisGM;
    //MacUILib_printf("x: %c, y: %c \n", objPos.x, objPos.y);
    srand(time(NULL));
}

//Destructor
Food::~Food()
{

}

//Food Generation
void Food::generateFood(objPosArrayList* blockOff)
{
    int randX, randY;
    bool overlap; // interference with the snake body flag
    do 
    {   
        
        randX = 1 + rand() % (foodGameMechsRef->getBoardSizeX() - 1);
        randY = 1 + rand() % (foodGameMechsRef->getBoardSizeY() - 1);
        foodPos.setObjPos(randX, randY, 'o'); // Assign coordinates and symbol to the food

        objPos bodySegment;
        overlap = false;

        for(int i = 0; i < blockOff->getSize(); i++)
        {
            blockOff->getElement(bodySegment, i);
            if(foodPos.isPosEqual(&bodySegment))
            {
                overlap = true;
                break;
            }
        }
        
        
        if ((overlap) || (randX == foodGameMechsRef->getBoardSizeX() - 1) || 
            (randY == foodGameMechsRef->getBoardSizeY() - 1)) // Check if randomly generated coordinates are on border or at the player position
        {
            //If true, continue generating and checking
            continue;
        }
        
        //MacUILib_printf("x: %c, y: %c \n", randX, randY);
    }while((overlap) || (randX == foodGameMechsRef->getBoardSizeX() - 1) || 
            (randY == foodGameMechsRef->getBoardSizeY() - 1)); // Exit the loop once suitable coordinates are found
    
    // check x and y against ) and boardSize X/Y

    // remember, in objPos class you have an isPosEqual() method. Use this instead of comparing element by element for your convenience
}

// Food Position Getter
void Food::getFoodPos(objPos &returnPos)
{
    returnPos = foodPos;
}