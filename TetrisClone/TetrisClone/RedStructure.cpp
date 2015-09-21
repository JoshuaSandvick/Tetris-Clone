#include "RedStructure.h"
#include "BlockStructure.h"
#include "GameState.h"


RedStructure::RedStructure()
{
	//Create new blocks on the game board
	blockVector.push_back(new Block(5, RED));
	blockVector.push_back(new Block(15, RED));
	blockVector.push_back(new Block(14, RED));
	blockVector.push_back(new Block(24, RED));
}


void RedStructure::handle_up()
{
	/* Check to see if the needed space is availabe to flip the structure */
	
	//If Block is currently flipped
	if (isFlipped) {
		int currentNum = blockVector[1]->getSquareNum();
		//If the next square below exists
		if (currentNum + 9 < 200) {
			if (!playSquares[currentNum - 1].rectFilled && !playSquares[currentNum + 9].rectFilled) {
				//Change the tile of the 3rd block
				blockVector[2]->setSquareNum(currentNum - 1);

				//Change the tile of the 4th block
				blockVector[3]->setSquareNum(currentNum + 9);

				//Indicate that the BlockStructure is flipped
				isFlipped = false;
			}
		}
	}
	//If Block isn't flipped
	else {
		int currentNum = blockVector[1]->getSquareNum();
		//If the next square to the right exists
		if (currentNum % 10 < (currentNum + 1) % 10) {
			if (!playSquares[currentNum - 11].rectFilled && !playSquares[currentNum + 1].rectFilled) {
				//Change the tile of the 3rd block
				blockVector[2]->setSquareNum(currentNum - 11);

				//Change the tile of the 4th block
				blockVector[3]->setSquareNum(currentNum + 1);

				//Indicate that the BlockStructure is not flipped
				isFlipped = true;
			}
		}
	}
	
}
