#include "PlayerWarcraft.h"

using namespace totoro;
using namespace std;

CONST TCHAR * PlayerWarcraft::TAG = TEXT("PlayerWarcraft");

PlayerWarcraft::PlayerWarcraft() : mTexture(NULL), mTextureDestroy(NULL), mMuzzleType(0), mMuzzleMiddleOffset(0), mMuzzleLeftOffset(0), mMuzzleRightOffset(0), mBulletNum(0), mBulletDelay(0), mBulletCurrDelay(0), mBulletSpeed(0), mDestroyCurrDelay(0)
{
}

PlayerWarcraft::~PlayerWarcraft()
{
}

PlayerWarcraft * PlayerWarcraft::Create()
{
	PlayerWarcraft * result = new PlayerWarcraft;
	if (result && result->_Initialize())
	{
		return result;
	}

	DELETE_PTR(result);
	return NULL;
}

BOOL PlayerWarcraft::_Initialize()
{
	String fileName = Cfg::PLAYER_INI_DIR_NAME;
	fileName += Cfg::GetPlayerIniName();
	if (!Activity::_Initialize(fileName))
	{
		return FALSE;
	}

	mTextureDestroy = TextureRegistry::AddImage(mDestroyImg, mDestroyImg);
	if (mTextureDestroy == NULL)
	{
		return FALSE;
	}

	mTexture = mSprite->GetTexture();

	if (mMuzzleType <= 0)
	{
		Log::e(TAG, TEXT("_Initialize '%s' Muzzle Type Wrong!\n"), fileName.c_str());
		return FALSE;
	}

	if (mBulletNum <= 0)
	{
		Log::e(TAG, TEXT("_Initialize '%s' Bullet Num Wrong!\n"), fileName.c_str());
		return FALSE;
	}

	if (mBulletDelay <= 0)
	{
		Log::e(TAG, TEXT("_Initialize '%s' Bullet Delay Wrong!\n"), fileName.c_str());
		return FALSE;
	}

	if (mBulletImg.IsEmpty())
	{
		Log::e(TAG, TEXT("_Initialize '%s' Bullet Img Is Empty!\n"), fileName.c_str());
		return FALSE;
	}

	if (mBulletSpeed <= 0)
	{
		Log::e(TAG, TEXT("_Initialize '%s' Bullet Speed Wrong!\n"), fileName.c_str());
		return FALSE;
	}

	if (mBulletAudio.IsEmpty())
	{
		Log::e(TAG, TEXT("_Initialize '%s' Bullet Audio Is Empty!\n"), fileName.c_str());
		return FALSE;
	}

	if (mDestroyImg.IsEmpty())
	{
		Log::e(TAG, TEXT("_Initialize '%s' Destroy Img Is Empty!\n"), fileName.c_str());
		return FALSE;
	}

	if (mDestroyAudio.IsEmpty())
	{
		Log::e(TAG, TEXT("_Initialize '%s' Destroy Audio Is Empty!\n"), fileName.c_str());
		return FALSE;
	}

	AudioRegistry::LoadOnce(mDestroyAudio);
	_InitBullets();

	SetMoveType(MOVE_TYPE::MT_KEYBOARD);
	return TRUE;
}

BOOL PlayerWarcraft::_InitBullets()
{
	for (UINT i = 0; i < mBulletNum; i++)
	{
		PlayerBullet * bullet = PlayerBullet::Create(this, mBulletImg);
		bullet->SetSpeed(mBulletSpeed);
		bullet->SetShootAudio(mBulletAudio);

		AddChild(bullet);
		mBullets.push_back(bullet);
	}

	return TRUE;
}

BOOL PlayerWarcraft::Update()
{
	if (GetAsyncKeyState(Cfg::KEY_RESET))
	{
		Reset();
		return TRUE;
	}

	if (mSprite->GetTexture() == mTextureDestroy)
	{
		mDestroyCurrDelay += GetRefreshInterval();
		if (mDestroyCurrDelay > Cfg::DESTROY_DELAY)
		{
			UnScheduleDraw();
		}

		return TRUE;
	}

	mBulletCurrDelay += GetRefreshInterval();

	if (!Activity::Update())
	{
		return FALSE;
	}

	if (GetAsyncKeyState(Cfg::KEY_SHOOT))
	{
		if (mBulletCurrDelay < mBulletDelay)
		{
			return TRUE;
		}

		mBulletCurrDelay = 0;
		BOOL setUsingBulletCnt = 0;
		PlayerBullet * bullet;
		for (list<PlayerBullet *>::iterator it = mBullets.begin(); it != mBullets.end(); it++)
		{
			bullet = (*it);
			if (bullet->IsUsing())
			{
				continue;
			}

			bullet->SetUsing(TRUE);

			if (mMuzzleType == 2)
			{
				if (setUsingBulletCnt == 0)
				{
					bullet->SetPos(GetLeftMuzzle());
					setUsingBulletCnt++;
					continue;
				}

				if (setUsingBulletCnt == 1)
				{
					bullet->SetPos(GetRightMuzzle());
					break;
				}
			}
			else if (mMuzzleType == 1)
			{
				bullet->SetPos(GetMiddleMuzzle());
				break;
			}
		}
	}

	return TRUE;
}

BOOL PlayerWarcraft::Destroy()
{
	mSprite->SetTexture(mTextureDestroy);
	AudioRegistry::PlayOnce(mDestroyAudio, TRUE);
	mDestroyCurrDelay = 0;
	return TRUE;
}

BOOL PlayerWarcraft::Reset()
{
	mSprite->SetTexture(mTexture);
	Activity::SetPos(GetSrcPos());
	ScheduleUpdate();
	ScheduleDraw();
	return TRUE;
}

CONST POSITION * PlayerWarcraft::GetMiddleMuzzle()
{
	CONST RECT4P * box = GetBox();
	mMuzzleMiddle.x = box->leftTop.x + GetWidth() / 2 + mMuzzleMiddleOffset;
	mMuzzleMiddle.y = box->leftTop.y;
	return &mMuzzleMiddle;
}

CONST POSITION * PlayerWarcraft::GetLeftMuzzle()
{
	CONST RECT4P * box = GetBox();
	mMuzzleLeft.x = box->leftTop.x + mMuzzleLeftOffset;
	mMuzzleLeft.y = box->leftTop.y;
	return &mMuzzleLeft;
}

CONST POSITION * PlayerWarcraft::GetRightMuzzle()
{
	CONST RECT4P * box = GetBox();
	mMuzzleRight.x = box->rightTop.x + mMuzzleRightOffset;
	mMuzzleRight.y = box->leftTop.y;
	return &mMuzzleRight;
}

BOOL PlayerWarcraft::SetParams(map<String, String> params)
{
	if (!Activity::SetParams(params))
	{
		return FALSE;
	}

	String sBulletNum = params[TEXT("bullet_num")], sBulletDelay = params[TEXT("bullet_delay")];
	String sBulletImg = params[TEXT("bullet_img")], sBulletSpeed = params[TEXT("bullet_speed")], sBulletAudio = params[TEXT("bullet_audio")];
	String sDestroyImg = params[TEXT("destroy_img")], sDestroyAudio = params[TEXT("destroy_audio")];
	String sMuzzleType = params[TEXT("muzzle_type")];
	String sMuzzleMiddleOffset = params[TEXT("muzzle_middle_offset")], sMuzzleLeftOffset = params[TEXT("muzzle_left_offset")], sMuzzleRightOffset = params[TEXT("muzzle_right_offset")];

	sBulletImg.Trim();
	sBulletAudio.Trim();
	sDestroyImg.Trim();
	sDestroyAudio.Trim();
	
	if (!sBulletNum.IsEmpty())          mBulletNum = sBulletNum.ToUInt();
	if (!sBulletDelay.IsEmpty())        mBulletDelay = sBulletDelay.ToFloat();
	if (!sBulletImg.IsEmpty())          mBulletImg = sBulletImg;
	if (!sBulletSpeed.IsEmpty())        mBulletSpeed = sBulletSpeed.ToUInt();
	if (!sBulletAudio.IsEmpty())        mBulletAudio = sBulletAudio;
	if (!sDestroyImg.IsEmpty())         mDestroyImg = sDestroyImg;
	if (!sDestroyAudio.IsEmpty())       mDestroyAudio = sDestroyAudio;
	if (!sMuzzleType.IsEmpty())         mMuzzleType = sMuzzleType.ToUInt();
	if (!sMuzzleMiddleOffset.IsEmpty()) mMuzzleMiddleOffset = sMuzzleMiddleOffset.ToInt();
	if (!sMuzzleLeftOffset.IsEmpty())   mMuzzleLeftOffset = sMuzzleLeftOffset.ToInt();
	if (!sMuzzleRightOffset.IsEmpty())  mMuzzleRightOffset = sMuzzleRightOffset.ToInt();

	return TRUE;
}

BOOL PlayerWarcraft::SetPos(FLOAT x, FLOAT y)
{
	if (x < 0 || y < 0)
	{
		return FALSE;
	}

	if (x >(Cfg::WIDTH - GetShowWidth() - 15))
	{
		return FALSE;
	}

	if (y >(Cfg::HEIGHT - GetShowHeight() - Window::GetInstance()->GetCaptionHeight() - 15))
	{
		return FALSE;
	}

	return Activity::SetPos(x, y);
}
