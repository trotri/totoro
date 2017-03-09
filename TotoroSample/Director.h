#pragma once

#include "app\scenes\MainScene.h"
#include "app\scenes\BattleScene.h"

#define WINDOW_WIDTH 432
#define WINDOW_HEIGHT 768
#define WINDOW_X 590
#define WINDOW_Y 20
#define WINDOW_TITLE TEXT("TotoroSample")

LRESULT CALLBACK DrawProc();

class Director : public totoro::ISingleton<Director>
{
private:
	totoro::Window * mWindow;
	totoro::Scene * mScene;
	BOOL mIsCutScene;
	totoro::String mSceneName;

public:
	Director();
	virtual ~Director();

protected:
	BOOL _InitWindow();
	BOOL _Initialize();
	BOOL _Exit();

public:
	MSG Run();
	BOOL Draw();
	totoro::Scene * GetScene();
	BOOL CutScene(totoro::String sceneName);
};
