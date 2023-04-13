#include "ViewPortGL.h"

class BinaryVisuals
{
public:
	static void PrepareBit(ViewPortGL& targetWindow, int xPos, int yPos, int width, int height, bool isOne);

	static void PrepareRepresentation(ViewPortGL& targetWindow, int xPos, int yPos, int width, int height, unsigned char value);

	static void PrepareRepresentation(ViewPortGL& targetWindow, int xPos, int yPos, int width, int height, unsigned int value);
	
	static unsigned char ExtractCharsFromInt(unsigned int value, int fromIndex, int toIndex);

	static unsigned int ExchangeHalves(unsigned int value, int fromBit, int toBit);
	
	static unsigned int Reverse(unsigned int b);

	static const unsigned int bitBuffer = 10;
	static const unsigned int byteBuffer = 50;
};
