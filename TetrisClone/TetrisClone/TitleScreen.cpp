#include "GameState.h"

#include <string>

TitleScreen::TitleScreen()
{
	iBackground = new LTexture();
	scrollingCounter = 0;
	scrollingTimer.start();
	jBlocksTexture = new LTexture();
	lambdaTexture = new LTexture();
	singlePlayerButton.buttonTexture = new LTexture();
	multiPlayerButton.buttonTexture = new LTexture();

	iBackground->loadFromFile("TitleScreen/Images/TitleBackground.png");
	jBlocksTexture->loadFromFile("TitleScreen/Images/JBlocksTitle.png");
	lambdaTexture->loadFromFile("TitleScreen/Images/LambdaSymbol.png");

	singlePlayerButton.buttonTexture->loadFromFile("TitleScreen/Images/MouseNotOverSingleButton.png");
	singlePlayerButton.buttonState = STATE_NOTOVER;
	singlePlayerButton.x = SCREEN_WIDTH * (1.5 / 4) - singlePlayerButton.buttonTexture->getWidth();
	singlePlayerButton.y = SCREEN_HEIGHT * (3.0 / 4) - singlePlayerButton.buttonTexture->getHeight();
	
	multiPlayerButton.buttonTexture->loadFromFile("TitleScreen/Images/MouseNotOverMultiButton.png");
	multiPlayerButton.buttonState = STATE_NOTOVER;
	multiPlayerButton.x = SCREEN_WIDTH * (3.0 / 4) - multiPlayerButton.buttonTexture->getWidth();
	multiPlayerButton.y = SCREEN_HEIGHT * (3.0 / 4) - multiPlayerButton.buttonTexture->getHeight();
}


TitleScreen::~TitleScreen()
{
	delete iBackground;
	delete jBlocksTexture;
	delete lambdaTexture;
	delete singlePlayerButton.buttonTexture;
	delete multiPlayerButton.buttonTexture;
}


void TitleScreen::handle_events()
{
	//While there is events to handle
	while (SDL_PollEvent(&event)) {
		//If the user has Xed out the window
		if (event.type == SDL_QUIT) {
			set_next_state(STATE_EXIT);
		}

		//If mouse event happened
		if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
			//Get mouse position
			int x, y;
			SDL_GetMouseState(&x, &y);

			//If the mouse is in the single player button
			if (x > singlePlayerButton.x && x < singlePlayerButton.x + singlePlayerButton.buttonTexture->getWidth() && 
				y > singlePlayerButton.y && y < singlePlayerButton.y + singlePlayerButton.buttonTexture->getHeight()) {
				
				//Act according to the event type
				switch (event.type) {
				case SDL_MOUSEMOTION:
					//If this isn't the current texture being displayed
					if (singlePlayerButton.buttonState != STATE_OVER) {
						singlePlayerButton.buttonTexture->loadFromFile("TitleScreen/Images/MouseOverSingleButton.png");
						singlePlayerButton.buttonState = STATE_OVER;
					}					
					break;

				case SDL_MOUSEBUTTONDOWN:
					//Start a single player game
					set_next_state(STATE_INGAME);
					break;

				case SDL_MOUSEBUTTONUP:
					//If this isn't the current texture being displayed
					if (singlePlayerButton.buttonState != STATE_OVER) {
						singlePlayerButton.buttonTexture->loadFromFile("TitleScreen/Images/MouseOverSingleButton.png");
						singlePlayerButton.buttonState = STATE_OVER;
					}
					break;
				}
			}
			//If the mouse isn't over the button
			else {
				//If this isn't the current texture being displayed
				if (singlePlayerButton.buttonState != STATE_NOTOVER) {
					singlePlayerButton.buttonTexture->loadFromFile("TitleScreen/Images/MouseNotOverSingleButton.png");
					singlePlayerButton.buttonState = STATE_NOTOVER;
				}
			}

			
			//If the mouse is in the multi player button
			if (x > multiPlayerButton.x && x < multiPlayerButton.x + multiPlayerButton.buttonTexture->getWidth() &&
				y > multiPlayerButton.y && y < multiPlayerButton.y + multiPlayerButton.buttonTexture->getHeight()) {

				//Act according to the event type
				switch (event.type) {
				case SDL_MOUSEMOTION:
					//If this isn't the current texture being displayed
					if (multiPlayerButton.buttonState != STATE_OVER) {
						multiPlayerButton.buttonTexture->loadFromFile("TitleScreen/Images/MouseOverMultiButton.png");
						multiPlayerButton.buttonState = STATE_OVER;
					}
					break;

				case SDL_MOUSEBUTTONDOWN:
					//MUST ADD MULTIPLAYER HERE
					break;

				case SDL_MOUSEBUTTONUP:
					//If this isn't the current texture being displayed
					if (multiPlayerButton.buttonState != STATE_OVER) {
						multiPlayerButton.buttonTexture->loadFromFile("TitleScreen/Images/MouseOverMultiButton.png");
						multiPlayerButton.buttonState = STATE_OVER;
					}
					break;
				}
			}
			//If the mouse isn't over the button
			else {
				//If this isn't the current texture being displayed
				if (multiPlayerButton.buttonState != STATE_NOTOVER) {
					multiPlayerButton.buttonTexture->loadFromFile("TitleScreen/Images/MouseNotOverMultiButton.png");
					multiPlayerButton.buttonState = STATE_NOTOVER;
				}
			}
		}
	}
}


void TitleScreen::logic()
{
	//Adjust the scrolling counter
	if (scrollingTimer.getTicks() / 1000.f > .01) {
		scrollingCounter++;
		//Reset the timer
		scrollingTimer.start();

		//If the backgrounds have made it to the top of the screen
		if (scrollingCounter > SCREEN_HEIGHT) {
			//Reset the scrolling counter
			scrollingCounter = 0;
		}
	}
}


void TitleScreen::render()
{
	//Clear screen
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(gRenderer);

	//Show the scrolling background
	iBackground->render(0, SCREEN_HEIGHT - scrollingCounter);
	iBackground->render(0, -scrollingCounter);

	//Show the lambda symbol
	lambdaTexture->render(SCREEN_WIDTH - 20 - lambdaTexture->getWidth(), 20);

	//Show the message
	jBlocksTexture->render(SCREEN_WIDTH / 3.0 - jBlocksTexture->getWidth() / 2, SCREEN_HEIGHT / 3.0 - jBlocksTexture->getHeight() / 2);

	//Show the buttons
	singlePlayerButton.buttonTexture->render(singlePlayerButton.x, singlePlayerButton.y);
	//multiPlayerButton.buttonTexture->render(multiPlayerButton.x, multiPlayerButton.y);

	//Render to the screen
	SDL_RenderPresent(gRenderer);
}
