#include <cstdlib>
#include <time.h>
//
#ifndef FOOD_H
#define FOOD_H
//
#define MAX_FOOD_CAP 3
#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"

using namespace std;


class Food
{
    private:
        objPos foodPos;
        
        objPosArrayList* foodBucket;
        GameMechs* foodGameMechsRef;

    public:
        Food(GameMechs* thisGM);
        ~Food();
        void generateFood(objPosArrayList* blockOff);
        void getFoodPos(objPos &returnPos);
        objPosArrayList* getFoodBucket();
};

#endif