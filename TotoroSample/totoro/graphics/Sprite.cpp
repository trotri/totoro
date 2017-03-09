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

#include "Sprite.h"

using namespace totoro;

Sprite::Sprite() : mTexture(NULL)
{
}

Sprite::~Sprite()
{
}

Sprite * Sprite::Create(Texture * texture)
{
	Sprite * result = new Sprite;
	if (result && result->SetTexture(texture))
	{
		return result;
	}

	DELETE_PTR(result);
	return NULL;
}

BOOL Sprite::Draw()
{
	Texture * texture = GetTexture();
	if (texture == NULL)
	{
		Log::e(TAG, TEXT("Draw Texture Is NULL!\n"));
		return FALSE;
	}

	TEXTURE_ID id = texture->GetId();
	if (id <= 0)
	{
		Log::e(TAG, TEXT("Draw Id Less or Equal Than Zero!\n"));
		return FALSE;
	}

	IGraphics * graphics = texture->GetGraphics();
	if (graphics == NULL)
	{
		Log::e(TAG, TEXT("Draw Graphics Is NULL!\n"));
		return FALSE;
	}

	GRAPHICS_TYPE type = texture->GetType();
	switch (type)
	{
	case GT_IMAGE:
		return graphics->DrawImage(id, &mAttributes);
		break;
	case GT_FONT:
		return graphics->DrawFont(id, &mAttributes);
		break;
	default:
		Log::e(TAG, TEXT("Draw Type '%d' Is Wrong!\n"), type);
		break;
	}

	return FALSE;
}

Texture * Sprite::GetTexture() CONST
{
	return mTexture;
}

BOOL Sprite::SetTexture(Texture * texture)
{
	if (texture == NULL)
	{
		return FALSE;
	}

	mTexture = texture;
	return TRUE;
}

FLOAT Sprite::GetHotspotX() CONST
{
	return mAttributes.hotspot.x;
}

FLOAT Sprite::GetHotspotY() CONST
{
	return mAttributes.hotspot.y;
}

CONST POSITION * Sprite::GetHotspot() CONST
{
	return &mAttributes.hotspot;
}

BOOL Sprite::SetHotspot(FLOAT x, FLOAT y)
{
	if (x < 0)
	{
		Log::e(TAG, TEXT("SetHotspot Failure, X '%.2f' Less Than Zero!\n"), x);
		return FALSE;
	}

	if (y < 0)
	{
		Log::e(TAG, TEXT("SetHotspot Failure, Y '%.2f' Less Than Zero!\n"), y);
		return FALSE;
	}

	mAttributes.hotspot.x = x;
	mAttributes.hotspot.y = y;
	return TRUE;
}

LONG Sprite::GetRegionLeft() CONST
{
	return (mAttributes.region != NULL) ? mAttributes.region->left : -1;
}

LONG Sprite::GetRegionTop() CONST
{
	return (mAttributes.region != NULL) ? mAttributes.region->top : -1;
}

LONG Sprite::GetRegionRight() CONST
{
	return (mAttributes.region != NULL) ? mAttributes.region->right : -1;
}

LONG Sprite::GetRegionBottom() CONST
{
	return (mAttributes.region != NULL) ? mAttributes.region->bottom : -1;
}

CONST RECT * Sprite::GetRegion() CONST
{
	return mAttributes.region;
}

BOOL Sprite::SetRegion(LONG left, LONG top, LONG right, LONG bottom)
{
	if (left < 0 || top < 0 || right <= 0 || bottom <= 0)
	{
		return FALSE;
	}

	if (mAttributes.region == NULL)
	{
		mAttributes.region = new RECT;
	}

	return SetRect(mAttributes.region, left, top, right, bottom);
}

FLOAT Sprite::GetScaleX() CONST
{
	return mAttributes.scale.x;
}

FLOAT Sprite::GetScaleY() CONST
{
	return mAttributes.scale.y;
}

CONST SCALE * Sprite::GetScale() CONST
{
	return &mAttributes.scale;
}

BOOL Sprite::SetScale(FLOAT x, FLOAT y)
{
	mAttributes.scale.x = x;
	mAttributes.scale.y = y;
	return TRUE;
}

FLOAT Sprite::GetAngle() CONST
{
	return mAttributes.angle;
}

BOOL Sprite::SetAngle(FLOAT angle)
{
	mAttributes.angle = FINAL_UNIT_RADIAN * angle;
	return TRUE;
}

FLOAT Sprite::GetPosX() CONST
{
	return mAttributes.pos.x;
}

FLOAT Sprite::GetPosY() CONST
{
	return mAttributes.pos.y;
}

CONST POSITION * Sprite::GetPos() CONST
{
	return &mAttributes.pos;
}

BOOL Sprite::SetPos(FLOAT x, FLOAT y)
{
	mAttributes.pos.x = x;
	mAttributes.pos.y = y;
	return TRUE;
}

FLOAT Sprite::GetZIndex() CONST
{
	return mAttributes.zIndex;
}

BOOL Sprite::SetZIndex(FLOAT zIndex)
{
	if (zIndex < FINAL_Z_INDEX_MIN || zIndex > FINAL_Z_INDEX_MAX)
	{
		return FALSE;
	}

	mAttributes.zIndex = zIndex;
	return TRUE;
}

WSTRING Sprite::GetTextW() CONST
{
	return mAttributes.wText;
}

BOOL Sprite::SetTextW(WSTRING text)
{
	mAttributes.wText = text;
	return TRUE;
}

ASTRING Sprite::GetTextA() CONST
{
	return mAttributes.aText;
}

BOOL Sprite::SetTextA(ASTRING text)
{
	mAttributes.aText = text;
	return TRUE;
}

BOOL Sprite::IsUnicode() CONST
{
	return mAttributes.isUnicode;
}

BOOL Sprite::SetUnicode(BOOL isUnicode)
{
	mAttributes.isUnicode = isUnicode;
	return TRUE;
}

TCOLOR Sprite::GetColor() CONST
{
	return mAttributes.color;
}

BOOL Sprite::SetColor(TCOLOR color)
{
	if (color < 0)
	{
		return FALSE;
	}

	mAttributes.color = color;
	return TRUE;
}

BOOL Sprite::IsTransform() CONST
{
	return mAttributes.isTransform;
}

BOOL Sprite::SetTransform(BOOL isTransform)
{
	mAttributes.isTransform = isTransform;
	return TRUE;
}

MOVE_WSAD Sprite::MoveToPos(POSITION * pos, CONST POSITION * dest, FLOAT distance)
{
	Texture * texture = GetTexture();
	if (texture == NULL)
	{
		Log::e(TAG, TEXT("MoveToPos Texture Is NULL!\n"));
		return MOVE_WSAD::MW_UNDEFINED;
	}

	IGraphics * graphics = texture->GetGraphics();
	if (graphics == NULL)
	{
		Log::e(TAG, TEXT("MoveToPos Graphics Is NULL!\n"));
		return MOVE_WSAD::MW_UNDEFINED;
	}

	return graphics->MoveToPos(pos, dest, distance);
}
