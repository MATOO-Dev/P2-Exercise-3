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

    while(!targetWindow.windowShouldClose()) 
        this_thread::sleep_for(chrono::milliseconds(100));
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

    while(!targetWindow.windowShouldClose()) 
        this_thread::sleep_for(chrono::milliseconds(100));
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

    while(!targetWindow.windowShouldClose()) 
        this_thread::sleep_for(chrono::milliseconds(100));
}

void Task1D(long stepDelay)
{    
    ViewPortGL targetWindow = ViewPortGL("Task 1-D) animated uint-32", 1500, 140);
    unsigned int i = 0;
    while(i <= 0xffffffff && !targetWindow.windowShouldClose())
    {
        BinaryVisuals::PrepareRepresentation(targetWindow, 20, 20, 32, 100, (unsigned int)i);
        targetWindow.sendTriangles();
        targetWindow.sendLines();
        targetWindow.swapBuffers();
        this_thread::sleep_for(chrono::milliseconds(stepDelay));
        i++;
    }

    while(!targetWindow.windowShouldClose()) 
        this_thread::sleep_for(chrono::milliseconds(100));
}

void Task2(unsigned int value, int fromBit, int toBit)
{
    //260
    ViewPortGL targetWindow = ViewPortGL("Task 2 - swap halves", 1500, 260);
    
    //flip bit blocks
    unsigned int changedValue = BinaryVisuals::ExchangeHalves(value, fromBit, toBit);

    //display results
    //original value
    BinaryVisuals::PrepareRepresentation(targetWindow, 20, 20, 32, 100, value);
    
    //calulcated value
    BinaryVisuals::PrepareRepresentation(targetWindow, 20, 140, 32, 100, changedValue);

    targetWindow.sendLines();
    targetWindow.sendTriangles();
    targetWindow.swapBuffers();

    while(!targetWindow.windowShouldClose()) 
        this_thread::sleep_for(chrono::milliseconds(100));
}

void Task3(unsigned int value)
{
    ViewPortGL targetWindow = ViewPortGL("Task 3 - reverse", 1500, 500);
    
    //flip bit blocks
    unsigned int reversedValue = BinaryVisuals::Reverse(value, 32, targetWindow);

    //display results
    //original value
    BinaryVisuals::PrepareRepresentation(targetWindow, 20, 20, 32, 100, value);
    
    //reversed value
    //140 or 380
    BinaryVisuals::PrepareRepresentation(targetWindow, 20, 140, 32, 100, reversedValue);

    targetWindow.sendLines();
    targetWindow.sendTriangles();
    targetWindow.swapBuffers();

    while(!targetWindow.windowShouldClose()) 
        this_thread::sleep_for(chrono::milliseconds(100));
}

int main()
{
    //Task1A();
    //Task1B(179);
    //Task1C(2016407690);
    //Task1D(500);
    Task2(2383392409, 7, 12);
    //Task3(2383392409);
    return 0;


    
}