#include "GameMechs.h"
#include "MacUILib.h"
#include "Food.h"


using namespace std;

//Default Constructor
Food::Food(GameMechs* thisGM)
{
    foodGameMechsRef = thisGM;
    foodBucket = new objPosArrayList[MAX_FOOD_CAP];
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
    //Clear all contents of the food bucket
    for (int i = 0; i < MAX_FOOD_CAP; i++)
    {
        foodBucket -> removeTail();
    }

    //Generate 3 items to be stored in the foodbucket    
    for (int i = 0; i < MAX_FOOD_CAP; i++)
    {
        int randX, randY;
        bool overlap; // interference with the snake body flag
        do 
        {   
            //Generate random x and y coordinates for the food
            randX = 1 + rand() % (foodGameMechsRef->getBoardSizeX() - 1);
            randY = 1 + rand() % (foodGameMechsRef->getBoardSizeY() - 1);

            if (i % 2 == 0)
            {
                // Assign coordinates and symbol to the normal food
                foodPos.setObjPos(randX, randY, 'o'); 
            }
            else
            {
                // Assign coordinates and symbol to the special food  
                foodPos.setObjPos(randX, randY, 'O'); 
            }
            

            objPos bodySegment;
            objPos inBucket;
            overlap = false;

            //Check if random food coords overlap with any segments of the snake body
            for(int j = 0; j < blockOff->getSize(); j++)
            {
                blockOff->getElement(bodySegment, j);
                if(foodPos.isPosEqual(&bodySegment))
                {
                    overlap = true;
                    break;
                }
            }
            
            //Check if random food coords overlap with any of the previously generated food coords
            for (int k = 0; k < i; k++)
            {
                blockOff -> getElement(inBucket, k);
                if (foodPos.isPosEqual(&inBucket))
                {
                    overlap = true;
                    break;
                }
            }
            
        }while((overlap) || (randX == foodGameMechsRef->getBoardSizeX() - 1) || 
                (randY == foodGameMechsRef->getBoardSizeY() - 1)); // Exit the loop once suitable coordinates are found

        //Add the food to the bucket
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
