#pragma once

#include <SDL.h>
#include "LTexture.h"


enum colors {
	RED, 
	BLUE,
	YELLOW,
	GREEN,
	WHITE,
};

enum direction {
	RIGHT,
	LEFT,
	DOWN,
};

const int NUM_OF_COLORS = 5;

class Block
{
public:
	Block(int blockNum, colors color);
	~Block();

	//Set the coordinates of the Block
	void setSquareNum(int blockNum);

	//Change the color of the Block to white
	void changeColorToWhite();

	//Move the Block 
	void moveBlock(direction dir);

	//Get the square number of the block
	int getSquareNum();

	//Get the color of the block
	colors getBlockColor();

	//Check to see if the Block can move down
	bool checkBelowBlock();

private:
	//The square number for the block
	int squareNum;

	//The color for the block
	colors bColor;
};

//The LTexture to use for the blocks
extern LTexture* bTexture;

//The array of Rects to use for cutting out colors
extern SDL_Rect* colorClips;

//The function that will assign the color Rects
extern void assignColorClips();

//Set the width and height of the blocks 
const int BLOCK_WIDTH = 25;
const int BLOCK_HEIGHT = 25;
