#include "GreenStructure.h"
#include "BlockStructure.h"
#include "GameState.h"


GreenStructure::GreenStructure()
{
	//Create new blocks on the game board
	blockVector.push_back(new Block(4, GREEN));
	blockVector.push_back(new Block(14, GREEN));
	blockVector.push_back(new Block(15, GREEN));
	blockVector.push_back(new Block(25, GREEN));
}


void GreenStructure::handle_up()
{
	/* Check to see if the needed space is availabe to flip the structure */

	//If Block is currently flipped
	if (isFlipped) {
		int currentNum = blockVector[1]->getSquareNum();
		//If the next square below exists
		if (currentNum + 10 < 200) {
			if (!playSquares[currentNum - 10].rectFilled && !playSquares[currentNum + 11].rectFilled) {
				//Change the tile of the 1st block
				blockVector[0]->setSquareNum(currentNum - 10);

				//Change the tile of the 4th block
				blockVector[3]->setSquareNum(currentNum + 11);

				//Indicate that the BlockStructure is flipped
				isFlipped = false;
			}
		}
	}
	//If Block isn't flipped
	else {
		int currentNum = blockVector[1]->getSquareNum();
		//If the next square to the left exists
		if (currentNum % 10 > (currentNum - 1) % 10) {
			if (!playSquares[currentNum + 10].rectFilled && !playSquares[currentNum + 9].rectFilled) {
				//Change the tile of the 1st block
				blockVector[0]->setSquareNum(currentNum + 10);

				//Change the tile of the 4th block
				blockVector[3]->setSquareNum(currentNum + 9);

				//Indicate that the BlockStructure is not flipped
				isFlipped = true;
			}
		}
	}

}
