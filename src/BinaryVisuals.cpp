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

unsigned int BinaryVisuals::ExchangeHalves(unsigned int value, int fromBit, int toBit, ViewPortGL& debug)
{
    //get delta between from and to bits
    int rangeDelta = toBit - fromBit + 1;

    //if delta % 2 != 0, return
    if(rangeDelta % 2 != 0 || rangeDelta < 0)
        return 0;

    //store first bits so they dont get lost
    //move left so everything except left storage is gone -> move back right
    unsigned int storage = value << (32-fromBit) >> (32-fromBit);

    //extract range to flip
    //move left so left storage is gone -> move back and further so right storage is gone
    unsigned int extract = value << (32-toBit-1) >> (32+fromBit-toBit-1);

    //extract left half
    //move right so right half is gone
    unsigned int leftHalf = extract >> (rangeDelta / 2);

    //extract right half
    //move left so left half is gone -> move back to correct position
    unsigned int rightHalf = extract << (32 - rangeDelta / 2) >> (32 - rangeDelta / 2);

    //swap halves
    //put in right half -> move by 1 half -> put in left half
    extract = 0 | rightHalf << (rangeDelta / 2) | leftHalf;

    //merge everything back together
    //move so only left storage stays over
    unsigned int merge = value >> (toBit + 1);

    //add in the extract    
    //move left by 2 halves and add the flipped value
    merge = merge << rangeDelta | extract;

    //add in the storage
    //move left by frombit and add back storage
    merge = merge << fromBit | storage;
    
    return merge;        


    ///more compressed code:
    /*
    //create right storage
        unsigned int storage = value << (32-fromBit) >> (32-fromBit);
    //extract range to flip
        unsigned int extract = value << (32-toBit-1) >> (32+fromBit-toBit-1);
    //extract left half
        unsigned int leftHalf = extract >> (rangeDelta / 2);
    //extract right half
        unsigned int rightHalf = extract << (32 - rangeDelta / 2) >> (32 - rangeDelta / 2);
    //swap halves
        extract = 0 | rightHalf << (rangeDelta / 2) | leftHalf;
    //merge everything back together
        unsigned int merge = value >> (toBit + 1) << rangeDelta | extract << fromBit | storage;
    return merge;    
    */
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