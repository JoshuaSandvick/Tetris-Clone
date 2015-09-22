# Tetris-Clone

JBlocks, a Tetris clone, was created solely by Joshua Sandvick using the SDL2 library in C++. 

The organization of the source code files is as follows:
  -The different states of the game can be found in the files:
    -GameState.cpp/.h
      -GameOver.cpp/.h
      -InGame.cpp/.h
      -TitleScreen.cpp/.h
      
  -The JBlocks game pieces are organized as follows:
    -Block.cpp/.h
    -BlockStructure.cpp/.h
      -GreenStructure.cpp/.h
      -RedStructure.cpp/.h
      -BlueStructure.cpp/.h
      -YellowStructure.cpp/.h
    
  -Self-explanatory source files:
    -LTexture.cpp/.h
    -LTimer.cpp/.h
    -ScoreHandler.cpp/.h
    -SoundHandler.cpp/.h
    
  -The main functionality of the project can be found in source.cpp
  
