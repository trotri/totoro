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

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "dx\DxGraphics.h"

namespace totoro
{
/**
 * Texture class file
 * Ã˘Õº¿‡
 *
 * @author ÀŒª∂ <trotri@yeah.net>
 * @version $Id: Texture.h 1 2015-04-02 16:18:06Z huan.song $
 * @since 1.0
 */
class Texture
{
public:
	CONST TCHAR * TAG = TEXT("Texture");

private:
	IGraphics * mGraphics;
	TEXTURE_ATTRIBUTES mAttributes;

protected:
	Texture();

public:
	virtual ~Texture();

public:
	static Texture * CreateImage(String name, String path);
	static Texture * CreateCollider(String name, String path);
	static Texture * CreateFont(String name, UINT width, UINT height, UINT weight, BOOL isItalic, DWORD quality, String faceName);

protected:
	BOOL _InitializeImage(String name, String path);
	BOOL _InitializeCollider(String name, String path);
	BOOL _InitializeFont(String name, UINT width, UINT height, UINT weight, BOOL isItalic, DWORD quality, String faceName);

public:
	IGraphics * GetGraphics() CONST;
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
	CONST DWORD * GetCollidedBits() CONST;
};

}

#endif /* !TEXTURE_H_ */
