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

#ifndef DX_GRAPHICS_H_
#define DX_GRAPHICS_H_

#include "..\IGraphics.h"
#include "DxDirect.h"

namespace totoro
{
/**
 * DxGraphics class file
 * Direct3DÕº–ŒªÊ÷∆¿‡
 *
 * @author ÀŒª∂ <trotri@yeah.net>
 * @version $Id: DxGraphics.h 1 2015-04-02 16:04:06Z huan.song $
 * @since 1.0
 */
class DxGraphics : public IGraphics, public ISingleton<DxGraphics>
{
public:
	CONST TCHAR * TAG = TEXT("DxGraphics");

private:
	DxDirect * mDirect;
	std::map<TEXTURE_ID, LPDIRECT3DTEXTURE9> mImageTextures;
	std::map<TEXTURE_ID, LPDIRECT3DTEXTURE9> mColliderTextures;
	std::map<TEXTURE_ID, LPD3DXFONT> mFontTextures;
	D3DXVECTOR2 mVertexes[2];

public:
	DxGraphics();
	virtual ~DxGraphics();

public:
	BOOL Clear();

public:
	BOOL BeginScene();
	BOOL EndScene();
	BOOL CreateImage(__inout LPTEXTURE_ATTRIBUTES Attrs);
	BOOL CreateCollider(__inout LPTEXTURE_ATTRIBUTES Attrs);
	BOOL CreateFont(__inout LPTEXTURE_ATTRIBUTES Attrs);
	BOOL DrawImage(__in TEXTURE_ID Id, __in CONST SPRITE_ATTRIBUTES * Attrs);
	BOOL DrawFont(__in TEXTURE_ID Id, __in CONST SPRITE_ATTRIBUTES * Attrs);
	BOOL DrawLine(__in CONST POSITION * Begin, __in CONST POSITION * End, __in TCOLOR Color, __in FLOAT Width);
	MOVE_WSAD MoveToPos(__inout POSITION * Pos, __in CONST POSITION * Dest, __in FLOAT Distance);
};

}

#endif /* !DX_GRAPHICS_H_ */
