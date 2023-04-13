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
    //7,12  -> delta 6  -> 25 -> retain 7 bits
    //8,23  -> delta 16 -> 24 -> retain 8 bits
    //4,7   -> delta 4  -> 28 -> retain 4 bits
    unsigned int storage = value << (32-fromBit) >> (32-fromBit) ^ 0;

    //extract range to flip
    //1     -> push out storage on the right    -> frombit
    //2     -> push out overflow on left        -> 32-frombit
    //3     -> move to right                    -> 32-frombit
    //7,12  -> delta 6  -> 7-26-26 -> frombit-(32-delta+1)-(32-delta+1)
    //8,23  -> delta 16 -> 8-16-16 -> frombit-(32-delta)-(32-delta)
    //4,7   -> delta 4  -> 4-28-28 -> frombit-(32-delta)-(32-delta)
    //7,12  -> overflow 19  -> 26 = overflow-frombit   -> overflow = 32-tobit-1 = 19    ->
    //8,23  -> overflow 8   -> 16 = overflow-frombit   -> overflow = 32-tobit-1 = 8     -> 
    //4,7   -> overflow 24  -> 28 = overflow-frombit   -> overflow = 32-tobit-1 = 24    -> 24 + frombit

    //7,12  -> 32+frombit-tobit-1 = 32+7-12-1 = 26
    //8,23  -> 32+frombit-tobit-1 = 32+8-23-1 = 16
    //4,7   -> 32+frombit-tobit-1 = 32+4-7-1  = 28

    //------------> 32+frombit-tobit-1
    unsigned int extract = value >> fromBit << (32+fromBit-toBit-1) >> (32+fromBit-toBit-1) ^ 0;

    //extract left half
    //7,12  -> delta 6  -> 3    -> delta/2
    //8,23  -> delta 16 -> 8    -> delta/2
    //4,7   -> delta 4  -> 2    -> delta/2
    unsigned int leftHalf = extract >> (rangeDelta / 2);

    //extract right half
    //7,12  -> delta 6  -> 29 -> 32-delta/2
    //8,23  -> delta 16 -> 24 -> 32-delta/2
    //4,7   -> delta 4  -> 30 -> 32-delta/2
    unsigned int rightHalf = extract << (32 - rangeDelta / 2) >> (32 - rangeDelta / 2);

    //swap halves
    //7,12  -> delta 6  -> 4    -> delta/2
    //8,23  -> delta 16 -> 8    -> delta/2
    //4,7   -> delta 4  -> 2    -> delta/2
    extract = 0 | rightHalf << (rangeDelta / 2) | leftHalf;

    //merge everything back together
    //7,12  -> delta 6  -> 13 -> alles außer erste 19   -> tobit+1
    //8,23  -> delta 16 -> 24 -> alles außer erste 8    -> tobit+1
    //4,7   -> delta 4  -> 8 -> alles außer erste 24    -> tobit+1
    unsigned int merge = value >> (toBit + 1);

    //add in the extract    -> rangedelta
    merge = merge << rangeDelta | extract;

    //add in the storage    -> frombit
    //7,12  -> delta 6  -> 7 -> store 7 bits
    //8,23  -> delta 16 -> 8 -> store 8 bits
    //4,7   -> delta 4  -> 4 -> store 4 bits
    merge = merge << fromBit | storage;
    
    return merge;        
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