#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"

using namespace std;

class Food : public GameMechs
{
    private:
        objPos foodPos;
        
        // objPosArrayList* foodBucket;

    public:
        Food();
        ~Food();
        void generateFood(objPos blockOff);
        void getFoodPos(objPos &returnPos);
};