#include "ViewPortGL.h"

class BinaryVisuals
{
	static void PrepareBit(ViewPortGL& targetWindow, int xPos, int yPos, int width, int height, bool isOne);
	
	static void PrepareRepresentation(ViewPortGL& targetWindow, int xPos, int yPos, int width, int height, unsigned char value);
	
	static void PrepareRepresentation(ViewPortGL& targetWindow, int xPos, int yPos, int width, int height, unsigned int value);
	
	unsigned int ExchangeHalves(unsigned int value, int fromBit, int toBit);
	
	unsigned int Reverse(unsigned int b);
};
