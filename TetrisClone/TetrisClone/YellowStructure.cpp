#include "YellowStructure.h"
#include "BlockStructure.h"
#include "GameState.h"


YellowStructure::YellowStructure()
{
	//Create new blocks on the game board
	blockVector.push_back(new Block(5, YELLOW));
	blockVector.push_back(new Block(6, YELLOW));
	blockVector.push_back(new Block(15, YELLOW));
	blockVector.push_back(new Block(16, YELLOW));
}


void YellowStructure::handle_up()
{}
