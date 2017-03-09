#include "BattleScene.h"

BattleScene::BattleScene()
{
	ScheduleUpdate();
	SetName(TEXT("BattleScene"));
}

BattleScene::~BattleScene()
{
}

BattleScene * BattleScene::Create()
{
	BattleScene * result = new BattleScene;
	if (result && result->_Initialize())
	{
		return result;
	}

	DELETE_PTR(result);
	return NULL;
}

BOOL BattleScene::_Initialize()
{
	Map * map = Map::Create();
	AddChild(map);

	PlayerWarcraft * playerWarcraft = PlayerWarcraft::Create();
	AddChild(playerWarcraft);

	Enemies * enemies = Enemies::Create(TEXT("res\\layout\\level_1\\enemies.ini"), playerWarcraft);
	AddChild(enemies);

	ScoreBoard * scoreBoard = ScoreBoard::GetInstance();
	scoreBoard->SetScore(0);
	AddChild(scoreBoard);

	return TRUE;
}

BOOL BattleScene::Update()
{
	if (GetAsyncKeyState(Cfg::KEY_ESCAPE))
	{
		CutScene(TEXT("MainScene"));
	}

	return TRUE;
}
