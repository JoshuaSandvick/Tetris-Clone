#pragma once
#include "BlockStructure.h"
#include "GameState.h"


class GreenStructure : public BlockStructure
{
public:
	GreenStructure();

	//Handles up events for Red Blocks
	void handle_up();
};

