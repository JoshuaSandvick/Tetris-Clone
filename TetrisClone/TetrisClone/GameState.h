#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <fstream>
#include "LTexture.h"
#include "SoundHandler.h"
#include "BlockStructure.h"
#include "RedStructure.h"
#include "BlueStructure.h"
#include "YellowStructure.h"
#include "GreenStructure.h"
#include "LTimer.h"


//Game states
enum GameStates
{
	STATE_NULL,
	STATE_TITLE,
	STATE_INGAME,
	STATE_HIGHSCORE,
	STATE_GAMEOVER,
	STATE_EXIT,
};


//Game state base class (virtual so that sub-class overloaded methods can be called)
class GameState
{
public:
	GameState();
	virtual ~GameState();

	//Handles keyboard events
	virtual void handle_events() = 0;

	//Handles the game logic of a state
	virtual void logic() = 0;

	//Renders the images of the state
	virtual void render() = 0;
};

//State status manager
void set_next_state(int newState);

//State changer
void change_state();

//State variables
extern int stateID;
extern int nextState;

//Game state object
extern GameState* currentState;


class InGame : public GameState
{
public:
	//Loads game resources
	InGame();
	//Frees game resources
	~InGame();

	//Main loop functions
	void handle_events();
	void logic();
	void render();

	//Handles deleting rows and allowing blocks to fall
	int destroyRows(std::vector <int> justFilledSquares);

private:
	//Level dimensions
	const static int SCREEN_WIDTH = 480;
	const static int SCREEN_HEIGHT = 640;

	//Game background
	LTexture* gBackground;

	//The score texture
	LTexture* scoreTexture;

	//The handler for collision sound
	SoundHandler* collisionSound;

	//The music player
	SoundHandler* musicPlayer;

	//The Block Structure vector that will contain the active game pieces
	BlockStructure* activeGamePiece;

	//A function that will create a new game piece
	void createNewGamePiece();

	//Handles the score increase
	void handle_score_increase(int numOfDestroyedRows);

	//The timer that determines when the activeGamePiece will drop
	LTimer dropTimer;

	//Number of rows and columns in game area
	const static int GAME_ROWS = 20;
	const static int GAME_COLUMNS = 10;
};

//Rects that the game is played in
extern GameSquare playSquares[200];

//The function that fills playAreaRects
extern void fillPlaySquares();

//The factor that affects how fast the Blocks will drop
extern float dropFactor; 

//The game score
extern int gameScore;


//Represents different mouse button states
enum MouseState
{
	STATE_NOTOVER,
	STATE_OVER,
	STATE_DOWN,
};

//Struct that represents the mouse buttons
struct MouseButton
{
	//The texture that will be on the screen
	LTexture* buttonTexture;

	//The current state of the button
	MouseState buttonState;

	//The positions of the button
	int x, y;
};

class TitleScreen : public GameState
{
public:
	//Loads intro resources
	TitleScreen();
	//Frees intro resources
	~TitleScreen();

	//Main loop functions
	void handle_events();
	void logic();
	void render();

private:
	//Screen dimensions
	const static int SCREEN_WIDTH = 640;
	const static int SCREEN_HEIGHT = 480;

	//Intro background
	LTexture* iBackground;
	//Variables to control the scrolling background
	LTimer scrollingTimer;
	int scrollingCounter;

	//Intro message
	LTexture* jBlocksTexture;

	//Lambda symbol
	LTexture* lambdaTexture;

	//Enter message for single player
	MouseButton singlePlayerButton;

	//Enter message for multiplayer
	MouseButton multiPlayerButton;
};


struct HighScore
{
	//The player name
	std::string playerName;

	//The player score
	int playerScore;
};

class GameOver : public GameState
{
public:
	GameOver();
	~GameOver();

	//Main loop functions
	void handle_events();
	void logic();
	void render();

	//Add the current player to the highscore if required
	void add_to_highscores();

	//Writes over the highscores file
	void overwrite_highscores_file();

private:
	//The screen dimensions
	const static int SCREEN_WIDTH = 640;
	const static int SCREEN_HEIGHT = 480;

	//The background texture
	LTexture* goBackground;

	//The game over message
	LTexture* goMessage;

	//The highscore texture
	LTexture* highscoreTexture;

	//The player score texture
	LTexture* playerScoreTexture;

	//The font to use for some of the textures
	TTF_Font* goFont;

	//The highscore files
	std::fstream highscoreFile;

	//The player's score
	HighScore playerScore;

	//The highscores
	std::vector <HighScore*> highscoreVector;

	//Indicates if the player made it in the highscores
	bool madeItInHighscores = false;
};


//Event variable
extern SDL_Event event;

//Window variable
extern SDL_Window* gWindow;

//Renderer
extern SDL_Renderer* gRenderer;

//Font to use
extern TTF_Font* gFont;
