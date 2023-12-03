#include "objPosArrayList.h"
#include "MacUILib.h"

// Paste your CUTE Tested implementation here.
// Paste your CUTE Tested implementation here.
// Paste your CUTE Tested implementation here.

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

// Default Constructor
objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP];
    listSize = 0;
    arrayCapacity = ARRAY_MAX_CAP;
}

// Destructor
objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize()
{
    // Returns list size
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    // Check to see if array is full
    if (listSize == arrayCapacity)
    {
        MacUILib_printf("The array is full");
        return;
    }

    for(int i = listSize; i > 0; i--)
    {
        // Shuffle all elements towards the tail
        aList[i].setObjPos(aList[i - 1]);

    }

    // Insert object at the head
    aList[0].setObjPos(thisPos);
    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    // Check to see if array is full
    if (listSize == arrayCapacity)
    {
        MacUILib_printf("The array is full");
        return;
    }

    // Insert object at the tail
    aList[listSize].setObjPos(thisPos);
    listSize++;
}

// Remove object at the head   
void objPosArrayList::removeHead()
{
    if (listSize > 0)
    {
        for(int i = 0; i < listSize; i++)
        {
            // Shuffle all elements towards the tail
            aList[i].setObjPos(aList[i + 1]);

        }
        listSize--;
    }
}

// Removes object at the tail
void objPosArrayList::removeTail()
{
    if (listSize > 0)
    {
        listSize--;
    }
}

// gets the element at the head
void objPosArrayList::getHeadElement(objPos &returnPos)
{
    if (listSize > 0)
    {
    returnPos.setObjPos(aList[0]);
    }
}

// gets the element at the tail
void objPosArrayList::getTailElement(objPos &returnPos)
{
    if (listSize > 0)
    {
    returnPos.setObjPos(aList[listSize - 1]);
    }
}

// Gets the element at the specified index
void objPosArrayList::getElement(objPos &returnPos, int index)
{
    if (index >= 0 && index <= listSize)
    {
    returnPos.setObjPos(aList[index]);
    }
}