#pragma once

#include "..\..\totoro\ap\ILayer.h"
#include "..\..\totoro\service\Basic.h"
#include "Cfg.h"

#define MAP_MAX_SIZE 4

/**
 * Map class file
 * ±≥æ∞¿‡
 *
 * @author ÀŒª∂ <trotri@yeah.net>
 * @version $Id: Map.h 1 2015-04-06 19:22:06Z huan.song $
 * @since 1.0
 */
class Map : public totoro::ILayer
{
public:
	static CONST TCHAR * TAG;
	static CONST totoro::String NAME;
	static CONST totoro::String PATH;
	static CONST FLOAT MAP_Z_INDEX;
	static CONST UINT MAP_DEFAULT_SPEED;

private:
	totoro::Basic * mBasics[MAP_MAX_SIZE];
	UINT mWndHeight;
	UINT mHeight;

protected:
	Map();

public:
	~Map();

public:
	static Map * Create();

protected:
	BOOL _Initialize();

public:
	BOOL Update();
};
