#include "Cfg.h"
#include "..\..\Director.h"

using namespace totoro;

CONST TCHAR * Cfg::TAG = TEXT("Cfg");
CONST FLOAT Cfg::DESTROY_DELAY = 0.2f;
CONST UINT Cfg::WIDTH = WINDOW_WIDTH;
CONST UINT Cfg::HEIGHT = WINDOW_HEIGHT;
CONST INT Cfg::KEY_SHOOT = 'J';
CONST INT Cfg::KEY_RESET = 'R';
CONST INT Cfg::KEY_ESCAPE = VK_ESCAPE;
CONST TCHAR * Cfg::PLAYER_INI_DIR_NAME = TEXT("res\\layout\\");
CONST String Cfg::PLAYER_INI_NAME = TEXT("player_1.ini");
CONST String Cfg::PLAYER_DOUBLE_MUZZLE_INI_NAME = TEXT("player_2.ini");

String Cfg::sPlayerIniName = PLAYER_INI_NAME;
BOOL Cfg::sAudioDisabled = FALSE;
BOOL Cfg::sDoubleMuzzle = FALSE;

Cfg::Cfg()
{
}

Cfg::~Cfg()
{
}

String Cfg::GetPlayerIniName()
{
	return sPlayerIniName;
}

BOOL Cfg::SetPlayerIniName(String playerIniName)
{
	if (playerIniName.IsEmpty())
	{
		return FALSE;
	}

	sPlayerIniName = playerIniName;
	return TRUE;
}

BOOL Cfg::IsAudioDisabled()
{
	return sAudioDisabled;
}

VOID Cfg::SetAudioDisabled(BOOL isAudioDisabled)
{
	sAudioDisabled = isAudioDisabled;
	AudioRegistry::SetDisabled(isAudioDisabled);
}

BOOL Cfg::IsDoubleMuzzle()
{
	return sDoubleMuzzle;
}

VOID Cfg::SetDoubleMuzzle(BOOL isDoubleMuzzle)
{
	sDoubleMuzzle = isDoubleMuzzle;
	SetPlayerIniName(sDoubleMuzzle ? PLAYER_DOUBLE_MUZZLE_INI_NAME : PLAYER_INI_NAME);
}
