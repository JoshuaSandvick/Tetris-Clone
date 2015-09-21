#pragma once
#include "BlockStructure.h"
#include "GameState.h"


class YellowStructure : public BlockStructure
{
public:
	YellowStructure();

	//Blank because yellow can't rotate
	void handle_up();
};

