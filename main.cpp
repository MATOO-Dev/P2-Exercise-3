#include <iostream>
#include "include/glad.h"
#include <GLFW/glfw3.h>
#include "include/ViewPortGL.h"

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

int main()
{
    std::cout << "Hello World!" << std::endl;
    test();
    
    return 0;
}