#pragma once
#include <vector>
#include <SDL.h>
#include "Block.h"
#include "SDL.h"


struct GameSquare
{
	//The spot on the gameboard
	SDL_Rect containingRect;

	//Indicates if the gameboard spot is filled
	bool rectFilled = false;

	//The Block on the spot (if it exists) 
	Block* containedBlock = NULL;
};


class BlockStructure
{
public:
	~BlockStructure();

	//Moves the structure
	void move_structure(direction dir);

	//Check for blocks below the blocks that will move (also handles border cases)
	bool checkForOpenSpace(direction dir);

	//Handles keyboard events
	void handle_events();

	//Handles the up keyboard event
	virtual void handle_up() = 0;

	//Returns a pointer to the block vector
	std::vector <Block*>* getBVector();

protected:
	//The vector that will contain the blocks of the structure
	std::vector <Block*> blockVector;

	//Indicates if the Block has been flipped or not
	bool isFlipped = false;
};
