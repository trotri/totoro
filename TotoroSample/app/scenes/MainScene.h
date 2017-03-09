#pragma once

#include "BaseScene.h"
#include "..\..\totoro\service\Basic.h"
#include "..\services\Map.h"
#include "..\..\totoro\form\ImageButton.h"
#include "..\services\SettingDialog.h"

LRESULT CALLBACK MenuStartProc(VOID * message);
LRESULT CALLBACK MenuSettingProc(VOID * message);
LRESULT CALLBACK MenuEscapeProc(VOID * message);

class MainScene : public BaseScene
{
public:
	static CONST TCHAR * TAG;

protected:
	MainScene();

public:
	~MainScene();

public:
	static MainScene * Create();

protected:
	BOOL _Initialize();

};
