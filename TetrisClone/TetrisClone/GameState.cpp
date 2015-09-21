#include "GameState.h"
#include "SDL_ttf.h"
#include "SDL.h"
#include <iostream>


GameState::GameState()
{}


GameState::~GameState()
{}


void set_next_state(int newState)
{
	//If the user doesn't want to exit
	if (nextState != STATE_EXIT) {
		//Set the next state
		nextState = newState;
	}
}


void change_state()
{
	//If the state needs to be changed
	if (nextState != STATE_NULL)
	{
		//Delete the current state
		if (nextState != STATE_EXIT) {
			delete currentState;
		}
		//Change the state
		switch (nextState)
		{
		case STATE_TITLE:			
			//Destroy and recreate window and renderer
			SDL_DestroyWindow(gWindow);
			gWindow = SDL_CreateWindow("JBlocks", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
			if (gWindow == NULL) {
				std::cout << "SDL encountered an error! Error: " << SDL_GetError() << "\n";
			}

			SDL_DestroyRenderer(gRenderer);
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL) {
				std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
			}

			//Start the new gamestate
			currentState = new TitleScreen();

			break;

		case STATE_INGAME:
			//Destroy and recreate window and renderer
			SDL_DestroyWindow(gWindow);
			gWindow = SDL_CreateWindow("JBlocks", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 480, 640, SDL_WINDOW_SHOWN);
			if (gWindow == NULL) {
				std::cout << "SDL encountered an error! Error: " << SDL_GetError() << "\n";
			}

			SDL_DestroyRenderer(gRenderer);
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL) {
				std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
			}

			//Recreate the Block Texture
			bTexture->loadFromFile("InGame/Images/BlockSheet.png");

			//Start the new gamestate
			currentState = new InGame();

			break;

		case STATE_GAMEOVER:
			//Destroy and recreate window and renderer
			SDL_DestroyWindow(gWindow);
			gWindow = SDL_CreateWindow("JBlocks", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
			if (gWindow == NULL) {
				std::cout << "SDL encountered an error! Error: " << SDL_GetError() << "\n";
			}

			SDL_DestroyRenderer(gRenderer);
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL) {
				std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
			}

			//Start the new gamestate
			currentState = new GameOver();

			break;
		}

		//Change the current state ID
		stateID = nextState;

		//NULL the next state ID
		nextState = STATE_NULL;
	}
}

void fillPlaySquares()
{
	//Set up the positions and dimensions of the play Rects
	for (int i = 0; i < 200; i++) {
		playSquares[i].containingRect.w = BLOCK_WIDTH;
		playSquares[i].containingRect.h = BLOCK_HEIGHT;
		playSquares[i].containingRect.x = 480 / 2 - BLOCK_WIDTH * 5 + BLOCK_WIDTH * (i % 10);
		playSquares[i].containingRect.y = 640 / 2 - BLOCK_HEIGHT * 9 + BLOCK_HEIGHT * (i / 10);
	}
}

/* Initialize all of the external variables */

//State variables
int stateID = STATE_NULL;
int nextState = STATE_NULL;

//Game state object
GameState* currentState = NULL;

//Event variable
SDL_Event event;

//Window variable
SDL_Window* gWindow;

//Font to use
TTF_Font* gFont;

//Renderer
SDL_Renderer* gRenderer;

//Rects that the game is played in
GameSquare playSquares[200];

//The factor that affects how fast the Blocks will drop
float dropFactor = .14;

//The game score
int gameScore;
