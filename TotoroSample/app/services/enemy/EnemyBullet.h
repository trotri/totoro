#pragma once

#include "..\..\..\totoro\service\Activity.h"
#include "../Cfg.h"

class EnemyWarcraft;

/**
 * EnemyBullet class file
 * µÐ»ú×Óµ¯Àà
 *
 * @author ËÎ»¶ <trotri@yeah.net>
 * @version $Id: EnemyBullet.h 1 2015-04-06 19:22:06Z huan.song $
 * @since 1.0
 */
class EnemyBullet : public totoro::Activity
{
public:
	static CONST TCHAR * TAG;

private:
	EnemyWarcraft * mWarcraft;
	BOOL mIsUsing;

protected:
	EnemyBullet();

public:
	~EnemyBullet();

public:
	static EnemyBullet * Create(EnemyWarcraft * warcraft, totoro::String path);

protected:
	BOOL _Initialize(EnemyWarcraft * warcraft, totoro::String path);

public:
	BOOL Update();
	BOOL IsUsing() CONST;
	BOOL SetUsing(BOOL isUsing);
};
