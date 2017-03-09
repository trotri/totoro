#pragma once

#include "..\..\totoro\ap\Defs.h"

/**
 * Cfg class file
 * œÓƒø≈‰÷√¿‡
 *
 * @author ÀŒª∂ <trotri@yeah.net>
 * @version $Id: Cfg.h 1 2015-04-06 19:22:06Z huan.song $
 * @since 1.0
 */
class Cfg
{
public:
	static CONST TCHAR * TAG;
	static CONST FLOAT DESTROY_DELAY;
	static CONST UINT WIDTH;
	static CONST UINT HEIGHT;
	static CONST INT KEY_SHOOT;
	static CONST INT KEY_RESET;
	static CONST INT KEY_ESCAPE;
	static CONST TCHAR * PLAYER_INI_DIR_NAME;
	static CONST totoro::String PLAYER_INI_NAME;
	static CONST totoro::String PLAYER_DOUBLE_MUZZLE_INI_NAME;

private:
	static totoro::String sPlayerIniName;
	static BOOL sAudioDisabled;
	static BOOL sDoubleMuzzle;

public:
	Cfg();

public:
	virtual ~Cfg();

public:
	static totoro::String GetPlayerIniName();
	static BOOL SetPlayerIniName(totoro::String playerIniName);
	static BOOL IsAudioDisabled();
	static VOID SetAudioDisabled(BOOL isAudioDisabled);
	static BOOL IsDoubleMuzzle();
	static VOID SetDoubleMuzzle(BOOL isDoubleMuzzle);
};
