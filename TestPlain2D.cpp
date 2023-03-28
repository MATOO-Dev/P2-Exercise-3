#include "ViewPortGL.h"
#include <cmath>
#include <algorithm>

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

void Task2(int windowWidthX, int windowWidthY, int widthX, int widthY)
{
	//generate window with correct dimensions
	ViewPortGL targetWindow = ViewPortGL("Task2", windowWidthX, windowWidthY);

	//prepare rendering the image and send to window
	//note: this is only done once instead of within the while loop, as we do not expect this to change
	//for a more realistic scenario, move the following block into the while-loop to execute it every frame
	targetWindow.prepareLine(500 - (widthX / 2), 500 - (widthY / 2), 500 + (widthX / 2), 500 - (widthY / 2), 255, 255, 255, 255, 255, 255);
	targetWindow.prepareLine(500 - (widthX / 2), 500 + (widthY / 2), 500 + (widthX / 2), 500 + (widthY / 2), 255, 255, 255, 255, 255, 255);
	targetWindow.prepareLine(500 - (widthX / 2), 500 - (widthY / 2), 500 - (widthX / 2), 500 + (widthY / 2), 255, 255, 255, 255, 255, 255);
	targetWindow.prepareLine(500 + (widthX / 2), 500 - (widthY / 2), 500 + (widthX / 2), 500 + (widthY / 2), 255, 255, 255, 255, 255, 255);
	targetWindow.sendLines();
	targetWindow.swapBuffers();

	//wait for window close signal
	while (!targetWindow.windowShouldClose()) {}
}

void Task3(int windowWidthX, int windowWidthY, int squareSizeMax, int squareSizeMin, int changeStep)
{
	//generate window with correct dimensions
	ViewPortGL targetWindow = ViewPortGL("Task3", windowWidthX, windowWidthY);
	//current size values for target and actual size
	int currentSize = squareSizeMin;
	int targetSize = squareSizeMax;
	//set sign for changestep
	changeStep = std::abs(changeStep);
	if (currentSize > targetSize)
		changeStep *= -1;
	//wait for window close signal
	while (!targetWindow.windowShouldClose())
	{
		targetWindow.clearViewPort();
		//suggestion: clamp this value to squareSizeMin/Max, to prevent over/undershooting while scaling
		currentSize = currentSize + changeStep;
		//check whether to flip grow direction next iteration
		if (currentSize <= squareSizeMin || currentSize >= squareSizeMax)
			changeStep *= -1;
		//color values taken from assignment pdf using gimp color picker
		targetWindow.prepareBlock((windowWidthX / 2) - (currentSize / 2), (windowWidthY / 2) - (currentSize / 2), currentSize, currentSize, 255, 0, 255);
		targetWindow.sendTriangles();
		targetWindow.swapBuffers();
	}
}

int main() {
	//test();
	//Task2(1000, 1000, 400, 400);
	//Task2(1000, 1000, 750, 750);
	//Task3(1000, 1000, 1000, 0, 5);
	//Task3(1000, 1000, 750, 250, 10);
	return 0;
}




