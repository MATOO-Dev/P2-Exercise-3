#include "../include/BinaryVisuals.h"
#include <cmath>
#include <cstddef>
#include <limits.h>
#include <iostream>
#include <stdexcept>

void BinaryVisuals::PrepareBit(ViewPortGL& targetWindow, int xPos, int yPos, int width, int height, bool isOne)
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

void BinaryVisuals::PrepareRepresentation(ViewPortGL& targetWindow, int xPos, int yPos, int width, int height, unsigned char value)
{
    //get bit count in unsigned char input (n)
    int inputBitCount = sizeof(value) * CHAR_BIT;
    //iterate over char input n times from max to min
    //for each bit in char
    for(int i = inputBitCount - 1; i >= 0; i--)
    {
        //tage origin point
        //add offset for previously drawn bits (inputbitcount - i - 1) * width
        //add offset for buffer spaces between previously drawn bits (inputbitcount * i - 1) * buffer
        int targetPosX = xPos + (inputBitCount - i - 1) * width + (inputBitCount - i - 1) * BinaryVisuals::bitBuffer;
        //value is read from char
        bool targetValue = (value >> i) & 1;
        //prepare a new bit with those values
        PrepareBit(targetWindow, targetPosX, yPos, width, height, targetValue);

    }
}

void BinaryVisuals::PrepareRepresentation(ViewPortGL& targetWindow, int xPos, int yPos, int width, int height, unsigned int value)
{
    //split int into 4 chars
    unsigned char charSplit[4];
    for(int i = 0; i <= 24; i += 8)
        charSplit[i/8] = (value >> i) ^ 0;

    //for each of the 4 chars
    for(int i = 3; i >= 0; i--)
    {
        //add offset for already placed bytes
        int targetPosX = xPos + (8 * width + 7 * bitBuffer + byteBuffer) * abs(i - 3);
        //call prepareRepresentation for char
        PrepareRepresentation(targetWindow, targetPosX, yPos, width, height, charSplit[i]);
    }
}

unsigned int BinaryVisuals::ExchangeHalves(unsigned int value, int fromBit, int toBit)
{
    //get delta between from and to bits
    int rangeDelta = toBit - fromBit;
    //if delta % 2 != 0, return
    if(rangeDelta % 2 != 0 || rangeDelta < 0)
        return 0;

    //create storage variable
    //iterate left starting from rights



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
    return value;
}

unsigned int BinaryVisuals::Reverse(unsigned int b)
{
    //create storage variable
    //iterate over input b from 0 to 31
        //bitshift read value into storage
    //return storage

    //alternatively, use suggestion from assignment sheet
    return 0;
}