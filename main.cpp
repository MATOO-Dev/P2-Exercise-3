#include <KHR/khrplatform.h>
#include <iostream>
#include "include/glad.h"
#include <GLFW/glfw3.h>
#include "include/ViewPortGL.h"
#include "include/BinaryVisuals.h"
#include <chrono>
#include <thread>

void Task1A()
{
    ViewPortGL targetWindow = ViewPortGL("Task 1-A) bits", 1000, 700);

    BinaryVisuals::PrepareBit(targetWindow, 100, 100, 200, 200, true);
    BinaryVisuals::PrepareBit(targetWindow, 400, 100, 200, 200, true);
    BinaryVisuals::PrepareBit(targetWindow, 700, 100, 200, 200, true);
    BinaryVisuals::PrepareBit(targetWindow, 100, 400, 200, 200, false);
    BinaryVisuals::PrepareBit(targetWindow, 400, 400, 200, 200, false);
    BinaryVisuals::PrepareBit(targetWindow, 700, 400, 200, 200, false);

    targetWindow.sendTriangles();
    targetWindow.sendLines();
    targetWindow.swapBuffers();

    while(!targetWindow.windowShouldClose());
}

void Task1B(unsigned char input)
{
    //exercise sheet value is 179
    ViewPortGL targetWindow = ViewPortGL("Task 1-B) uchar-8", 1250, 550);

    BinaryVisuals::PrepareRepresentation(targetWindow, 50, 50, 50, 100, input);
    BinaryVisuals::PrepareRepresentation(targetWindow, 50, 250, 75, 75, input);
    BinaryVisuals::PrepareRepresentation(targetWindow, 50, 450, 100, 50, input);

    targetWindow.sendTriangles();
    targetWindow.sendLines();
    targetWindow.swapBuffers();

    while(!targetWindow.windowShouldClose());
}

void Task1C(unsigned int input)
{
    //exercise sheet value is 2016407690
    ViewPortGL targetWindow = ViewPortGL("Task 1-C) uint-32", 1500, 215);

    BinaryVisuals::PrepareRepresentation(targetWindow, 20, 20, 32, 100, input);
    BinaryVisuals::PrepareRepresentation(targetWindow, 20, 170, 32, 25, input);

    targetWindow.sendTriangles();
    targetWindow.sendLines();
    targetWindow.swapBuffers();

    while(!targetWindow.windowShouldClose());
}

void Task1D(long stepDelay)
{    
    ViewPortGL targetWindow = ViewPortGL("Task 1-D) animated uint-32", 1500, 140);
    int i = 0;
    while(i <= 0xffffffff && !targetWindow.windowShouldClose())
    {
        BinaryVisuals::PrepareRepresentation(targetWindow, 20, 20, 32, 100, (unsigned int)i);
        targetWindow.sendTriangles();
        targetWindow.sendLines();
        targetWindow.swapBuffers();
        this_thread::sleep_for(chrono::milliseconds(stepDelay));
        i++;
    }

    while(!targetWindow.windowShouldClose());
}

void Task2(unsigned int value, int fromBit, int toBit)
{
    //1500x265
    ViewPortGL targetWindow = ViewPortGL("Task 2", 1500, 500);
    
    unsigned int changedValue = BinaryVisuals::ExchangeHalves(value, fromBit, toBit);

    //BinaryVisuals::PrepareRepresentation(targetWindow, 20, 20, 32, 100, value);





    //26 is 32bit - delta(tobit-frombit)
    //store first bits so they dont get lost
    unsigned int storage = value << 26 >> 26 ^ 0;

    //7 is frombit index
    //extract range to flip
    unsigned int extract = value >> 7 << 26 >> 26 ^ 0;


    //split extract into 2, then flip them
    //3 is delta(tobit-frombit)/2
    unsigned int leftHalf = extract >> 3;
    std::cout << "left half value is " << leftHalf << ", should be 3" << std::endl;

    //29 is 32bit - delta(tobit-frombit)/2
    unsigned int rightHalf = extract << 29 >> 29;
    std::cout << "right half value is " << rightHalf << ", should be 5" << std::endl;

    extract = 0 | rightHalf << 3 | leftHalf;




    //merge everything back together
    //13 is tobit index + 1
    unsigned int merge = value >> 13;
    merge = merge << 6 | extract;
    merge = merge << 7 | storage;




    if(merge == 2383394201)
        std::cout << "success" << std::endl;
    else
        std::cout << "not quite there yet" << std::endl;










    //display results
    BinaryVisuals::PrepareRepresentation(targetWindow, 20, 20, 32, 100, value);
    BinaryVisuals::PrepareRepresentation(targetWindow, 20, 140, 32, 100, extract);
    BinaryVisuals::PrepareRepresentation(targetWindow, 20, 260, 32, 100, storage);
    BinaryVisuals::PrepareRepresentation(targetWindow, 20, 380, 32, 100, merge);

    targetWindow.sendLines();
    targetWindow.sendTriangles();
    targetWindow.swapBuffers();

    while(!targetWindow.windowShouldClose());
}

int main()
{
    //Task1A();
    //Task1B(179);
    //Task1C(2016407690);
    //Task1D(500);
    Task2(2383392409, 7, 12);
    
    return 0;
}