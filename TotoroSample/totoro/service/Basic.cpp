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

#include "Basic.h"

using namespace totoro;

CONST UINT Basic::DEFAULT_SPEED = 120;

Basic::Basic() : mSprite(NULL), mIsOutputTextureAttrs(FALSE), mIsOutputSpriteAttrs(FALSE), mIsOutputBasicAttrs(FALSE), mIsNeedResetShowSize(TRUE), mIsNeedResetBox(TRUE), mIsAllowOutside(TRUE), mSpeed(DEFAULT_SPEED), mMoveWsad(MOVE_WSAD::MW_UNDEFINED)
{
	ScheduleUpdate();
}

Basic::~Basic()
{
	DELETE_PTR(mSprite);
}

Basic * Basic::Create(String fileName)
{
	Basic * result = new Basic;
	if (result && result->_Initialize(fileName))
	{
		return result;
	}

	DELETE_PTR(result);
	return NULL;
}

Basic * Basic::CreateImage(String name, String path)
{
	Basic * result = new Basic;
	if (result && result->_InitializeImage(name, path))
	{
		return result;
	}

	DELETE_PTR(result);
	return NULL;
}

Basic * Basic::CreateFont(String name, UINT width, UINT height, UINT weight, BOOL isItalic, DWORD quality, String faceName)
{
	Basic * result = new Basic;
	if (result && result->_InitializeFont(name, width, height, weight, isItalic, quality, faceName))
	{
		return result;
	}

	DELETE_PTR(result);
	return NULL;
}

BOOL Basic::_Initialize(String fileName)
{
	if (fileName.IsEmpty())
	{
		return FALSE;
	}

	std::map<String, String> params = Text::GetCfg(fileName);

	String sType = params[TEXT("type")], sName = params[TEXT("name")];
	String sPath = params[TEXT("path")];
	String sWidth = params[TEXT("width")], sHeight = params[TEXT("height")];
	String sWeight = params[TEXT("weight")];
	String sIsItalic = params[TEXT("is_italic")];
	String sQuality = params[TEXT("quality")];
	String sFontId = params[TEXT("font_id")];

	UINT type = GRAPHICS_TYPE::GT_UNDEFINED;
	UINT width = 0, height = 0;
	UINT weight = 0;
	BOOL isItalic = FALSE;
	DWORD quality = 0;
	UINT fontId = 1001;

	if (!sType.IsEmpty())     type     = sType.ToInt();
	if (!sWidth.IsEmpty())    width    = sWidth.ToInt();
	if (!sHeight.IsEmpty())   height   = sHeight.ToInt();
	if (!sWeight.IsEmpty())   weight   = sWeight.ToInt();
	if (!sIsItalic.IsEmpty()) isItalic = ((sIsItalic.ToInt() == 0) ? FALSE : TRUE);
	if (!sQuality.IsEmpty())  quality  = sQuality.ToULong();
	if (!sFontId.IsEmpty())   fontId   = sFontId.ToInt();

	String fontName = FontFamily::GetInstance()->GetName(fontId);

	if (type == GRAPHICS_TYPE::GT_IMAGE)
	{
		if (!_InitializeImage(sName, sPath))
		{
			return FALSE;
		}

		SetParams(params);
		return TRUE;
	}

	if (type == GRAPHICS_TYPE::GT_FONT)
	{
		if (!_InitializeFont(sName, width, height, weight, isItalic, quality, fontName))
		{
			return FALSE;
		}

		SetParams(params);
		return TRUE;
	}

	Log::e(TAG, TEXT("_Initialize Failure, Type '%d' Wrong!\n"), type);
	return FALSE;
}

BOOL Basic::_InitializeImage(String name, String path)
{
	Texture * texture = TextureRegistry::AddImage(name, path);
	if (texture == NULL)
	{
		return FALSE;
	}

	mSprite = Sprite::Create(texture);
	if (mSprite == NULL)
	{
		return FALSE;
	}

	SetName(name);
	return TRUE;
}

BOOL Basic::_InitializeFont(String name, UINT width, UINT height, UINT weight, BOOL isItalic, DWORD quality, String faceName)
{
	Texture * texture = TextureRegistry::AddFont(name, width, height, weight, isItalic, quality, faceName);
	if (texture == NULL)
	{
		return FALSE;
	}

	mSprite = Sprite::Create(texture);
	if (mSprite == NULL)
	{
		return FALSE;
	}

	SetName(name);
	return TRUE;
}

BOOL Basic::Draw()
{
	if (!mSprite->Draw())
	{
		Log::e(TAG, TEXT("Draw Failure, mSprite->Draw Failure!\n"));
		return FALSE;
	}

	DebugOutput();
	return TRUE;
}

BOOL Basic::SetParams(std::map<String, String> params)
{
	String sHotspotX = params[TEXT("hotspot_x")], sHotspotY = params[TEXT("hotspot_y")];
	String sHotspotXPercent = params[TEXT("hotspot_x_percent")], sHotspotYPercent = params[TEXT("hotspot_y_percent")];
	String sLeft = params[TEXT("region_left")], sTop = params[TEXT("region_top")], sRight = params[TEXT("region_right")], sBottom = params[TEXT("region_bottom")];
	String sScaleX = params[TEXT("scale_x")], sScaleY = params[TEXT("scale_y")];
	String sAngle = params[TEXT("angle")];
	String sPosX = params[TEXT("pos_x")], sPosY = params[TEXT("pos_y")], sZIndex = params[TEXT("z_index")];
	String sIsTransform = params[TEXT("is_transform")];
	String sIsUnicode = params[TEXT("is_unicode")];
	String sColor = params[TEXT("color")];
	String sIsAllowOutside = params[TEXT("is_allow_outside")];
	String sSpeed = params[TEXT("speed")];
	String sMoveWsad = params[TEXT("move_wsad")];

	FLOAT hotspotX = 0, hotspotY = 0;
	FLOAT hotspotXPercent = -1, hotspotYPercent = -1;
	LONG left = -1, top = -1, right = -1, bottom = -1;
	FLOAT scaleX = 1, scaleY = 1;
	FLOAT angle = 0;
	FLOAT posX = 0, posY = 0, zIndex = -1;
	BOOL isTransform = TRUE, isUnicode = TRUE, isAllowOutside = TRUE;
	TCOLOR color = -1;
	UINT speed = DEFAULT_SPEED;
	MOVE_WSAD moveWsad = MW_UNDEFINED;

	if (!sHotspotX.IsEmpty())        hotspotX = sHotspotX.ToFloat();
	if (!sHotspotY.IsEmpty())        hotspotY = sHotspotY.ToFloat();
	if (!sHotspotXPercent.IsEmpty()) hotspotXPercent = sHotspotXPercent.ToFloat();
	if (!sHotspotYPercent.IsEmpty()) hotspotYPercent = sHotspotYPercent.ToFloat();
	if (!sLeft.IsEmpty())            left = sLeft.ToLong();
	if (!sTop.IsEmpty())             top = sTop.ToLong();
	if (!sRight.IsEmpty())           right = sRight.ToLong();
	if (!sBottom.IsEmpty())          bottom = sBottom.ToLong();
	if (!sScaleX.IsEmpty())          scaleX = sScaleX.ToFloat();
	if (!sScaleY.IsEmpty())          scaleY = sScaleY.ToFloat();
	if (!sAngle.IsEmpty())           angle = sAngle.ToFloat();
	if (!sPosX.IsEmpty())            posX = sPosX.ToFloat();
	if (!sPosY.IsEmpty())            posY = sPosY.ToFloat();
	if (!sZIndex.IsEmpty())          zIndex = sZIndex.ToFloat();
	if (!sIsTransform.IsEmpty())     isTransform = ((sIsTransform.ToInt() == 0) ? FALSE : TRUE);
	if (!sIsUnicode.IsEmpty())       isUnicode = ((sIsUnicode.ToInt() == 0) ? FALSE : TRUE);
	if (!sColor.IsEmpty())           color = sColor.ToULong();
	if (!sIsAllowOutside.IsEmpty())  isAllowOutside = ((sIsAllowOutside.ToInt() == 0) ? FALSE : TRUE);
	if (!sSpeed.IsEmpty())           speed = sSpeed.ToUInt();
	if (!sMoveWsad.IsEmpty())        moveWsad = static_cast<MOVE_WSAD>(sMoveWsad.ToUInt());

	SetHotspot(hotspotX, hotspotY);
	SetRegion(left, top, right, bottom);
	SetScale(scaleX, scaleY);
	SetAngle(angle);
	SetPos(posX, posY);
	SetZIndex(zIndex);
	SetTransform(isTransform);
	SetUnicode(isUnicode);
	SetColor(color);
	SetAllowOutside(isAllowOutside);
	SetHotspotPercent(hotspotXPercent, hotspotYPercent);
	SetSpeed(speed);
	SetMoveWsad(moveWsad);
	return TRUE;
}

GRAPHICS_TYPE Basic::GetType() CONST
{
	return mSprite->GetTexture()->GetType();
}

TEXTURE_ID Basic::GetId() CONST
{
	return mSprite->GetTexture()->GetId();
}

String Basic::GetName() CONST
{
	return mSprite->GetTexture()->GetName();
}

String Basic::GetPath() CONST
{
	return mSprite->GetTexture()->GetPath();
}

UINT Basic::GetWidth() CONST
{
	return mSprite->GetTexture()->GetWidth();
}

UINT Basic::GetHeight() CONST
{
	return mSprite->GetTexture()->GetHeight();
}

CONST RECTWH * Basic::GetSize() CONST
{
	return mSprite->GetTexture()->GetSize();
}

IMG_FORMAT Basic::GetFormat() CONST
{
	return mSprite->GetTexture()->GetFormat();
}

UINT Basic::GetWeight() CONST
{
	return mSprite->GetTexture()->GetWeight();
}

BOOL Basic::IsItalic() CONST
{
	return mSprite->GetTexture()->IsItalic();
}

DWORD Basic::GetQuality() CONST
{
	return mSprite->GetTexture()->GetQuality();
}

String Basic::GetFaceName() CONST
{
	return mSprite->GetTexture()->GetFaceName();
}

FLOAT Basic::GetHotspotX() CONST
{
	return mSprite->GetHotspotX();
}

BOOL Basic::SetHotspotX(FLOAT hotspotX)
{
	return SetHotspot(hotspotX, GetHotspotY());
}

FLOAT Basic::GetHotspotY() CONST
{
	return mSprite->GetHotspotY();
}

BOOL Basic::SetHotspotY(FLOAT hotspotY)
{
	return SetHotspot(GetHotspotX(), hotspotY);
}

CONST POSITION * Basic::GetHotspot() CONST
{
	return mSprite->GetHotspot();
}

BOOL Basic::SetHotspot(CONST POSITION * hotspot)
{
	if (hotspot == NULL)
	{
		return FALSE;
	}

	return SetHotspot(hotspot->x, hotspot->y);
}

BOOL Basic::SetHotspot(FLOAT x, FLOAT y)
{
	if (!mSprite->SetHotspot(x, y))
	{
		return FALSE;
	}

	UINT width = GetShowWidth();
	UINT height = GetShowHeight();
	if (width <= 0 || height <= 0)
	{
		return FALSE;
	}

	if (x > width)
	{
		Log::e(TAG, TEXT("SetHotspot Failure, X '%.2f' Greater Than Show Width '%d'!\n"), x, width);
		return FALSE;
	}

	if (y > height)
	{
		Log::e(TAG, TEXT("%s::SetHotspot Failure, Y '%.2f' Greater Than Show Height '%d'!\n"), y, height);
		return FALSE;
	}

	SetNeedResetBox(TRUE);
	return TRUE;
}

BOOL Basic::SetHotspotPercent(FLOAT xPercent, FLOAT yPercent)
{
	if (xPercent < 0 || yPercent < 0 || xPercent > 1.0f || yPercent > 1.0f)
	{
		return FALSE;
	}

	UINT width = GetShowWidth();
	UINT height = GetShowHeight();
	if (width <= 0 || height <= 0)
	{
		return FALSE;
	}

	FLOAT x = width * xPercent;
	FLOAT y = height * yPercent;
	SetHotspot(x, y);
	return TRUE;
}

LONG Basic::GetRegionLeft() CONST
{
	return mSprite->GetRegionLeft();
}

LONG Basic::GetRegionTop() CONST
{
	return mSprite->GetRegionTop();
}

LONG Basic::GetRegionRight() CONST
{
	return mSprite->GetRegionRight();
}

LONG Basic::GetRegionBottom() CONST
{
	return mSprite->GetRegionBottom();
}

CONST RECT * Basic::GetRegion() CONST
{
	return mSprite->GetRegion();
}

BOOL Basic::SetRegion(CONST RECT * region)
{
	if (region == NULL)
	{
		return FALSE;
	}

	return SetRegion(region->left, region->top, region->right, region->bottom);
}

BOOL Basic::SetRegion(LONG left, LONG top, LONG right, LONG bottom)
{
	if (!mSprite->SetRegion(left, top, right, bottom))
	{
		return FALSE;
	}

	SetNeedResetShowSize(TRUE);
	return TRUE;
}

FLOAT Basic::GetScaleX() CONST
{
	return mSprite->GetScaleX();
}

BOOL Basic::SetScaleX(FLOAT x)
{
	return SetScale(x, GetScaleY());
}

FLOAT Basic::GetScaleY() CONST
{
	return mSprite->GetScaleY();
}

BOOL Basic::SetScaleY(FLOAT y)
{
	return SetScale(GetScaleX(), y);
}

CONST SCALE * Basic::GetScale() CONST
{
	return mSprite->GetScale();
}

BOOL Basic::SetScale(CONST SCALE * scale)
{
	if (scale == NULL)
	{
		return FALSE;
	}

	return SetScale(scale->x, scale->y);
}

BOOL Basic::SetScale(FLOAT x, FLOAT y)
{
	if (!mSprite->SetScale(x, y))
	{
		return FALSE;
	}

	SetNeedResetShowSize(TRUE);
	return TRUE;
}

FLOAT Basic::GetAngle() CONST
{
	return mSprite->GetAngle();
}

BOOL Basic::SetAngle(FLOAT angle)
{
	if (!mSprite->SetAngle(angle))
	{
		return FALSE;
	}

	SetNeedResetBox(TRUE); // 角度改变时，重置ShowSize和Box都无法准确计算出矩形区域
	return TRUE;
}

FLOAT Basic::GetPosX() CONST
{
	return mSprite->GetPosX();
}

BOOL Basic::SetPosX(FLOAT x)
{
	return SetPos(x, GetPosY());
}

FLOAT Basic::GetPosY() CONST
{
	return mSprite->GetPosY();
}

BOOL Basic::SetPosY(FLOAT y)
{
	return SetPos(GetPosX(), y);
}

CONST POSITION * Basic::GetPos() CONST
{
	return mSprite->GetPos();
}

BOOL Basic::SetPos(CONST POSITION * pos)
{
	if (pos == NULL)
	{
		return FALSE;
	}

	return SetPos(pos->x, pos->y);
}

BOOL Basic::SetPos(FLOAT x, FLOAT y)
{
	if (!mSprite->SetPos(x, y))
	{
		return FALSE;
	}

	SetNeedResetBox(TRUE);
	return TRUE;
}

FLOAT Basic::GetZIndex() CONST
{
	return mSprite->GetZIndex();
}

BOOL Basic::SetZIndex(FLOAT zIndex)
{
	return mSprite->SetZIndex(zIndex);
}

WSTRING Basic::GetTextW() CONST
{
	return mSprite->GetTextW();
}

BOOL Basic::SetTextW(WSTRING text)
{
	return mSprite->SetTextW(text);
}

ASTRING Basic::GetTextA() CONST
{
	return mSprite->GetTextA();
}

BOOL Basic::SetTextA(ASTRING text)
{
	return mSprite->SetTextA(text);
}

BOOL Basic::IsUnicode() CONST
{
	return mSprite->IsUnicode();
}

BOOL Basic::SetUnicode(BOOL isUnicode)
{
	return mSprite->SetUnicode(isUnicode);
}

TCOLOR Basic::GetColor() CONST
{
	return mSprite->GetColor();
}

BOOL Basic::SetColor(TCOLOR color)
{
	return mSprite->SetColor(color);
}

BOOL Basic::IsTransform() CONST
{
	return mSprite->IsTransform();
}

BOOL Basic::SetTransform(BOOL isTransform)
{
	return mSprite->SetTransform(isTransform);
}

BOOL Basic::IsOutputTextureAttrs() CONST
{
	return mIsOutputTextureAttrs;
}

Basic * Basic::SetOutputTextureAttrs(BOOL isOutput)
{
	mIsOutputTextureAttrs = isOutput;
	return this;
}

BOOL Basic::IsOutputSpriteAttrs() CONST
{
	return mIsOutputSpriteAttrs;
}

Basic * Basic::SetOutputSpriteAttrs(BOOL isOutput)
{
	mIsOutputSpriteAttrs = isOutput;
	return this;
}

BOOL Basic::IsOutputBasicAttrs() CONST
{
	return mIsOutputBasicAttrs;
}

Basic * Basic::SetOutputBasicAttrs(BOOL isOutput)
{
	mIsOutputBasicAttrs = isOutput;
	return this;
}

UINT Basic::GetShowWidth()
{
	return GetShowSize()->width;
}

UINT Basic::GetShowHeight()
{
	return GetShowSize()->height;
}

CONST RECTWH * Basic::GetShowSize()
{
	if (IsNeedResetShowSize())
	{
		UINT width   = GetWidth();
		UINT height  = GetHeight();
		LONG left    = GetRegionLeft();
		LONG right   = GetRegionRight();
		LONG top     = GetRegionTop();
		LONG bottom  = GetRegionBottom();
		FLOAT scaleX = GetScaleX();
		FLOAT scaleY = GetScaleY();

		if (left >= 0 && top >= 0 && right > 0 && bottom > 0)
		{
			width = abs(right - left);
			height = abs(bottom - top);
		}

		mShowSize.width = static_cast<UINT>(width * abs(scaleX));
		mShowSize.height = static_cast<UINT>(height * abs(scaleY));

		SetNeedResetShowSize(FALSE);
		SetNeedResetBox(TRUE);
	}

	return &mShowSize;
}

BOOL Basic::IsNeedResetShowSize() CONST
{
	return mIsNeedResetShowSize;
}

BOOL Basic::SetNeedResetShowSize(BOOL isNeedResetShowSize)
{
	mIsNeedResetShowSize = isNeedResetShowSize;
	return TRUE;
}

CONST RECT4P * Basic::GetBox()
{
	if (IsNeedResetBox())
	{
		mBox.leftTop.x     = GetPosX() - GetHotspotX();
		mBox.leftTop.y     = GetPosY() - GetHotspotY();
		mBox.leftBottom.x  = mBox.leftTop.x;
		mBox.leftBottom.y  = mBox.leftTop.y + GetShowHeight();
		mBox.rightTop.x    = mBox.leftTop.x + GetShowWidth();
		mBox.rightTop.y    = mBox.leftTop.y;
		mBox.rightBottom.x = mBox.rightTop.x;
		mBox.rightBottom.y = mBox.leftBottom.y;

		SetNeedResetBox(FALSE);
	}

	return &mBox;
}

BOOL Basic::IsNeedResetBox() CONST
{
	return mIsNeedResetBox;
}

BOOL Basic::SetNeedResetBox(BOOL isNeedResetBox)
{
	mIsNeedResetBox = isNeedResetBox;
	return TRUE;
}

BOOL Basic::IsAllowOutside() CONST
{
	return mIsAllowOutside;
}

BOOL Basic::SetAllowOutside(BOOL isAllowOutside)
{
	mIsAllowOutside = isAllowOutside;
	return TRUE;
}

UINT Basic::GetSpeed() CONST
{
	return mSpeed;
}

BOOL Basic::SetSpeed(UINT speed)
{
	mSpeed = speed;
	return TRUE;
}

MOVE_WSAD Basic::GetMoveWsad() CONST
{
	return mMoveWsad;
}

BOOL Basic::SetMoveWsad(MOVE_WSAD moveWsad)
{
	mMoveWsad = moveWsad;
	return TRUE;
}

FLOAT Basic::GetRefreshIntervalDistance() CONST
{
	return GetRefreshInterval() * GetSpeed();
}

MOVE_WSAD Basic::MoveToPos(POSITION * pos, CONST POSITION * dest)
{
	return MoveToPos(pos, dest, GetRefreshIntervalDistance());
}

MOVE_WSAD Basic::MoveToPos(POSITION * pos, CONST POSITION * dest, FLOAT distance)
{
	return mSprite->MoveToPos(pos, dest, distance);
}

VOID Basic::DebugOutput()
{
	if (IsOutputTextureAttrs())
	{
		Log::e(TAG,
			TEXT("Debug Texture Attrs, Type: %d, ID: %ld, Name: %s, Path: %s, Width: %d, Height: %d, Format: %d, Weight: %d, IsItalic: %s, Quality: %ld, FaceName: %s\n"),
			GetType(), GetId(), GetName().c_str(), GetPath().c_str(), GetWidth(), GetHeight(), GetFormat(), GetWeight(), (IsItalic() ? TEXT("TRUE") : TEXT("FALSE")), GetQuality(), GetFaceName().c_str()
		);
	}

	if (IsOutputSpriteAttrs())
	{
		Log::d(TAG,
			TEXT("Debug Sprite Attrs, HotspotX: %.2f, HotspotY: %.2f, RegionLeft: %ld, RegionTop: %ld, RegionRight: %ld, RegionBottom: %ld, ScaleX: %.2f, ScaleY: %.2f, Angle: %.2f, PosX: %.2f, PosY: %.2f, ZIndex: %.2f, WText: %s, AText: %s, IsUnicode: %s, Color: 0x%0x, IsTransform: %s\n"),
			GetHotspotX(), GetHotspotY(), GetRegionLeft(), GetRegionTop(), GetRegionRight(), GetRegionBottom(), GetScaleX(), GetScaleY(), GetAngle(), GetPosX(), GetPosY(), GetZIndex(), GetTextW().c_str(), GetTextA().c_str(), (IsUnicode() ? TEXT("TRUE") : TEXT("FALSE")), GetColor(), (IsTransform() ? TEXT("TRUE") : TEXT("FALSE"))
		);
	}

	if (IsOutputBasicAttrs())
	{
		CONST RECT4P * box = GetBox();
		Log::d(TAG,
			TEXT("Debug Basic Attrs, ShowWidth: %d, ShowHeight: %d, IsNeedResetShowSize: %s, IsAllowOutside: %s, Speed: %d, MoveWsad: %d, IsNeedResetBox: %s, BoxLeftTopX: %.2f, BoxLeftTopY: %.2f, BoxRightTopX: %.2f, BoxRightTopY: %.2f, BoxLeftBottomX: %.2f, BoxLeftBottomY: %.2f, BoxRightBottomX: %.2f, BoxRightBottomY: %.2f\n"),
			GetShowWidth(), GetShowHeight(), (IsNeedResetShowSize() ? TEXT("TRUE") : TEXT("FALSE")), (IsAllowOutside() ? TEXT("TRUE") : TEXT("FALSE")), GetSpeed(), GetMoveWsad(), (IsNeedResetBox() ? TEXT("TRUE") : TEXT("FALSE")), box->leftTop.x, box->leftTop.y, box->rightTop.x, box->rightTop.y, box->leftBottom.x, box->leftBottom.y, box->rightBottom.x, box->rightBottom.y
		);
	}

}
