#pragma once

#include "..\..\..\totoro\audio\AudioRegistry.h"
#include "..\..\..\totoro\service\MvVectorHelper.h"
#include "../Cfg.h"
#include "EnemyBullet.h"

/**
 * EnemyWarcraft class file
 * µÐ»úÀà
 *
 * @author ËÎ»¶ <trotri@yeah.net>
 * @version $Id: EnemyWarcraft.h 1 2015-04-06 19:22:06Z huan.song $
 * @since 1.0
 */
class EnemyWarcraft : public totoro::Activity
{
public:
	static CONST TCHAR * TAG;

public:
	std::list<EnemyBullet *> mBullets;

private:
	totoro::Texture * mTexture;
	totoro::Texture * mTextureDestroy;
	BOOL mIsUsing;
	totoro::POSITION mMuzzle;
	INT mMuzzleOffset;
	UINT mBulletNum;
	FLOAT mBulletDelay;
	FLOAT mBulletCurrDelay;
	totoro::String mBulletImg;
	UINT mBulletSpeed;
	totoro::String mDestroyImg;
	totoro::String mDestroyAudio;
	FLOAT mDestroyCurrDelay;

protected:
	EnemyWarcraft();

public:
	~EnemyWarcraft();

public:
	static EnemyWarcraft * Create(totoro::String fileName);

protected:
	BOOL _Initialize(totoro::String fileName);
	BOOL _InitBullets();

public:
	BOOL Update();
	BOOL Destroy();
	BOOL Reset();
	BOOL IsDestroyed() CONST;
	BOOL IsUsing() CONST;
	BOOL SetUsing(BOOL isUsing);
	CONST totoro::POSITION * GetMuzzle();
	BOOL SetParams(std::map<totoro::String, totoro::String> params);
};
