#include "BaseScene.h"
#include "..\..\Director.h"

using namespace totoro;

BaseScene::BaseScene()
{
	mDirector = Director::GetInstance();
	AudioRegistry::SetDisabled(Cfg::IsAudioDisabled());
}

BaseScene::~BaseScene()
{
}

BOOL BaseScene::CutScene(String sceneName) CONST
{
	return mDirector->CutScene(sceneName);
}
