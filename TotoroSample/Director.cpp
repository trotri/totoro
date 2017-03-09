#include "Director.h"

using namespace totoro;

Director::Director() : mScene(NULL), mIsCutScene(FALSE)
{
	mWindow = Window::GetInstance();
}

Director::~Director()
{
	DELETE_PTR(mScene);
	DELETE_PTR(mWindow);
}

BOOL Director::_InitWindow()
{
	mWindow->SetDrawProc(DrawProc);
	mWindow->SetTitle(WINDOW_TITLE);
	mWindow->SetWndSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	mWindow->SetWndPos(WINDOW_X, WINDOW_Y);
	return TRUE;
}

BOOL Director::_Initialize()
{
	CutScene(TEXT("MainScene"));
	return TRUE;
}

BOOL Director::_Exit()
{
	return TRUE;
}

MSG Director::Run()
{
	_InitWindow();
	_Initialize();
	MSG msg = mWindow->Run();
	_Exit();
	return msg;
}

BOOL Director::Draw()
{
	Scene * scene = GetScene();
	if (scene != NULL)
	{
		return scene->Visit();
	}

	return FALSE;
}

Scene * Director::GetScene()
{
	if (mIsCutScene)
	{
		mIsCutScene = FALSE;

		DELETE_PTR(mScene);
		if (mSceneName.compare(TEXT("MainScene")) == 0)
		{
			mScene = MainScene::Create();
		}
		else if (mSceneName.compare(TEXT("BattleScene")) == 0)
		{
			mScene = BattleScene::Create();
		}
	}

	return mScene;
}

BOOL Director::CutScene(String sceneName)
{
	if (sceneName.IsEmpty())
	{
		return FALSE;
	}

	Window::GetInstance()->ClearListeners();
	mSceneName = sceneName;
	mIsCutScene = TRUE;
	return TRUE;
}

LRESULT CALLBACK DrawProc()
{
	Director::GetInstance()->Draw();
	return 0;
}
