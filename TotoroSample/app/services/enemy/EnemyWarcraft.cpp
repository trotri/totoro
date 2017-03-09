#include "EnemyWarcraft.h"

using namespace totoro;
using namespace std;

CONST TCHAR * EnemyWarcraft::TAG = TEXT("EnemyWarcraft");

EnemyWarcraft::EnemyWarcraft() : mTexture(NULL), mTextureDestroy(NULL), mIsUsing(FALSE), mMuzzleOffset(0), mBulletNum(0), mBulletDelay(0), mBulletCurrDelay(0), mBulletSpeed(0), mDestroyCurrDelay(0)
{
	ScheduleUpdate();
	ScheduleDraw();
}

EnemyWarcraft::~EnemyWarcraft()
{
}

EnemyWarcraft * EnemyWarcraft::Create(String fileName)
{
	EnemyWarcraft * result = new EnemyWarcraft;
	if (result && result->_Initialize(fileName))
	{
		return result;
	}

	DELETE_PTR(result);
	return NULL;
}

BOOL EnemyWarcraft::_Initialize(String fileName)
{
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

	if (mDestroyImg.IsEmpty())
	{
		Log::e(TAG, TEXT("_Initialize '%s' Destroy Img Is Empty!\n"), fileName.c_str());
		return FALSE;
	}

	if (mDestroyAudio.IsEmpty())
	{
		Log::e(TEXT("_Initialize '%s' Destroy Audio Is Empty!\n"), fileName.c_str());
		return FALSE;
	}

	AudioRegistry::LoadOnce(mDestroyAudio);
	_InitBullets();

	MvVectorHelper * mvVectorHelper = MvVectorHelper::Create(fileName);
	mvVectorHelper->SetNeedBackward(FALSE);
	SetMvVectorHelper(mvVectorHelper);

	SetMoveType(MOVE_TYPE::MT_VECTORS);
	return TRUE;
}

BOOL EnemyWarcraft::_InitBullets()
{
	for (UINT i = 0; i < mBulletNum; i++)
	{
		EnemyBullet * bullet = EnemyBullet::Create(this, mBulletImg);
		bullet->SetSpeed(mBulletSpeed);

		AddChild(bullet);
		mBullets.push_back(bullet);
	}

	return TRUE;
}

BOOL EnemyWarcraft::Update()
{
	if (IsDestroyed())
	{
		mDestroyCurrDelay += GetRefreshInterval();
		if (mDestroyCurrDelay > Cfg::DESTROY_DELAY)
		{
			SetUsing(FALSE);
		}

		return TRUE;
	}

	Activity::Update();

	if (!IsUsing())
	{
		return TRUE;
	}

	mBulletCurrDelay += GetRefreshInterval();
	if (mBulletCurrDelay < mBulletDelay)
	{
		return TRUE;
	}

	mBulletCurrDelay = 0;
	EnemyBullet * bullet;
	for (list<EnemyBullet *>::iterator it = mBullets.begin(); it != mBullets.end(); it++)
	{
		bullet = (*it);
		if (bullet->IsUsing())
		{
			continue;
		}

		bullet->SetPos(GetMuzzle());
		bullet->SetUsing(TRUE);
		break;
	}

	return TRUE;
}

BOOL EnemyWarcraft::Destroy()
{
	mSprite->SetTexture(mTextureDestroy);
	AudioRegistry::PlayOnce(mDestroyAudio, TRUE);
	mDestroyCurrDelay = 0;
	return TRUE;
}

BOOL EnemyWarcraft::Reset()
{
	mSprite->SetTexture(mTexture);
	
	MvVectorHelper * mvVectorHelper = GetMvVectorHelper();
	mvVectorHelper->Reset();
	SetMvVectorHelper(mvVectorHelper);

	ScheduleUpdate();
	ScheduleDraw();
	return TRUE;
}

BOOL EnemyWarcraft::IsDestroyed() CONST
{
	return (mSprite->GetTexture() == mTextureDestroy) ? TRUE : FALSE;
}

BOOL EnemyWarcraft::IsUsing() CONST
{
	if (IsDestroyed())
	{
		return FALSE;
	}

	return mIsUsing;
}

BOOL EnemyWarcraft::SetUsing(BOOL isUsing)
{
	mIsUsing = isUsing;
	if (mIsUsing)
	{
		ScheduleDraw();
	}
	else
	{
		SetPosY(-1000);
		UnScheduleDraw();
	}

	return TRUE;
}

CONST POSITION * EnemyWarcraft::GetMuzzle()
{
	CONST RECT4P * box = GetBox();
	mMuzzle.x = box->leftTop.x + GetWidth() / 2 + mMuzzleOffset;
	mMuzzle.y = box->leftTop.y;
	return &mMuzzle;
}

BOOL EnemyWarcraft::SetParams(map<String, String> params)
{
	if (!Activity::SetParams(params))
	{
		return FALSE;
	}

	String sBulletNum = params[TEXT("bullet_num")], sBulletDelay = params[TEXT("bullet_delay")];
	String sBulletImg = params[TEXT("bullet_img")], sBulletSpeed = params[TEXT("bullet_speed")];
	String sMuzzleOffset = params[TEXT("muzzle_offset")];
	String sDestroyImg = params[TEXT("destroy_img")], sDestroyAudio = params[TEXT("destroy_audio")];
	
	sBulletImg.Trim();
	sDestroyImg.Trim();
	sDestroyAudio.Trim();

	if (!sBulletNum.IsEmpty())    mBulletNum = sBulletNum.ToUInt();
	if (!sBulletDelay.IsEmpty())  mBulletDelay = sBulletDelay.ToFloat();
	if (!sBulletImg.IsEmpty())    mBulletImg = sBulletImg;
	if (!sBulletSpeed.IsEmpty())  mBulletSpeed = sBulletSpeed.ToUInt();
	if (!sMuzzleOffset.IsEmpty()) mMuzzleOffset = sMuzzleOffset.ToInt();
	if (!sDestroyImg.IsEmpty())   mDestroyImg = sDestroyImg;
	if (!sDestroyAudio.IsEmpty()) mDestroyAudio = sDestroyAudio;

	return TRUE;
}
