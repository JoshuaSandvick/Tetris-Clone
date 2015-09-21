#include "BlueStructure.h"
#include "BlockStructure.h"
#include "GameState.h"


BlueStructure::BlueStructure()
{
	//Create new blocks on the game board
	blockVector.push_back(new Block(5, BLUE));
	blockVector.push_back(new Block(6, BLUE));
	blockVector.push_back(new Block(7, BLUE));
	blockVector.push_back(new Block(8, BLUE));
}


void BlueStructure::handle_up()
{
	/* Check to see if the needed space is availabe to flip the structure */

	//If Block is currently flipped
	if (isFlipped) {
		int currentNum = blockVector[0]->getSquareNum();
		//If the gamesquare 3 to the right exists
		if (currentNum % 10 < (currentNum + 3) % 10) {
			//If the correct gamesquares are free
			if (!playSquares[currentNum + 1].rectFilled && !playSquares[currentNum + 2].rectFilled && !playSquares[currentNum + 3].rectFilled) {
				//Change the tile of the 2nd block
				blockVector[1]->setSquareNum(currentNum + 1);

				//Change the tile of the 3rd block
				blockVector[2]->setSquareNum(currentNum + 2);

				//Change the tile of the 4th block
				blockVector[3]->setSquareNum(currentNum + 3);

				//Indicate that the BlockStructure is not flipped
				isFlipped = false;
			}
		}
	}
	//If Block isn't flipped
	else {
		int currentNum = blockVector[1]->getSquareNum();
		//If the gamesquare 3 to the right exists
		if (currentNum - 10 >= 0 && currentNum + 20 < 200) {
			//If the correct gamesquares are free
			if (!playSquares[currentNum - 10].rectFilled && !playSquares[currentNum + 10].rectFilled && !playSquares[currentNum + 20].rectFilled) {
				//Change the tile of the 1st block
				blockVector[0]->setSquareNum(currentNum - 10);

				//Change the tile of the 3rd block
				blockVector[2]->setSquareNum(currentNum + 10);

				//Change the tile of the 4th block
				blockVector[3]->setSquareNum(currentNum + 20);

				//Indicate that the BlockStructure is not flipped
				isFlipped = true;
			}
		}
	}

}
