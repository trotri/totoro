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

#ifndef DEFS_H_
#define DEFS_H_

#include "Macros.h"
#include "String.h"
#include "ISingleton.h"
#include "Log.h"
#include "Console.h"

#include <tchar.h>
#include <map>
#include <list>
#include <vector>

namespace totoro
{

#ifndef POSITION_H_
#define POSITION_H_

typedef struct tagPOSITION
{
	FLOAT x;
	FLOAT y;
	tagPOSITION() : x(0), y(0) {}
	tagPOSITION(FLOAT x, FLOAT y) : x(x), y(y) {}
} POSITION, *PPOSITION, *LPPOSITION;

#endif // !POSITION_H_

#ifndef RECT4P_H_
#define RECT4P_H_

typedef struct tagRECT4P
{
	POSITION leftTop;
	POSITION rightTop;
	POSITION leftBottom;
	POSITION rightBottom;
} RECT4P, *PRECT4P, *LPRECT4P;

#endif // !RECT4P_H_

#ifndef RECTXY_H_
#define RECTXY_H_

typedef struct tagRECTXY
{
	INT x;
	INT y;
	tagRECTXY() : x(0), y(0) {}
	tagRECTXY(INT x, INT y) : x(x), y(y) {}
} RECTXY, *PRECTXY, *LPRECTXY;

#endif // !RECTXY_H_

#ifndef RECTWH_H_
#define RECTWH_H_

typedef struct tagRECTWH
{
	UINT width;
	UINT height;
	tagRECTWH() : width(0), height(0) {}
	tagRECTWH(UINT width, UINT height) : width(width), height(height) {}
} RECTWH, *PRECTWH, *LPRECTWH;

#endif // !RECTWH_H_

#ifndef SCALE_H_
#define SCALE_H_

typedef struct tagSCALE
{
	FLOAT x;
	FLOAT y;
	tagSCALE() : x(1), y(1) {}
	tagSCALE(FLOAT x, FLOAT y) : x(x), y(y) {}
} SCALE, *PSCALE, *LPSCALE;

#endif // !SCALE_H_

#ifndef GRAPHICS_TYPE_H_
#define GRAPHICS_TYPE_H_

typedef enum _GRAPHICS_TYPE
{
	GT_IMAGE     = 1,
	GT_FONT      = 2,
	GT_COLLIDER  = 3,
	GT_UNDEFINED = 0x7fffffff,
} GRAPHICS_TYPE;

#endif // !GRAPHICS_TYPE_H_

#ifndef IMG_FORMAT_H_
#define IMG_FORMAT_H_

typedef enum _IMG_FORMAT
{
	FMT_BMP = 0,
	FMT_JPG = 1,
	FMT_TGA = 2,
	FMT_PNG = 3,
	FMT_DDS = 4,
	FMT_PPM = 5,
	FMT_DIB = 6,
	FMT_HDR = 7,
	FMT_PFM = 8,
	FMT_FORCE_DWORD = 0x7fffffff,
} IMG_FORMAT;

#endif // !IMG_FORMAT_H_

#ifndef MOVE_WSAD_H_
#define MOVE_WSAD_H_

typedef enum _MOVE_WSAD
{
	MW_UP        = 1,
	MW_DOWN      = 2,
	MW_LEFT      = 3,
	MW_RIGHT     = 4,
	MW_UNDEFINED = 0x7fffffff,
} MOVE_WSAD;

#endif // !MOVE_WSAD_H_

#ifndef BUTTON_STATUS_H_
#define BUTTON_STATUS_H_

typedef enum _BUTTON_STATUS
{
	BS_NORMAL       = 1,
	BS_ONMOUSEOVER  = 2,
	BS_ONMOUSECLICK = 3,
	BS_DISABLED     = 4,
	BS_UNDEFINED    = 0x7fffffff
} BUTTON_STATUS;

#endif // !BUTTON_STATUS_H_

#ifndef TEXTURE_ATTRIBUTES_H_
#define TEXTURE_ATTRIBUTES_H_

typedef struct tagTEXTURE_ATTRIBUTES
{
	GRAPHICS_TYPE type;
	TEXTURE_ID id;
	String name;
	String path;
	RECTWH size;
	IMG_FORMAT format;
	UINT weight;
	BOOL isItalic;
	DWORD quality;
	String faceName;
	DWORD * collidedBits;
	tagTEXTURE_ATTRIBUTES() : type(GT_UNDEFINED), id(0), format(FMT_FORCE_DWORD), weight(0), isItalic(FALSE), quality(0), collidedBits(NULL) {}
	~tagTEXTURE_ATTRIBUTES() { DELETE_PTR(collidedBits); }
} TEXTURE_ATTRIBUTES, *PTEXTURE_ATTRIBUTES, *LPTEXTURE_ATTRIBUTES;

#endif // !TEXTURE_ATTRIBUTES_H_

#ifndef SPRITE_ATTRIBUTES_H_
#define SPRITE_ATTRIBUTES_H_

typedef struct tagSPRITE_ATTRIBUTES
{
	POSITION hotspot;
	RECT * region;
	SCALE scale;
	FLOAT angle;
	POSITION pos;
	FLOAT zIndex;
	WSTRING wText;
	ASTRING aText;
	BOOL isUnicode;
	TCOLOR color;
	BOOL isTransform;
	tagSPRITE_ATTRIBUTES() : region(NULL), angle(0), zIndex(FINAL_Z_INDEX_MIN), wText(L""), aText(""), isUnicode(TRUE), color(0xFF000000), isTransform(TRUE) {}
	~tagSPRITE_ATTRIBUTES() { DELETE_PTR(region); }
} SPRITE_ATTRIBUTES, *PSPRITE_ATTRIBUTES, *LPSPRITE_ATTRIBUTES;

#endif // !SPRITE_ATTRIBUTES_H_

}

#endif /* !DEFS_H_ */
