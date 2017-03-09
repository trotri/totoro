#pragma once

#include "..\..\..\totoro\ap\ILayer.h"
#include "..\player\PlayerWarcraft.h"
#include "EnemyWarcraft.h"
#include "..\ScoreBoard.h"

class Enemies : public totoro::ILayer
{
private:
	std::list<EnemyWarcraft *> mEnemyWarcrafts;
	PlayerWarcraft * mPlayerWarcraft;
	ScoreBoard * mScoreBoard;

protected:
	Enemies();

public:
	~Enemies();

public:
	static Enemies * Create(totoro::String fileName, PlayerWarcraft * playerWarcraft);

protected:
	BOOL _Initialize(totoro::String fileName, PlayerWarcraft * playerWarcraft);

public:
	BOOL Update();
	VOID Hit();
	UINT UpdateUsing();
	BOOL ResetEnemyWarcrafts();
};
