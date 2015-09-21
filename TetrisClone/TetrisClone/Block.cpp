#include "Block.h"
#include <SDL.h>
#include "LTexture.h"
#include "GameState.h"


Block::Block(int blockNum, colors color)
{
	//Set the square number of the Block
	squareNum = blockNum;

	//Set the color of the Block
	bColor = color;
}

//Initialize the Block sprite sheet texture
LTexture* bTexture = new LTexture();

//Initialize the color clips Rect array
SDL_Rect* colorClips = new SDL_Rect[NUM_OF_COLORS];


Block::~Block()
{
	playSquares[squareNum].rectFilled = false;
	playSquares[squareNum].containedBlock = NULL;
}


void Block::setSquareNum(int blockNum)
{
	squareNum = blockNum;
}


void Block::changeColorToWhite()
{
	bColor = WHITE;
}


void assignColorClips()
{
	//For every color clip Rect
	for (int i = 0; i < NUM_OF_COLORS; i++) {
		//Set the Rect's position and dimensions
		colorClips[i].w = BLOCK_WIDTH;
		colorClips[i].h = BLOCK_HEIGHT;
		colorClips[i].x = i * BLOCK_WIDTH;
		colorClips[i].y = 0;
	}
}


int Block::getSquareNum()
{
	return squareNum;
}


void Block::moveBlock(direction dir)
{
	//For moving to the right
	if (dir == RIGHT) {
		int oldNum = getSquareNum();
		setSquareNum(oldNum + 1);
	}

	//For moving to the left
	if (dir == LEFT) {
		int oldNum = getSquareNum();
		setSquareNum(oldNum - 1);
	}

	//For moving to down
	if (dir == DOWN) {
		int oldNum = getSquareNum();
		setSquareNum(oldNum + 10);
	}
}


colors Block::getBlockColor()
{
	return bColor;
}


bool Block::checkBelowBlock()
{
	//Check to see if the square below the Block is occupied or out-of-bounds
	if (playSquares[squareNum + 10].rectFilled || squareNum + 10 >= 200) {
		return false;
	}

	//Allow the Block to move if no conflicts were found
	return true;
}
