#include "PlayerBullet.h"

using namespace totoro;

CONST TCHAR * PlayerBullet::TAG = TEXT("PlayerBullet");

PlayerBullet::PlayerBullet() : mWarcraft(NULL)
{
	SetUsing(FALSE);
}

PlayerBullet::~PlayerBullet()
{
}

PlayerBullet * PlayerBullet::Create(PlayerWarcraft * warcraft, String path)
{
	PlayerBullet * result = new PlayerBullet;
	if (result && result->_Initialize(warcraft, path))
	{
		return result;
	}

	DELETE_PTR(result);
	return NULL;
}

BOOL PlayerBullet::_Initialize(PlayerWarcraft * warcraft, String path)
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

BOOL PlayerBullet::Update()
{
	if (!Activity::Update())
	{
		return FALSE;
	}

	FLOAT y = GetPosY();
	y -= GetRefreshIntervalDistance();
	if (y < 0)
	{
		SetUsing(FALSE);
	}

	SetPosY(y);
	return TRUE;
}

BOOL PlayerBullet::PlayShootAudio() CONST
{
	return AudioRegistry::PlayOnce(mShootAudio, TRUE);
}

String PlayerBullet::GetShootAudio() CONST
{
	return mShootAudio;
}

BOOL PlayerBullet::SetShootAudio(String shootAudio)
{
	if (shootAudio.IsEmpty())
	{
		return FALSE;
	}

	mShootAudio = shootAudio;
	AudioRegistry::LoadOnce(mShootAudio);
	return TRUE;
}

BOOL PlayerBullet::IsUsing() CONST
{
	return mIsUsing;
}

BOOL PlayerBullet::SetUsing(BOOL isUsing)
{
	mIsUsing = isUsing;
	if (mIsUsing)
	{
		PlayShootAudio();
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
