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

#ifndef BASIC_H_
#define BASIC_H_

#include "..\ap\INode.h"
#include "..\graphics\Sprite.h"
#include "..\util\FontFamily.h"
#include "..\util\Text.h"

namespace totoro
{
/**
 * Basic class file
 * 游戏基本元素类
 *
 * @author 宋欢 <trotri@yeah.net>
 * @version $Id: Basic.h 1 2015-04-06 19:22:06Z huan.song $
 * @since 1.0
 */
class Basic : public INode
{
public:
	CONST TCHAR * TAG = TEXT("Basic");

public:
	static CONST UINT DEFAULT_SPEED;

protected:
	Sprite * mSprite;
	BOOL mIsOutputTextureAttrs;
	BOOL mIsOutputSpriteAttrs;
	BOOL mIsOutputBasicAttrs;
	RECTWH mShowSize;
	BOOL mIsNeedResetShowSize;
	RECT4P mBox;
	BOOL mIsNeedResetBox;
	BOOL mIsAllowOutside;
	UINT mSpeed;
	MOVE_WSAD mMoveWsad;

protected:
	Basic();

public:
	~Basic();

public:
	static Basic * Create(String fileName);
	static Basic * CreateImage(String name, String path);
	static Basic * CreateFont(String name, UINT width, UINT height, UINT weight, BOOL isItalic, DWORD quality, String faceName);

protected:
	virtual BOOL _Initialize(String fileName);
	virtual BOOL _InitializeImage(String name, String path);
	virtual BOOL _InitializeFont(String name, UINT width, UINT height, UINT weight, BOOL isItalic, DWORD quality, String faceName);

public:
	virtual BOOL Draw();

public:
	virtual BOOL SetParams(std::map<String, String> params);
	GRAPHICS_TYPE GetType() CONST;
	TEXTURE_ID GetId() CONST;
	String GetName() CONST;
	String GetPath() CONST;
	UINT GetWidth() CONST;
	UINT GetHeight() CONST;
	CONST RECTWH * GetSize() CONST;
	IMG_FORMAT GetFormat() CONST;
	UINT GetWeight() CONST;
	BOOL IsItalic() CONST;
	DWORD GetQuality() CONST;
	String GetFaceName() CONST;
	FLOAT GetHotspotX() CONST;
	BOOL SetHotspotX(FLOAT hotspotX);
	FLOAT GetHotspotY() CONST;
	BOOL SetHotspotY(FLOAT hotspotY);
	CONST POSITION * GetHotspot() CONST;
	BOOL SetHotspot(CONST POSITION * hotspot);
	virtual BOOL SetHotspot(FLOAT x, FLOAT y);
	virtual BOOL SetHotspotPercent(FLOAT xPercent, FLOAT yPercent);
	LONG GetRegionLeft() CONST;
	LONG GetRegionTop() CONST;
	LONG GetRegionRight() CONST;
	LONG GetRegionBottom() CONST;
	CONST RECT * GetRegion() CONST;
	BOOL SetRegion(CONST RECT * region);
	virtual BOOL SetRegion(LONG left, LONG top, LONG right, LONG bottom);
	FLOAT GetScaleX() CONST;
	BOOL SetScaleX(FLOAT x);
	FLOAT GetScaleY() CONST;
	BOOL SetScaleY(FLOAT y);
	CONST SCALE * GetScale() CONST;
	BOOL SetScale(CONST SCALE * scale);
	virtual BOOL SetScale(FLOAT x, FLOAT y);
	FLOAT GetAngle() CONST;
	virtual BOOL SetAngle(FLOAT angle);
	FLOAT GetPosX() CONST;
	BOOL SetPosX(FLOAT x);
	FLOAT GetPosY() CONST;
	BOOL SetPosY(FLOAT y);
	CONST POSITION * GetPos() CONST;
	BOOL SetPos(CONST POSITION * pos);
	virtual BOOL SetPos(FLOAT x, FLOAT y);
	FLOAT GetZIndex() CONST;
	virtual BOOL SetZIndex(FLOAT zIndex);
	WSTRING GetTextW() CONST;
	virtual BOOL SetTextW(WSTRING text);
	ASTRING GetTextA() CONST;
	virtual BOOL SetTextA(ASTRING text);
	BOOL IsUnicode() CONST;
	virtual BOOL SetUnicode(BOOL isUnicode);
	TCOLOR GetColor() CONST;
	virtual BOOL SetColor(TCOLOR color);
	BOOL IsTransform() CONST;
	virtual BOOL SetTransform(BOOL isTransform);
	BOOL IsOutputTextureAttrs() CONST;
	Basic * SetOutputTextureAttrs(BOOL isOutput);
	BOOL IsOutputSpriteAttrs() CONST;
	Basic * SetOutputSpriteAttrs(BOOL isOutput);
	BOOL IsOutputBasicAttrs() CONST;
	Basic * SetOutputBasicAttrs(BOOL isOutput);
	UINT GetShowWidth();
	UINT GetShowHeight();
	CONST RECTWH * GetShowSize();
	BOOL IsNeedResetShowSize() CONST;
	virtual BOOL SetNeedResetShowSize(BOOL isNeedResetShowSize);
	CONST RECT4P * GetBox();
	BOOL IsNeedResetBox() CONST;
	virtual BOOL SetNeedResetBox(BOOL isNeedResetBox);
	BOOL IsAllowOutside() CONST;
	virtual BOOL SetAllowOutside(BOOL isAllowOutside);
	UINT GetSpeed() CONST;
	virtual BOOL SetSpeed(UINT speed);
	MOVE_WSAD GetMoveWsad() CONST;
	virtual BOOL SetMoveWsad(MOVE_WSAD moveWsad);
	FLOAT GetRefreshIntervalDistance() CONST;
	MOVE_WSAD MoveToPos(POSITION * pos, CONST POSITION * dest);
	MOVE_WSAD MoveToPos(POSITION * pos, CONST POSITION * dest, FLOAT distance);
	VOID DebugOutput();
};

}

#endif /* !BASIC_H_ */
