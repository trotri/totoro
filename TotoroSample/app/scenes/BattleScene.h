#pragma once

#include "BaseScene.h"
#include "..\services\Map.h"
#include "..\services\player\PlayerWarcraft.h"
#include "..\services\enemy\Enemies.h"
#include "..\services\ScoreBoard.h"

class BattleScene : public BaseScene
{
protected:
	BattleScene();

public:
	~BattleScene();

public:
	static BattleScene * Create();

protected:
	BOOL _Initialize();

public:
	BOOL Update();
};
