#pragma once
#include "BlockStructure.h"
#include "GameState.h"


class BlueStructure : public BlockStructure
{
public:
	BlueStructure();

	//Handles up events for Red Blocks
	void handle_up();
};
