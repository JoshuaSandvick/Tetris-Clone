#include "BlockStructure.h"
#include <SDL.h>
#include <vector>
#include "Block.h"
#include "GameState.h"


BlockStructure::~BlockStructure()
{
	for (int i = 0; i < blockVector.size(); i++) {
		delete blockVector.at(i);
	}
}


void BlockStructure::handle_events()
{
	switch (event.key.keysym.sym)
	{
	case SDLK_RIGHT:
		//If the structure is able to move and the key hasn't been held down and it's a keydown event
		if (!event.key.repeat && event.type == SDL_KEYDOWN && checkForOpenSpace(RIGHT)){
			move_structure(RIGHT);
		}		
		break;

	case SDLK_LEFT:
		//If the structure is able to move and the key hasn't been held down and it's a keydown event
		if (!event.key.repeat && event.type == SDL_KEYDOWN && checkForOpenSpace(LEFT)){
			move_structure(LEFT);
		}
		break;

	case SDLK_DOWN:
		switch (event.type) {
		//If the user presses the down key
		case SDL_KEYDOWN:
			//If the drop factor is not already lowered
			if (dropFactor > .13) {
				//Lower the drop factor
				dropFactor = .028;
			}
			break;

		//If the user releases the down key
		case SDL_KEYUP:
			//If the drop factor is lowered
			if (dropFactor < .13) {
				//Raise the drop factor
				dropFactor = .14;
			}
		}
		break;

	case SDLK_UP:
		//If the key hasn't been held down and it's a keydown event
		if (!event.key.repeat && event.type == SDL_KEYDOWN) {
			handle_up();
		}
		break;
	}
}

bool BlockStructure::checkForOpenSpace(direction dir)
{
	//If the Blocks want to move right
	if (dir == RIGHT) {
		//For each block, make sure that the space to the right isn't occupied or out-of-bounds
		for (int i = 0; i < blockVector.size(); i++) {
			int currentNum = blockVector[i]->getSquareNum();
			if (currentNum % 10 > (currentNum + 1) % 10 || playSquares[currentNum + 1].rectFilled) {
				return false;
			}
		}

		//Allow the Blocks to move if no conflicts were found
		return true;
	}

	//If the Blocks want to move left
	if (dir == LEFT) {
		//For each block, make sure that the space to the left isn't occupied or out-of-bounds
		for (int i = 0; i < blockVector.size(); i++) {
			int currentNum = blockVector[i]->getSquareNum();
			if (currentNum % 10 < (currentNum - 1) % 10 || playSquares[currentNum - 1].rectFilled) {
				return false;
			}
		}

		//Allow the Blocks to move if no conflicts were found
		return true;
	}

	//If the Blocks want to move down
	if (dir == DOWN) {
		//For each block, make sure that the space to the left isn't occupied or out-of-bounds
		for (int i = 0; i < blockVector.size(); i++) {
			int currentNum = blockVector[i]->getSquareNum();
			//MAY THROW AN ERROR FOR INDEX OUT OF BOUNDS
			if (currentNum + 10 >= 200 || playSquares[currentNum + 10].rectFilled) {
				return false;
			}
		}

		//Allow the Blocks to move if no conflicts were found
		return true;
	}
}


void BlockStructure::move_structure(direction dir)
{
	for (int i = 0; i < blockVector.size(); i++) {
		blockVector[i]->moveBlock(dir);
	}	
}


std::vector <Block*>* BlockStructure::getBVector()
{
	return &blockVector;
}
