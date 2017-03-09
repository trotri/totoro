#include "MainScene.h"
#include "..\..\Director.h"

using namespace totoro;

CONST TCHAR * MainScene::TAG = TEXT("MainScene");

MainScene::MainScene()
{
	SetName(TEXT("MainScene"));
}

MainScene::~MainScene()
{
}

MainScene * MainScene::Create()
{
	MainScene * result = new MainScene;
	if (result && result->_Initialize())
	{
		return result;
	}

	DELETE_PTR(result);
	return NULL;
}

BOOL MainScene::_Initialize()
{
	Map * map = Map::Create();
	AddChild(map);

	Basic * title = Basic::Create(TEXT("res\\layout\\title.ini"));
	title->SetTextW(L"Air War");
	AddChild(title);

	ImageButton * menuStart = ImageButton::Create(TEXT("res\\layout\\menu_start.ini"));
	menuStart->SetOnClickProc(MenuStartProc);
	AddChild(menuStart);

	ImageButton * menuSetting = ImageButton::Create(TEXT("res\\layout\\menu_setting.ini"));
	menuSetting->SetOnClickProc(MenuSettingProc);
	AddChild(menuSetting);

	ImageButton * menuEscape = ImageButton::Create(TEXT("res\\layout\\menu_escape.ini"));
	menuEscape->SetOnClickProc(MenuEscapeProc);
	AddChild(menuEscape);

	SettingDialog * settingDialog = SettingDialog::Create();
	AddChild(settingDialog);

	menuSetting->SetMessage(settingDialog);

	return TRUE;
}

LRESULT CALLBACK MenuStartProc(VOID * message)
{
	Director::GetInstance()->CutScene(TEXT("BattleScene"));
	return 0;
}

LRESULT CALLBACK MenuSettingProc(VOID * message)
{
	SettingDialog * settingDialog = (SettingDialog *)message;
	settingDialog->Show();
	return 0;
}

LRESULT CALLBACK MenuEscapeProc(VOID * message)
{
	Window::GetInstance()->PostCloseMessage();
	return 0;
}
