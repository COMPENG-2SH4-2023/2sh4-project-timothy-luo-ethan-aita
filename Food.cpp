#include "GameMechs.h"
#include "MacUILib.h"
#include "Food.h"


using namespace std;

//Constructor
Food::Food()
{
    // Initialize foodPos outside board so it isn't displayed
    foodPos.setObjPos(-1, -1, 'o'); 
}

//Destructor
/*Food::~Food()
{

}*/

//Food Generation
void Food::generateFood(objPos blockOff)
{
    int randX, randY;

    do 
    {
        srand(time(NULL));
        // Generate random x and y coordinates
        randX = 1 + rand() % getBoardSizeX();
        randY = 1 + rand() % getBoardSizeY();
        
        // Check if randomly generated coordinates are on border or at the player position
        if ((foodPos.isPosEqual(&blockOff)) || 
            (randX == getBoardSizeX()) || 
            (randY == getBoardSizeY()))
        {
            //If true, continue generating and checking
            continue;
        }

        // Assign coordinates and symbol to the food
        foodPos.setObjPos(randX, randY, 'o');
    }while(false); // Exit the loop once suitable coordinates are found

    
    // check x and y against ) and boardSize X/Y

    // remember, in objPos class you have an isPosEqual() method. Use this instead of comparing element by element for your convenience
}

// Food Position Getter
void Food::getFoodPos(objPos &returnPos)
{
    returnPos = foodPos;
}