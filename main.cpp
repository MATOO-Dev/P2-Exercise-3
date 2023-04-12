#include <iostream>
#include "include/glad.h"
#include <GLFW/glfw3.h>
#include "include/ViewPortGL.h"
#include "include/BinaryVisuals.h"

void test() {
    ViewPortGL vp = ViewPortGL("OpenGL Plain Test", 1000, 1000);
    bool isRunning = true;
    while (isRunning) {
        isRunning = !vp.windowShouldClose();

        vp.prepareTriangle(0, 999, 999, 999, 500, 0, 200, 0, 0, 0, 0, 200, 0, 200, 0);
        vp.sendTriangles();

        vp.swapBuffers();
    }
}

void Task1()
{
    ViewPortGL targetWindow = ViewPortGL("Task 1", 1000, 700);

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

void Task2(unsigned char input)
{
    //todo: console input
    //todo: add check if value is a valid unsigned char
    //input = 179;

    ViewPortGL targetWindow = ViewPortGL("Task 2", 1250, 550);

    BinaryVisuals::PrepareRepresentation(targetWindow, 50, 50, 50, 100, input);
    BinaryVisuals::PrepareRepresentation(targetWindow, 50, 250, 75, 75, input);
    BinaryVisuals::PrepareRepresentation(targetWindow, 50, 450, 100, 50, input);

    targetWindow.sendTriangles();
    targetWindow.sendLines();
    targetWindow.swapBuffers();

    while(!targetWindow.windowShouldClose());
}

int main()
{
    std::cout << "Hello World!" << std::endl;
    unsigned int input = 2016407690;
    unsigned char one = input << 8;
    unsigned char two = input << 8;
    unsigned char three = input << 8;
    unsigned char four = input << 8;

    std:: cout << one << two << three << four << std::endl;
    //test();
    //Task1();
    Task2(one);
    
    return 0;
}