#include "..\..\app\services\Map.h"
#include "..\..\Director.h"

using namespace totoro;

CONST TCHAR * Map::TAG = TEXT("Map");
CONST String Map::NAME = TEXT("map");
CONST String Map::PATH = TEXT("res\\drawable\\map_battle.png");
CONST FLOAT Map::MAP_Z_INDEX = 0.8f;
CONST UINT Map::MAP_DEFAULT_SPEED = 40;

Map::Map() : mHeight(0)
{
	ScheduleUpdate();
}

Map::~Map()
{
}

Map * Map::Create()
{
	Map * result = new Map;
	if (result && result->_Initialize())
	{
		return result;
	}

	DELETE_PTR(result);
	return NULL;
}

BOOL Map::_Initialize()
{
	Basic * basic = Basic::CreateImage(NAME, PATH);
	if (basic == NULL)
	{
		return FALSE;
	}

	if (mHeight <= 0)
	{
		mHeight = basic->GetShowHeight();
	}

	FLOAT height = static_cast<FLOAT>(mHeight);
	for (INT i = 0; i < MAP_MAX_SIZE; i++)
	{
		Basic * basic = Basic::CreateImage(NAME, PATH);
		basic->SetZIndex(MAP_Z_INDEX);
		basic->SetSpeed(MAP_DEFAULT_SPEED);
		basic->SetPosY(i * height);

		AddChild(basic);
		mBasics[i] = basic;
	}

	return TRUE;
}

BOOL Map::Update()
{
	FLOAT minY = 0;
	for (INT i = 0; i < MAP_MAX_SIZE; i++)
	{
		FLOAT y = mBasics[i]->GetPosY();
		if (y < minY)
		{
			minY = y;
		}
	}

	for (INT i = 0; i < MAP_MAX_SIZE; i++)
	{
		FLOAT y = mBasics[i]->GetPosY();
		if (y >= Cfg::HEIGHT - 10)
		{
			y = minY - mHeight + 2;
		}

		mBasics[i]->SetPosY(y);
	}

	FLOAT distance = mBasics[0]->GetRefreshIntervalDistance();
	for (INT i = 0; i < MAP_MAX_SIZE; i++)
	{
		FLOAT y = mBasics[i]->GetPosY() + distance;
		mBasics[i]->SetPosY(y);
	}

	return TRUE;
}
