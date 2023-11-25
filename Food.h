#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"

using namespace std;

class Food
{
    private:
        objPos foodPos;

    public:
        Food();
        ~Food();
        void generateFood(objPos blockOff);
        void getFoodPos(objPos &returnPos);
};