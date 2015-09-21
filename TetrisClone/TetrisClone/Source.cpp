#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>
#include <sstream>
#include <time.h>
#include "LTexture.h"
#include "LTimer.h"
#include "Block.h"
#include "SoundHandler.h"
#include "GameState.h"
#include <time.h>
using namespace std;


//Function to quit the program
void close();

//Function to initialize SDL video, create a window, and map a screen to that window
bool init();

int main(int argc, char **argv)
{
	//If SDL fails to initialize
	if (!init()) {
		cout << "SDL could not be initialized! \n";
	}
	else {
		//Initialize the font
		gFont = TTF_OpenFont("Fonts/lazy.ttf", 28);
		if (gFont == NULL)
		{
			printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		}

		//Seed the timer
		srand(time(NULL));

		//Set the current state ID
		set_next_state(STATE_TITLE);
		change_state();

		//Set the next state to NULL
		set_next_state(STATE_NULL);

		//Create the gameboard Rects
		fillPlaySquares();

		//Load the Block's sprite sheet
		bTexture->loadFromFile("InGame/Images/BlockSheet.png");

		//Set the dimensions of the color clips for the Block
		assignColorClips();

		//Main loop
		while (stateID != STATE_EXIT) {
			//Do state handling events
			currentState->handle_events();

			//Do state logic
			currentState->logic();

			//Change state if needed
			change_state();

			//Do state rendering
			currentState->render();
		}

		//Close everything
		close();
	}

	return 0;
}

/*
*Function to initialize SDL video, create a window, and map a screen to that window
*
*@returns
*	whether or not SDL initialized successfully
*/
bool init() {
	bool success = true;

	//Initialize SDL Video
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		cout << "SDL_VIDEO could not be initialized! Error: " << SDL_GetError() << "\n";
		success = false;
	}
	else {
		//Initialize PNG loading
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags)) {
			cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
			success = false;
		}

				

#ifdef _SDL_MIXER_H
				//Initialize SDL_mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
					cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
					success = false;
				}
#endif


#ifdef _SDL_TTF_H
				//Initialize SDL_tff
				if (TTF_Init() == -1) {
					cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << endl;
					success = false;
				}
#endif
			}

	return success;
}

/*
*Function to quit the program
*/
void close() {
	//Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Close the font that was used
	TTF_CloseFont(gFont);

	//Delete game state and free state resources
	delete currentState;

	//Close all SDL subsystems
	SDL_Quit();
	IMG_Quit();

#ifdef _SDL_MIXER_H
	Mix_Quit();
#endif

#ifdef _SDL_TTF_H
	TTF_Quit();
#endif
}
