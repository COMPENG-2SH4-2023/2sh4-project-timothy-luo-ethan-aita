#include "GameMechs.h"
#include "MacUILib.h"
#include "Food.h"


using namespace std;

//Default Constructor
Food::Food(GameMechs* thisGM)
{
    foodGameMechsRef = thisGM;
    foodBucket = new objPosArrayList[3];
    srand(time(NULL));
}

//Destructor
Food::~Food()
{
    delete[] foodBucket;
}

//Food Generation
void Food::generateFood(objPosArrayList* blockOff)
{
    for (int i = 0; i < 3; i++)
    {
        foodBucket -> removeTail();
    }
        
    for (int i = 0; i < 3; i++)
    {
        int randX, randY;
        bool overlap; // interference with the snake body flag
        do 
        {   
            
            randX = 1 + rand() % (foodGameMechsRef->getBoardSizeX() - 1);
            randY = 1 + rand() % (foodGameMechsRef->getBoardSizeY() - 1);

            if (i < 2)
            {
                foodPos.setObjPos(randX, randY, 'o'); // Assign coordinates and symbol to the food  
            }
            else{
                foodPos.setObjPos(randX, randY, 'O'); // Assign coordinates and symbol to the food  
            }
            

            objPos bodySegment;
            objPos inBucket;
            overlap = false;

            for(int j = 0; j < blockOff->getSize(); j++)
            {
                blockOff->getElement(bodySegment, j);
                if(foodPos.isPosEqual(&bodySegment))
                {
                    overlap = true;
                    break;
                }
            }

            for (int k = 0; k < i; k++)
            {
                blockOff -> getElement(inBucket, k);
                if (foodPos.isPosEqual(&inBucket))
                {
                    overlap = true;
                    break;
                }
            }
            
            //MacUILib_printf("x: %c, y: %c \n", randX, randY);
        }while((overlap) || (randX == foodGameMechsRef->getBoardSizeX() - 1) || 
                (randY == foodGameMechsRef->getBoardSizeY() - 1)); // Exit the loop once suitable coordinates are found

        foodBucket -> insertTail(foodPos);
    }
        
}

// Food Position Getter
void Food::getFoodPos(objPos &returnPos)
{
    returnPos = foodPos;
}

objPosArrayList* Food::getFoodBucket()
{
    return foodBucket;
}
