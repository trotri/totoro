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

#include "DxDirect.h"

using namespace totoro;

DxDirect::DxDirect() : mDirect(NULL), mDevice(NULL), mSprite(NULL), mLine(NULL)
{
	ZeroMemory(&mParams, sizeof(D3DPRESENT_PARAMETERS));
	
	D3DXMatrixIdentity(&mMatrix);
	D3DXMatrixIdentity(&mTranslation);
	D3DXMatrixIdentity(&mRotationZ);
	D3DXMatrixIdentity(&mScaling);

	mVector2.x = 0;
	mVector2.y = 0;

	mVector3.x = 0;
	mVector3.y = 0;
	mVector3.z = 0;

	_Initialize();
}

DxDirect::~DxDirect()
{
	_Clear();
}

BOOL DxDirect::_Initialize()
{
	Log::d(TAG, TEXT("_Initialize Begin\n"));

	Window * window = Window::GetInstance();

	mDirect = Direct3DCreate9(D3D_SDK_VERSION);
	if (mDirect == NULL)
	{
		Log::e(TAG, TEXT("_Initialize Direct3DCreate9 Failure!\n"));
		return FALSE;
	}

	D3DPRESENT_PARAMETERS params;
	ZeroMemory(&params, sizeof(D3DPRESENT_PARAMETERS));
	params.hDeviceWindow = window->GetHandle();
	params.Windowed = TRUE;
	params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	params.PresentationInterval = D3DPRESENT_DONOTWAIT;
	params.EnableAutoDepthStencil = TRUE;
	params.AutoDepthStencilFormat = D3DFMT_D24S8;

	HRESULT hResult = mDirect->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, window->GetHandle(), D3DCREATE_SOFTWARE_VERTEXPROCESSING, &params, &mDevice);
	if (mDevice == NULL)
	{
		Log::e(TAG, TEXT("_Initialize CreateDevice Failure!\n"));
		return FALSE;
	}

	mDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	hResult = D3DXCreateSprite(mDevice, &mSprite);
	if (mSprite == NULL)
	{
		Log::e(TAG, TEXT("_Initialize D3DXCreateSprite Failure!\n"));
		return FALSE;
	}

	hResult = D3DXCreateLine(mDevice, &mLine);
	if (mLine == NULL)
	{
		Log::e(TAG, TEXT("_Initialize D3DXCreateLine Failure!\n"));
		return FALSE;
	}

	Log::d(TAG, TEXT("_Initialize End\n"));
	return TRUE;
}

BOOL DxDirect::_Clear()
{
	RELEASE_PTR(mLine);
	RELEASE_PTR(mSprite);
	RELEASE_PTR(mDevice);
	RELEASE_PTR(mDirect);

	return TRUE;
}

BOOL DxDirect::BeginScene()
{
	GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xFFFFFFFF, 1.0f, 0);
	GetDevice()->BeginScene();
	GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);

	Console::d(TEXT("%s::BeginScene\n"), TAG);
	return TRUE;
}

BOOL DxDirect::EndScene()
{
	GetSprite()->End();
	GetDevice()->EndScene();
	GetDevice()->Present(0, 0, 0, 0);

	Console::d(TEXT("%s::EndScene\n"), TAG);
	return TRUE;
}

BOOL DxDirect::CreateImageTexture(LPDIRECT3DTEXTURE9 * Texture, LPTEXTURE_ATTRIBUTES Attrs)
{
	if (Attrs == NULL)
	{
		Log::e(TAG, TEXT("CreateImageTexture Failure, Attrs Is NULL!\n"));
		return FALSE;
	}

	if (Attrs->path.IsEmpty())
	{
		Log::e(TAG, TEXT("CreateImageTexture Failure, Path Is Empty!\n"));
		return FALSE;
	}

	D3DXIMAGE_INFO info;
	ZeroMemory(&info, sizeof(D3DXIMAGE_INFO));

	(*Texture) = NULL;

	HRESULT hResult = D3DXCreateTextureFromFileEx(
		GetDevice(),
		Attrs->path.c_str(),
		D3DX_FROM_FILE,
		D3DX_FROM_FILE,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_A8B8G8R8,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,
		&info,
		NULL,
		Texture
	);

	if ((*Texture) == NULL)
	{
		Log::e(TAG, TEXT("CreateImageTexture Failure, HRESULT: %d, Path: %s\n"), hResult, Attrs->path.c_str());
		return FALSE;
	}

	if (Attrs != NULL)
	{
		Attrs->size.width = info.Width;
		Attrs->size.height = info.Height;
		Attrs->format = static_cast<IMG_FORMAT>(info.ImageFileFormat);
	}

	return TRUE;
}

BOOL DxDirect::CreateColliderTexture(LPDIRECT3DTEXTURE9 * Texture, LPTEXTURE_ATTRIBUTES Attrs)
{
	if (Attrs == NULL)
	{
		Log::e(TAG, TEXT("CreateColliderTexture Failure, Attrs Is NULL!\n"));
		return FALSE;
	}

	if (Attrs->path.IsEmpty())
	{
		Log::e(TAG, TEXT("CreateColliderTexture Failure, Path Is Empty!\n"));
		return FALSE;
	}

	D3DXIMAGE_INFO info;
	ZeroMemory(&info, sizeof(D3DXIMAGE_INFO));

	(*Texture) = NULL;

	HRESULT hResult = D3DXCreateTextureFromFileEx(
		GetDevice(),
		Attrs->path.c_str(),
		D3DX_FROM_FILE,
		D3DX_FROM_FILE,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_A8B8G8R8,
		D3DPOOL_SYSTEMMEM,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,
		&info,
		NULL,
		Texture
	);

	if ((*Texture) == NULL)
	{
		Log::e(TAG, TEXT("CreateColliderTexture Failure, HRESULT: %d, Path: %s\n"), hResult, Attrs->path.c_str());
		return FALSE;
	}

	D3DLOCKED_RECT oLockedRect;
	(*Texture)->LockRect(0, &oLockedRect, 0, D3DLOCK_DISCARD);
	DWORD * pCollidedBits = static_cast<DWORD *>(oLockedRect.pBits);
	(*Texture)->UnlockRect(0);

	Attrs->size.width = info.Width;
	Attrs->size.height = info.Height;
	Attrs->format = static_cast<IMG_FORMAT>(info.ImageFileFormat);
	Attrs->collidedBits = pCollidedBits;

	return TRUE;
}

BOOL DxDirect::CreateFontTexture(LPD3DXFONT * Texture, LPTEXTURE_ATTRIBUTES Attrs)
{
	if (Attrs == NULL)
	{
		Log::e(TAG, TEXT("CreateFontTexture Failure, Attrs Is NULL!\n"));
		return FALSE;
	}

	(*Texture) = NULL;

	HRESULT hResult = D3DXCreateFont(GetDevice(), Attrs->size.height, Attrs->size.width, Attrs->weight, 1, Attrs->isItalic, 0, 0, Attrs->quality, 0, Attrs->faceName.c_str(), Texture);
	if ((*Texture) == NULL)
	{
		Log::e(TAG,
			TEXT("CreateFontTexture Failure, HRESULT: %d, width: %d, height: %d, weight: %d, is-italic: %s, quality: %d, face-name: %s\n"),
			hResult, Attrs->size.width, Attrs->size.height, Attrs->weight, Attrs->isItalic, Attrs->quality, Attrs->faceName.c_str());
		return FALSE;
	}

	return TRUE;
}

BOOL DxDirect::DrawImageTexture(LPDIRECT3DTEXTURE9 Texture, CONST SPRITE_ATTRIBUTES * Attrs)
{
	if (Texture == NULL)
	{
		Log::e(TAG, TEXT("DrawImageTexture Failure, Texture Is NULL!\n"));
		return FALSE;
	}

	if (Attrs == NULL)
	{
		Log::e(TAG, TEXT("DrawImageTexture Failure, Attrs Is NULL!\n"));
		return FALSE;
	}

	Transform(Attrs);
	mVector3.x = Attrs->hotspot.x;
	mVector3.y = Attrs->hotspot.y;

	GetSprite()->Draw(Texture, Attrs->region, &mVector3, 0, 0xFFFFFFFF);
	return TRUE;
}

BOOL DxDirect::DrawFontTexture(LPD3DXFONT Texture, CONST SPRITE_ATTRIBUTES * Attrs)
{
	if (Texture == NULL)
	{
		Log::e(TAG, TEXT("DrawFontTexture Failure, Texture Is NULL!\n"));
		return FALSE;
	}

	if (Attrs == NULL)
	{
		Log::e(TAG, TEXT("DrawFontTexture Failure, Attrs Is NULL!\n"));
		return FALSE;
	}

	Transform(Attrs);

	if (Attrs->isUnicode)
	{
		Texture->DrawTextW(GetSprite(), Attrs->wText.c_str(), -1, Attrs->region, 0, Attrs->color);
	}
	else
	{
		Texture->DrawTextA(GetSprite(), Attrs->aText.c_str(), -1, Attrs->region, 0, Attrs->color);
	}
	
	return TRUE;
}

BOOL DxDirect::DrawLine(CONST D3DXVECTOR2 * VertexList, DWORD Count, TCOLOR Color, FLOAT Width)
{
	LPD3DXLINE line = GetLine();

	line->SetWidth(Width);
	line->Begin();
	line->Draw(VertexList, Count, Color);
	line->End();

	return TRUE;
}

BOOL DxDirect::Transform(CONST SPRITE_ATTRIBUTES * Attrs)
{
	if (Attrs == NULL)
	{
		return FALSE;
	}

	if (!Attrs->isTransform)
	{
		return FALSE;
	}

	D3DXMatrixTranslation(&mTranslation, Attrs->pos.x, Attrs->pos.y, Attrs->zIndex);
	D3DXMatrixRotationZ(&mRotationZ, Attrs->angle);
	D3DXMatrixScaling(&mScaling, Attrs->scale.x, Attrs->scale.y, 1);

	mMatrix = mScaling * mRotationZ * mTranslation;
	GetSprite()->SetTransform(&mMatrix);
	return TRUE;
}

MOVE_WSAD DxDirect::MoveToPos(POSITION * Pos, CONST POSITION * Dest, FLOAT Distance)
{
	MOVE_WSAD moveWsad = MOVE_WSAD::MW_UNDEFINED;

	if (Pos == NULL || Dest == NULL || Distance <= 0)
	{
		return moveWsad;
	}

	mVector2.x = Dest->x - Pos->x;
	mVector2.y = Dest->y - Pos->y;

	D3DXVec2Normalize(&mVector2, &mVector2);
	if (abs(mVector2.x) > abs(mVector2.y))
	{
		moveWsad = (mVector2.x > 0) ? MW_RIGHT : MW_LEFT;
	}
	else
	{
		moveWsad = (mVector2.y > 0) ? MW_DOWN : MW_UP;
	}

	Pos->x += mVector2.x * Distance;
	Pos->y += mVector2.y * Distance;
	return moveWsad;
}

LPDIRECT3D9 DxDirect::GetDirect() CONST
{
	return mDirect;
}

LPDIRECT3DDEVICE9 DxDirect::GetDevice() CONST
{
	return mDevice;
}

LPD3DXSPRITE DxDirect::GetSprite() CONST
{
	return mSprite;
}

LPD3DXLINE DxDirect::GetLine() CONST
{
	return mLine;
}

CONST D3DPRESENT_PARAMETERS * DxDirect::GetParams() CONST
{
	return &mParams;
}
