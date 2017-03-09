#pragma once

#include "..\..\..\totoro\audio\AudioRegistry.h"
#include "../Cfg.h"
#include "PlayerBullet.h"

/**
 * PlayerWarcraft class file
 * 玩家战机类
 *
 * @author 宋欢 <trotri@yeah.net>
 * @version $Id: PlayerWarcraft.h 1 2015-04-06 19:22:06Z huan.song $
 * @since 1.0
 */
class PlayerWarcraft : public totoro::Activity
{
public:
	static CONST TCHAR * TAG;

public:
	std::list<PlayerBullet *> mBullets;

private:
	totoro::Texture * mTexture;
	totoro::Texture * mTextureDestroy;
	totoro::POSITION mMuzzleMiddle;
	totoro::POSITION mMuzzleLeft;
	totoro::POSITION mMuzzleRight;
	UINT mMuzzleType;
	INT mMuzzleMiddleOffset;
	INT mMuzzleLeftOffset;
	INT mMuzzleRightOffset;
	UINT mBulletNum;
	FLOAT mBulletDelay;
	FLOAT mBulletCurrDelay;
	totoro::String mBulletImg;
	UINT mBulletSpeed;
	totoro::String mBulletAudio;
	totoro::String mDestroyImg;
	totoro::String mDestroyAudio;
	FLOAT mDestroyCurrDelay;
	
protected:
	PlayerWarcraft();

public:
	~PlayerWarcraft();

public:
	static PlayerWarcraft * Create();

protected:
	BOOL _Initialize();
	BOOL _InitBullets();

public:
	BOOL Update();
	BOOL Destroy();
	BOOL Reset();
	CONST totoro::POSITION * GetMiddleMuzzle();
	CONST totoro::POSITION * GetLeftMuzzle();
	CONST totoro::POSITION * GetRightMuzzle();
	BOOL SetParams(std::map<totoro::String, totoro::String> params);
	BOOL SetPos(FLOAT x, FLOAT y);
};
