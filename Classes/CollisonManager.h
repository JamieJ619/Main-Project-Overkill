#pragma once
#include "Tile.h"

class Player;

class CollisonManager
{
public:
	static void CheckWalleyJobs(Player * p_player, std::vector<sf::IntRect> * p_tileList);

};

