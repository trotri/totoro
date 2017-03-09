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

#include "DxGraphics.h"

using namespace totoro;

DxGraphics::DxGraphics()
{
	mDirect = DxDirect::GetInstance();
}

DxGraphics::~DxGraphics()
{
	DELETE_PTR(mDirect);
}

BOOL DxGraphics::Clear()
{
	mAutoIncrementId = 0;

	LPDIRECT3DTEXTURE9 pImageTexture;
	for (std::map<TEXTURE_ID, LPDIRECT3DTEXTURE9>::iterator it = mImageTextures.begin(); it != mImageTextures.end(); it++)
	{
		pImageTexture = it->second;
		RELEASE_PTR(pImageTexture);
	}

	mImageTextures.clear();

	LPDIRECT3DTEXTURE9 pColliderTexture;
	for (std::map<TEXTURE_ID, LPDIRECT3DTEXTURE9>::iterator it = mColliderTextures.begin(); it != mColliderTextures.end(); it++)
	{
		pColliderTexture = it->second;
		RELEASE_PTR(pColliderTexture);
	}

	mColliderTextures.clear();

	LPD3DXFONT pFontTexture;
	for (std::map<TEXTURE_ID, LPD3DXFONT>::iterator it = mFontTextures.begin(); it != mFontTextures.end(); it++)
	{
		pFontTexture = it->second;
		RELEASE_PTR(pFontTexture);
	}

	mFontTextures.clear();

	return TRUE;
}

BOOL DxGraphics::BeginScene()
{
	return mDirect->BeginScene();
}

BOOL DxGraphics::EndScene()
{
	return mDirect->EndScene();
}

BOOL DxGraphics::CreateImage(LPTEXTURE_ATTRIBUTES Attrs)
{
	LPDIRECT3DTEXTURE9 pTexture;
	if (mDirect->CreateImageTexture(&pTexture, Attrs))
	{
		if (pTexture != NULL)
		{
			Attrs->id = GetAutoIncrementId(TRUE);
			mImageTextures.insert(std::make_pair(Attrs->id, pTexture));
			return TRUE;
		}
	}

	return FALSE;
}

BOOL DxGraphics::CreateCollider(LPTEXTURE_ATTRIBUTES Attrs)
{
	LPDIRECT3DTEXTURE9 pTexture;
	if (mDirect->CreateColliderTexture(&pTexture, Attrs))
	{
		if (pTexture != NULL)
		{
			Attrs->id = GetAutoIncrementId(TRUE);
			mColliderTextures.insert(std::make_pair(Attrs->id, pTexture));
			return TRUE;
		}
	}

	return FALSE;
}

BOOL DxGraphics::CreateFont(LPTEXTURE_ATTRIBUTES Attrs)
{
	LPD3DXFONT pTexture;
	if (mDirect->CreateFontTexture(&pTexture, Attrs))
	{
		if (pTexture != NULL)
		{
			Attrs->id = GetAutoIncrementId(TRUE);
			mFontTextures.insert(std::make_pair(Attrs->id, pTexture));
			return TRUE;
		}
	}

	return FALSE;
}

BOOL DxGraphics::DrawImage(TEXTURE_ID Id, CONST SPRITE_ATTRIBUTES * Attrs)
{
	LPDIRECT3DTEXTURE9 pTexture = mImageTextures[Id];
	if (pTexture == NULL)
	{
		return FALSE;
	}

	return mDirect->DrawImageTexture(pTexture, Attrs);
}

BOOL DxGraphics::DrawFont(TEXTURE_ID Id, CONST SPRITE_ATTRIBUTES * Attrs)
{
	LPD3DXFONT pTexture = mFontTextures[Id];
	if (pTexture == NULL)
	{
		return FALSE;
	}

	return mDirect->DrawFontTexture(pTexture, Attrs);
}

BOOL DxGraphics::DrawLine(CONST POSITION * Begin, CONST POSITION * End, TCOLOR Color, FLOAT Width)
{
	if (Begin == NULL || End == NULL)
	{
		return FALSE;
	}

	mVertexes[0].x = Begin->x;
	mVertexes[0].y = Begin->y;
	mVertexes[1].x = End->x;
	mVertexes[1].y = End->y;

	return mDirect->DrawLine(mVertexes, 2, Color, Width);
}

MOVE_WSAD DxGraphics::MoveToPos(POSITION * Pos, CONST POSITION * Dest, FLOAT Distance)
{
	return mDirect->MoveToPos(Pos, Dest, Distance);
}
