/*
 * Copyright (C) 2015 The C++ Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SCENE_H_
#define SCENE_H_

#include "..\ap\IScene.h"
#include "dx\DxGraphics.h"
#include "TextureRegistry.h"
#include "..\audio\AudioRegistry.h"

namespace totoro
{
/**
 * Scene class file
 * ≥°æ∞¿‡
 *
 * @author ÀŒª∂ <trotri@yeah.net>
 * @version $Id: Scene.h 1 2015-01-30 16:02:06Z huan.song $
 * @since 1.0
 */
class Scene : public IScene
{
public:
	CONST TCHAR * TAG = TEXT("Scene");

private:
	IGraphics * mGraphics;

protected:
	Scene();

public:
	virtual ~Scene();

public:
	BOOL Begin();
	BOOL End();
};

}

#endif /* !SCENE_H_ */
