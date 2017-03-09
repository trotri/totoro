#pragma once

#include "..\..\..\totoro\service\Activity.h"
#include "..\..\..\totoro\audio\AudioRegistry.h"

class PlayerWarcraft;

/**
 * PlayerBullet class file
 * Íæ¼Ò×Óµ¯Àà
 *
 * @author ËÎ»¶ <trotri@yeah.net>
 * @version $Id: PlayerBullet.h 1 2015-04-06 19:22:06Z huan.song $
 * @since 1.0
 */
class PlayerBullet : public totoro::Activity
{
public:
	static CONST TCHAR * TAG;

private:
	PlayerWarcraft * mWarcraft;
	totoro::String mShootAudio;
	BOOL mIsUsing;

protected:
	PlayerBullet();

public:
	~PlayerBullet();

public:
	static PlayerBullet * Create(PlayerWarcraft * warcraft, totoro::String path);

protected:
	BOOL _Initialize(PlayerWarcraft * warcraft, totoro::String path);

public:
	BOOL Update();
	BOOL PlayShootAudio() CONST;
	totoro::String GetShootAudio() CONST;
	BOOL SetShootAudio(totoro::String shootAudio);
	BOOL IsUsing() CONST;
	BOOL SetUsing(BOOL isUsing);
};
