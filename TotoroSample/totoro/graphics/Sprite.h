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

#ifndef SPRITE_H_
#define SPRITE_H_

#include "TextureRegistry.h"

namespace totoro
{
/**
 * Sprite class file
 * Ã˘ÕºªÊ÷∆¿‡
 *
 * @author ÀŒª∂ <trotri@yeah.net>
 * @version $Id: Sprite.h 1 2015-04-06 19:22:06Z huan.song $
 * @since 1.0
 */
class Sprite
{
public:
	CONST TCHAR * TAG = TEXT("Sprite");

private:
	Texture * mTexture;
	SPRITE_ATTRIBUTES mAttributes;

protected:
	Sprite();

public:
	virtual ~Sprite();

public:
	static Sprite * Create(Texture * texture);

public:
	BOOL Draw();

public:
	Texture * GetTexture() CONST;
	BOOL SetTexture(Texture * texture);
	FLOAT GetHotspotX() CONST;
	FLOAT GetHotspotY() CONST;
	CONST POSITION * GetHotspot() CONST;
	BOOL SetHotspot(FLOAT x, FLOAT y);
	LONG GetRegionLeft() CONST;
	LONG GetRegionTop() CONST;
	LONG GetRegionRight() CONST;
	LONG GetRegionBottom() CONST;
	CONST RECT * GetRegion() CONST;
	BOOL SetRegion(LONG left, LONG top, LONG right, LONG bottom);
	FLOAT GetScaleX() CONST;
	FLOAT GetScaleY() CONST;
	CONST SCALE * GetScale() CONST;
	BOOL SetScale(FLOAT x, FLOAT y);
	FLOAT GetAngle() CONST;
	BOOL SetAngle(FLOAT angle);
	FLOAT GetPosX() CONST;
	FLOAT GetPosY() CONST;
	CONST POSITION * GetPos() CONST;
	BOOL SetPos(FLOAT x, FLOAT y);
	FLOAT GetZIndex() CONST;
	BOOL SetZIndex(FLOAT zIndex);
	WSTRING GetTextW() CONST;
	BOOL SetTextW(WSTRING text);
	ASTRING GetTextA() CONST;
	BOOL SetTextA(ASTRING text);
	BOOL IsUnicode() CONST;
	BOOL SetUnicode(BOOL isUnicode);
	TCOLOR GetColor() CONST;
	BOOL SetColor(TCOLOR color);
	BOOL IsTransform() CONST;
	BOOL SetTransform(BOOL isTransform);
	MOVE_WSAD MoveToPos(POSITION * pos, CONST POSITION * dest, FLOAT distance);
};

}

#endif /* !SPRITE_H_ */
