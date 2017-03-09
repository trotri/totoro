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

#include "Texture.h"

using namespace totoro;

Texture::Texture()
{
	mGraphics = DxGraphics::GetInstance();
}

Texture::~Texture()
{
}

Texture * Texture::CreateImage(String name, String path)
{
	Texture * result = new Texture;
	if (result && result->_InitializeImage(name, path))
	{
		return result;
	}

	DELETE_PTR(result);
	return NULL;
}

Texture * Texture::CreateCollider(String name, String path)
{
	Texture * result = new Texture;
	if (result && result->_InitializeCollider(name, path))
	{
		return result;
	}

	DELETE_PTR(result);
	return NULL;
}

Texture * Texture::CreateFont(String name, UINT width, UINT height, UINT weight, BOOL isItalic, DWORD quality, String faceName)
{
	Texture * result = new Texture;
	if (result && result->_InitializeFont(name, width, height, weight, isItalic, quality, faceName))
	{
		return result;
	}

	DELETE_PTR(result);
	return NULL;
}

BOOL Texture::_InitializeImage(String name, String path)
{
	if (name.IsEmpty())
	{
		Log::e(TAG, TEXT("_InitializeImage Failure, Name Is Empty!\n"));
		return FALSE;
	}

	mAttributes.type = GRAPHICS_TYPE::GT_IMAGE;
	mAttributes.name = name;
	mAttributes.path = path;

	if (!mGraphics->CreateImage(&mAttributes))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL Texture::_InitializeCollider(String name, String path)
{
	if (name.IsEmpty())
	{
		Log::e(TAG, TEXT("_InitializeCollider Failure, Name Is Empty!\n"));
		return FALSE;
	}

	mAttributes.type = GRAPHICS_TYPE::GT_COLLIDER;
	mAttributes.name = name;
	mAttributes.path = path;

	if (!mGraphics->CreateCollider(&mAttributes))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL Texture::_InitializeFont(String name, UINT width, UINT height, UINT weight, BOOL isItalic, DWORD quality, String faceName)
{
	if (name.IsEmpty())
	{
		Log::e(TAG, TEXT("_InitializeFont Failure, Name Is Empty!\n"));
		return FALSE;
	}

	mAttributes.type = GRAPHICS_TYPE::GT_FONT;
	mAttributes.name = name;
	mAttributes.size.width = width;
	mAttributes.size.height = height;
	mAttributes.weight = weight;
	mAttributes.isItalic = isItalic;
	mAttributes.quality = quality;
	mAttributes.faceName = faceName;

	if (!mGraphics->CreateFont(&mAttributes))
	{
		return FALSE;
	}

	return TRUE;
}

IGraphics * Texture::GetGraphics() CONST
{
	return mGraphics;
}

GRAPHICS_TYPE Texture::GetType() CONST
{
	return mAttributes.type;
}

TEXTURE_ID Texture::GetId() CONST
{
	return mAttributes.id;
}

String Texture::GetName() CONST
{
	return mAttributes.name;
}

String Texture::GetPath() CONST
{
	return mAttributes.path;
}

UINT Texture::GetWidth() CONST
{
	return mAttributes.size.width;
}

UINT Texture::GetHeight() CONST
{
	return mAttributes.size.height;
}

CONST RECTWH * Texture::GetSize() CONST
{
	return &mAttributes.size;
}

IMG_FORMAT Texture::GetFormat() CONST
{
	return mAttributes.format;
}

UINT Texture::GetWeight() CONST
{
	return mAttributes.weight;
}

BOOL Texture::IsItalic() CONST
{
	return mAttributes.isItalic;
}

DWORD Texture::GetQuality() CONST
{
	return mAttributes.quality;
}

String Texture::GetFaceName() CONST
{
	return mAttributes.faceName;
}

CONST DWORD * Texture::GetCollidedBits() CONST
{
	return mAttributes.collidedBits;
}
