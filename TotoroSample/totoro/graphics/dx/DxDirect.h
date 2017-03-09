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

#ifndef DX_DIRECT_H_
#define DX_DIRECT_H_

#include "..\..\ap\Defs.h"
#include "..\..\ap\Window.h"

/**
 * 附加依赖项：d3d9.lib、d3dx9.lib
 * 包含目录：...\Microsoft DirectX SDK June 2010\Include
 * 库目录：...\Microsoft DirectX SDK June 2010\Lib\x86
 */

#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

namespace totoro
{
/**
 * DxDirect class file
 * Direct3D图形绘制类，初始化D3D对象和设备、创建和绘制贴图、变换精灵
 *
 * @author 宋欢 <trotri@yeah.net>
 * @version $Id: DxDirect.h 1 2015-04-02 16:04:06Z huan.song $
 * @since 1.0
 */
class DxDirect : public ISingleton<DxDirect>
{
public:
	CONST TCHAR * TAG = TEXT("DxDirect");

private:
	LPDIRECT3D9 mDirect;
	LPDIRECT3DDEVICE9 mDevice;
	LPD3DXSPRITE mSprite;
	LPD3DXLINE mLine;
	D3DPRESENT_PARAMETERS mParams;
	D3DXMATRIXA16 mMatrix;
	D3DXMATRIXA16 mTranslation;
	D3DXMATRIXA16 mRotationZ;
	D3DXMATRIXA16 mScaling;
	D3DXVECTOR2 mVector2;
	D3DXVECTOR3 mVector3;

public:
	DxDirect();
	virtual ~DxDirect();

protected:
	BOOL _Initialize();
	BOOL _Clear();

public:
	BOOL BeginScene();
	BOOL EndScene();
	BOOL CreateImageTexture(__out LPDIRECT3DTEXTURE9 * Texture, __inout LPTEXTURE_ATTRIBUTES Attrs);
	BOOL CreateColliderTexture(__out LPDIRECT3DTEXTURE9 * Texture, __inout LPTEXTURE_ATTRIBUTES Attrs);
	BOOL CreateFontTexture(__out LPD3DXFONT * Texture, __inout LPTEXTURE_ATTRIBUTES Attrs);
	BOOL DrawImageTexture(__in LPDIRECT3DTEXTURE9 Texture, __in CONST SPRITE_ATTRIBUTES * Attrs);
	BOOL DrawFontTexture(__in LPD3DXFONT Texture, __in CONST SPRITE_ATTRIBUTES * Attrs);
	BOOL DrawLine(__in CONST D3DXVECTOR2 * VertexList, __in DWORD Count, __in TCOLOR Color, __in FLOAT Width);
	BOOL Transform(__in CONST SPRITE_ATTRIBUTES * Attrs);
	MOVE_WSAD MoveToPos(__inout POSITION * Pos, __in CONST POSITION * Dest, __in FLOAT Distance);

protected:
	LPDIRECT3D9 GetDirect() CONST;
	LPDIRECT3DDEVICE9 GetDevice() CONST;
	LPD3DXSPRITE GetSprite() CONST;
	LPD3DXLINE GetLine() CONST;
	CONST D3DPRESENT_PARAMETERS * GetParams() CONST;
};

}

#endif /* !DX_DIRECT_H_ */
