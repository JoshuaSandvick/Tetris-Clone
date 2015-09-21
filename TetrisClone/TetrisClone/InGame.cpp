#include "GameState.h"
#include <vector>
#include "BlockStructure.h"
#include <time.h>
#include <string>


InGame::InGame()
{
	//Initialize the background and score textures
	scoreTexture = new LTexture();
	gBackground = new LTexture();

	//Load the Background images
	gBackground->loadFromFile("SinglePlayer/Images/GameBackground.png");


	//Load the sound files
	collisionSound = new SoundHandler(false, "InGame/Sounds/CollisionSound.wav");
	musicPlayer = new SoundHandler(true, "InGame/Sounds/JBlocksMusic.mp3");


	//Create the first BlockStructure
	createNewGamePiece();

	//Start the drop timer
	dropTimer.start();

	//Start the music
	musicPlayer->playMusic();

	//Set the game score to 0
	gameScore = 0;
}


InGame::~InGame()
{
	delete activeGamePiece;
	delete collisionSound;
	delete musicPlayer;
	delete gBackground;
	delete scoreTexture;

	//Clear the gamesquares if they are filled
	for (int i = 0; i < 200; i++) {
		if (playSquares[i].rectFilled) {
			delete playSquares[i].containedBlock;
		}
	}

	//Reset the drop factor
	dropFactor = .14;
}


void InGame::handle_events()
{
	//While there's events to handle
	while (SDL_PollEvent(&event)) {
		//Handle events for the player block
		activeGamePiece->handle_events();

		//If the user has Xed out the window
		if (event.type == SDL_QUIT) {
			//Quit the program
			set_next_state(STATE_EXIT);
		}
	}
}


void InGame::logic()
{
	//If it's been 3 seconds (or .5 seconds with the down key pressed) since the last drop
	if (dropTimer.getTicks() / 1000.f > dropFactor) {
		//If the spots below the active game piece are open
		if (activeGamePiece->checkForOpenSpace(DOWN)) {
			//Move the game piece
			activeGamePiece->move_structure(DOWN);
		}
		//If the spots below the active game piece are occupied (MOST IMPORTANT LOGIC SECTION)
		else {
			//Array of freshly-filled gamesquares
			std::vector <int> justFilledSquares;

			//Indicate that new spaces are occupied
			while ( !(activeGamePiece->getBVector()->empty()) ) {
				//The current Block that is being processed
				Block* currentBlock = activeGamePiece->getBVector()->back();
				
				//Remove the last element from the active game piece vector
				activeGamePiece->getBVector()->pop_back();

				//The gamesquare number of the current Block
				int currentNum = currentBlock->getSquareNum();
				justFilledSquares.push_back(currentNum);

				//Indicate that the gamesquare is filled
				playSquares[currentNum].rectFilled = true; 

				//Store a pointer to the current Block in the gamesquare
				playSquares[currentNum].containedBlock = currentBlock;
			}	

			//Delete any needed rows and update the score
			handle_score_increase(destroyRows(justFilledSquares));		

			//Create a new active game piece
			createNewGamePiece();


			//End the game if Blocks have reached the top
			if (playSquares[3].rectFilled || playSquares[4].rectFilled || playSquares[5].rectFilled) {
				set_next_state(STATE_GAMEOVER);
			}

			//Play the collision sound
			collisionSound->playSound();
		}

		//Reset the drop timer
		dropTimer.start();
	}
}


void InGame::render()
{
	//Clear screen
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);

	//Set the drawing color
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);

	
	//Render the game background
	gBackground->render(0, 0);


	//For the active game piece
	for (int i = 0; i < activeGamePiece->getBVector()->size(); i++) {
		//Get the current Block
		Block* currentBlock = activeGamePiece->getBVector()->at(i);

		//Render the current Block
		bTexture->render(playSquares[currentBlock->getSquareNum()].containingRect.x, playSquares[currentBlock->getSquareNum()].containingRect.y, &colorClips[currentBlock->getBlockColor()]);
	}


	//For all of the gamesquares
	for (int i = 0; i < 200; i++) {
		//If a gamesquare is filled
		if (playSquares[i].rectFilled) {
			//Render the Block in the square
			bTexture->render(playSquares[i].containingRect.x, playSquares[i].containingRect.y, &colorClips[playSquares[i].containedBlock->getBlockColor()]);
		}

		//Render all of the gamesquare rects
		SDL_RenderDrawRect(gRenderer, &(playSquares[i].containingRect));
	}

	//Render the score
	std::string scoreMessage = "Score: " + std::to_string(gameScore);
	scoreTexture->loadFromRenderedText(scoreMessage, gFont, { 0, 0, 0, 255 });
	scoreTexture->render(10, 10);


	//Render to the screen
	SDL_RenderPresent(gRenderer);
}


int InGame::destroyRows(std::vector <int> justFilledSquares)
{
	/* Check each row to see if it should be destroyed */

	//Counts how many rows have been destroyed
	int numOfDestroyedRows = 0;

	//While there are more blocks to test
	while(!justFilledSquares.empty()) {
		bool destroyRow = true;

		//The number of the square being tested
		int testingNum = justFilledSquares.back();
		justFilledSquares.pop_back();

		//Set the testingNum to the beginning of the row
		while (testingNum % 10 > (testingNum - 1) % 10) {
			testingNum--;
		}

		//For each Block in the row
		for (int j = testingNum; j < testingNum + 10; j++) {
			//If a gamesquare is empty
			if (!playSquares[j].rectFilled) {
				//Indicate that the row shouldn't be destroyed
				destroyRow = false;

				//Break out of the loop early
				break;
			}
		}
		//If the row should be destroyed
		if (destroyRow) {
			//For every block in the row
			for (int j = testingNum; j < testingNum + 10; j++) {
				//Render the whole row that is being destroyed as white Blocks and their Rects
				bTexture->render(playSquares[j].containingRect.x, playSquares[j].containingRect.y, &colorClips[WHITE]);
				SDL_RenderDrawRect(gRenderer, &(playSquares[j].containingRect));
				
				//Delete the Block
				delete playSquares[j].containedBlock;
			}

			//Indicate for the score that a row has been destroyed
			numOfDestroyedRows++;


			/* Have any Blocks that fall that need to */

			//For every Block above the row that was destroyed
			for (int k = testingNum - 1; k >= 0; k--) {
				//If the gamesquare is occupied
				if (playSquares[k].rectFilled) {
					Block* fallingBlock = playSquares[k].containedBlock;
					
					//Clear the gamesquare that is being vacated
					playSquares[fallingBlock->getSquareNum()].containedBlock = NULL;
					playSquares[fallingBlock->getSquareNum()].rectFilled = false;

					//Move the Block down and fill the gamesquare
					fallingBlock->moveBlock(DOWN);
					playSquares[fallingBlock->getSquareNum()].containedBlock = fallingBlock;
					playSquares[fallingBlock->getSquareNum()].rectFilled = true;
				}
			}
		}
	}

	//If any rows were destroyed
	if (numOfDestroyedRows) {
		//Render the white blocks to the screen and then delay the program for one second
		SDL_RenderPresent(gRenderer);
		
		LTimer delayTimer;
		delayTimer.start();
		while (delayTimer.getTicks() / 1000.f < 1) {}
	}

	return numOfDestroyedRows;
}


void InGame::createNewGamePiece()
{
	//The int that will determine the block type
	int randomInt = rand() % 4;

	switch (randomInt) 
	{
	case RED:
		activeGamePiece = new RedStructure();
		break;

	case BLUE:
		activeGamePiece = new BlueStructure();
		break;

	case YELLOW:
		activeGamePiece = new YellowStructure();
		break;

	case GREEN:
		activeGamePiece = new GreenStructure();
		break;
	}
}


void InGame::handle_score_increase(int numOfDestroyedRows)
{
	switch (numOfDestroyedRows)
	{
	case 1:
		gameScore += 40;
		break;

	case 2:
		gameScore += 100;
		break;

	case 3:
		gameScore += 300;
		break;

	case 4:
		gameScore += 1200;
		break;
	}
}
