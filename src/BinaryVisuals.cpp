#include "../include/BinaryVisuals.h"
#include <limits.h>

static void BinaryVisuals::PrepareBit(ViewPortGL& targetWindow, int xPos, int yPos, int width, int height, bool isOne)
{
    //if bit is one, draw a filled box using two triangles
    if(isOne)
        targetWindow.prepareBlock(xPos, yPos, width, height, 255, 255, 255);
    //if bit is zero, draw empty box using four lines
    else
    {
        targetWindow.prepareLine(xPos, yPos, xPos+width, yPos, 255, 255, 255);
        targetWindow.prepareLine(xPos, yPos, xPos, yPos + height, 255, 255, 255);
        targetWindow.prepareLine(xPos + width, yPos, xPos+width, yPos + height, 255, 255, 255);
        targetWindow.prepareLine(xPos, yPos + height, xPos+width, yPos + height, 255, 255, 255);
    }
}

static void BinaryVisuals::PrepareRepresentation(ViewPortGL& targetWindow, int xPos, int yPos, int width, int height, unsigned char value)
{
    //get bit count in unsigned char input (n)
    int inputBitCount = sizeof(value) * CHAR_BIT;
    //iterate over char input n times from max to min
    //for each bit in char
    for(int i = inputBitCount - 1; i >= 0; i--)
    {
        //position is xpos + (width * i) + (buffer * (i - 1))
        int buffer = 10;
        //note: position calculation is right-to-left, but for loop is left-to-right, fix this
        //either fix the calculation by changing the offset
        //or
        //change the loop direction from right-to-left aswell
        int targetPosX = xPos + (width * i) + (buffer * (i - 1));
        //value is read from char
        bool targetValue = (value >> i) & 1;
        //prepare a new bit with those values
        PrepareBit(targetWindow, targetPosX, yPos, width, height, targetValue);

    }
}

static void BinaryVisuals::PrepareRepresentation(ViewPortGL& targetWindow, int xPos, int yPos, int width, int height, unsigned int value)
{
    //split int into n chars
    //iterate over split-list n times from max to min
    //for each char in int
        //prepare char
        //position is xpos + (width * i) + (buffer * (i - 1))
        //value is read from int

unsigned int BinaryVisuals::ExchangeHalves(unsigned int value, int fromBit, int toBit)
{
    //get delta between from and to bits
    //if delta % 2 != 0, return
    //create storage variable
    //iterate left starting from right
    //frombit to middle (frombit + delta / 2)
        //bitshift read value into storage
    //iterate left starting from middle
    //middle (frombit + delta / 2) to tobit
        //bitshift read value into storage
    //create replacing variable
    //iterate from input end (index 31) to tobit
        //bitshift read value into replacing
    //iterate over storage variable
        //bitshift read value into replacing
    //iterate from input frombit to start (index 0)
        //bitshift read value into replacing
    //return replacing
}

unsigned int BinaryVisuals::Reverse(unsigned int b)
{
    //create storage variable
    //iterate over input b from 0 to 31
        //bitshift read value into storage
    //return storage

    //alternatively, use suggestion from assignment sheet
}