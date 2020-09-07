#include "cell.h"

void turnOnBit(unsigned char &cell, unsigned char mask)
{
    cell |= mask;
}

void turnOffBit(unsigned char &cell, unsigned char mask)
{
    cell &= ~mask;
}

int checkBit(unsigned char &cell,unsigned char mask)
{
    if(cell & mask)
    {
        return 1;
    }
    else
    {
        return 0;
    }
} 