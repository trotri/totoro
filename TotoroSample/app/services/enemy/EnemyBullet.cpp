#include "EnemyBullet.h"

using namespace totoro;

CONST TCHAR * EnemyBullet::TAG = TEXT("EnemyBullet");

EnemyBullet::EnemyBullet() : mWarcraft(NULL)
{
	SetUsing(FALSE);
}

EnemyBullet::~EnemyBullet()
{
}

EnemyBullet * EnemyBullet::Create(EnemyWarcraft * warcraft, String path)
{
	EnemyBullet * result = new EnemyBullet;
	if (result && result->_Initialize(warcraft, path))
	{
		return result;
	}

	DELETE_PTR(result);
	return NULL;
}

BOOL EnemyBullet::_Initialize(EnemyWarcraft * warcraft, String path)
{
	if (warcraft == NULL)
	{
		return FALSE;
	}

	if (!_InitializeImage(path, path))
	{
		return FALSE;
	}

	mWarcraft = warcraft;
	return TRUE;
}

BOOL EnemyBullet::Update()
{
	if (!Activity::Update())
	{
		return FALSE;
	}

	FLOAT y = GetPosY();
	y += GetRefreshIntervalDistance();
	if (y > Cfg::HEIGHT)
	{
		SetUsing(FALSE);
	}

	SetPosY(y);
	return TRUE;
}

BOOL EnemyBullet::IsUsing() CONST
{
	return mIsUsing;
}

BOOL EnemyBullet::SetUsing(BOOL isUsing)
{
	mIsUsing = isUsing;
	if (mIsUsing)
	{
		ScheduleUpdate();
		ScheduleDraw();
	}
	else
	{
		UnScheduleUpdate();
		UnScheduleDraw();
	}

	return TRUE;
}
