#include <cstdlib>
#include <time.h>
//
#ifndef FOOD_H
#define FOOD_H
//
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
        //int bucketSize;

    public:
        Food(GameMechs* thisGM);
        ~Food();
        //void generateFood(objPos blockOff); //  upgrade
        void generateFood(objPosArrayList* blockOff); // upgrade
        void getFoodPos(objPos &returnPos);
        objPosArrayList* getFoodBucket();
};

#endif