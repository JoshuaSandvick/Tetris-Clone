#include "GameState.h"
#include <iostream>


GameOver::GameOver()
{
	//Initialize the textures
	goBackground = new LTexture();
	goBackground->loadFromFile("GameOver/Images/Background.png");
	goMessage = new LTexture();
	goMessage->loadFromFile("GameOver/Images/GameOverMessage.png");
	highscoreTexture = new LTexture();
	playerScoreTexture = new LTexture();

	//Initialize the font
	goFont = TTF_OpenFont("Fonts/BRITANIC.ttf", 40);
	if (goFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
	}

	//Set the player score variable
	playerScore.playerName = "";
	playerScore.playerScore = gameScore;

	//Open the highscore file and create if non-existant
	highscoreFile.open("GameOver/Highscores.txt", std::fstream::out || std::fstream::app);
	highscoreFile.close();
	highscoreFile.open("GameOver/Highscores.txt", std::fstream::in);

	/* Read the highscore file */

	std::string currentName, currentScore;
	//If the file isn't empty
	if (highscoreFile.peek() != highscoreFile.eof()) {
		//While the file is not at its end
		while (!highscoreFile.eof()) {
			std::getline(highscoreFile, currentName, ',');

			std::getline(highscoreFile, currentScore, ',');

			//Create the highscore player and add it to the vector of players
			HighScore* playerToAdd = new HighScore();
			playerToAdd->playerName = currentName;
			playerToAdd->playerScore = atoi(currentScore.c_str());

			highscoreVector.push_back(playerToAdd);

			//Move the eof reader forward
			highscoreFile.peek();
		}
	}

	//Change the highscores table
	add_to_highscores();

	//Close the files
	highscoreFile.close();
}


GameOver::~GameOver()
{
	delete goBackground, highscoreTexture, playerScoreTexture;

	//Reset the game score
	gameScore = 0;

	//Close the font
	TTF_CloseFont(goFont);
}


void GameOver::handle_events()
{
	//While there are events to handle
	while (SDL_PollEvent(&event)) {
		//If the user has Xed out the window
		if (event.type == SDL_QUIT) {
			//Quit the program
			set_next_state(STATE_EXIT);
		}

		switch (event.type) {
		case SDL_TEXTINPUT:
			//If the player has written less than 3 initials
			if (playerScore.playerName.size() < 3) {
				//Append the character to the player name
				playerScore.playerName += event.text.text;
			}

			break;

		case SDL_KEYDOWN:
			//If the key hit was enter
			if (event.key.keysym.sym == SDLK_RETURN) {
				//If the player has written any initials
				if (playerScore.playerName.size() > 0 || !madeItInHighscores) {
					//Update the highscores file
					overwrite_highscores_file();

					//Return to the title screen
					set_next_state(STATE_TITLE);
				}

				break;
			}
			//If the key hit was backspace
			else if (event.key.keysym.sym == SDLK_BACKSPACE) {
				//If the player has written any initials
				if (playerScore.playerName.size() > 0) {
					//Get rid of the last character on the name
					std::string playerTempName = playerScore.playerName.substr(0, playerScore.playerName.size() - 1);
					playerScore.playerName = playerTempName;
				}

				break;
			}
		}
	}
}


void GameOver::logic()
{

}


void GameOver::render()
{
	//Clear the screen
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);
	
	//Set the drawing color
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);

	//Render the game over background
	goBackground->render(0, 0);

	//Render the game over message
	goMessage->render(SCREEN_WIDTH / 2 - goMessage->getWidth() / 2, 15);

	//Render the player score
	playerScoreTexture->loadFromRenderedText("Your Score: " + std::to_string(gameScore), goFont, { 255, 0, 0, 255 });
	playerScoreTexture->render(SCREEN_WIDTH / 2 - playerScoreTexture->getWidth() / 2, 70 + playerScoreTexture->getHeight());

	//Render the highscores table
	highscoreTexture->loadFromRenderedText("High Scores", goFont, { 255, 255, 0, 255 });
	highscoreTexture->render(70, 170);
	for (int i = 0; i < highscoreVector.size(); i++) {
		std::string highscoreInfo = std::to_string(i + 1) + ". " + highscoreVector[i]->playerName + "   " + std::to_string(highscoreVector[i]->playerScore);
		highscoreTexture->loadFromRenderedText(highscoreInfo, goFont, { 100, 255, 175, 255 });
		highscoreTexture->render(30, 220 + i * 40);
	}

	//Render to the screen
	SDL_RenderPresent(gRenderer);
}


void GameOver::add_to_highscores()
{
	//If the high score table is not empty
	if (highscoreVector.size() > 0) {
		//Pop the last score off of the table
		HighScore* currentHighScore = highscoreVector.back();
		highscoreVector.pop_back();

		//If the player's high score is better than the current high score
		if (playerScore.playerScore > currentHighScore->playerScore) {
			//Test the next high score in the list
			add_to_highscores();

			//Push the removed high score back onto the table
			highscoreVector.push_back(currentHighScore);

			//Indicate that the player made it into the high scores
			madeItInHighscores = true;
		}
		//Must add score to table somehow
		else{
			//Add the popped high score back onto the table and then the player high score
			highscoreVector.push_back(currentHighScore);
			highscoreVector.push_back(&playerScore);
		}
	}
	//If the high score table is empty
	else {
		//Push the player score onto the table
		highscoreVector.push_back(&playerScore);
	}

	//If table has more than five entries
	if (highscoreVector.size() > 5) {
		//Get rid of the last high score on the table
		highscoreVector.pop_back();
	}
}


void GameOver::overwrite_highscores_file()
{
	//Rewrite the file if necessary
	if (madeItInHighscores) {
		//Open the file and clear it
		highscoreFile.open("GameOver/Highscores.txt", std::ios::out, std::ios::trunc);

		//Write every variable to the file
		for (int i = 0; i < highscoreVector.size(); i++) {
			highscoreFile << highscoreVector[i]->playerName << ',';

			std::string currentPlayerScore = std::to_string( highscoreVector[i]->playerScore );
			highscoreFile << currentPlayerScore + ',';
		}

		//Close the file
		highscoreFile.close();
	}
}
