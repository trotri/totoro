#pragma once

#include "..\..\totoro\graphics\Scene.h"

class Director;

class BaseScene : public totoro::Scene
{
private:
	Director * mDirector;

protected:
	BaseScene();

public:
	~BaseScene();

public:
	BOOL CutScene(totoro::String sceneName) CONST;
};
