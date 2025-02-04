#ifndef _GAMEMANAGE_H_
#define _GAMEMANAGE_H_

#include <vector>
#include <memory>

#include "Game.h"
#include "Session.h"
#include "Player.h"
#include "BaseDice.h"

/*
	This will be responsable of the Game managing. Can be include more games
	carious functions to mainupalte the game.
*/

class GameManage
{
public:
	GameManage();
	~GameManage();
	GameManage operator=(const GameManage& GM);


private:
	std::shared_ptr<Game> game;
};

#endif