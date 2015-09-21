#pragma once
#include "BlockStructure.h"
#include "GameState.h"


class RedStructure : public BlockStructure
{
public:
	RedStructure();

	//Handles up events for Red Blocks
	void handle_up();
};

