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

#include "TextureRegistry.h"

using namespace totoro;

CONST TCHAR * TextureRegistry::TAG = TEXT("TextureRegistry");
std::map<String, Texture *> TextureRegistry::sImageTextures;
std::map<String, Texture *> TextureRegistry::sColliderTextures;
std::map<String, Texture *> TextureRegistry::sFontTextures;

TextureRegistry::TextureRegistry()
{
}

TextureRegistry::~TextureRegistry()
{
}

Texture * TextureRegistry::GetImage(String name)
{
	return sImageTextures[name];
}

Texture * TextureRegistry::GetCollider(String name)
{
	return sColliderTextures[name];
}

Texture * TextureRegistry::GetFont(String name)
{
	return sFontTextures[name];
}

Texture * TextureRegistry::AddImage(String name, String path)
{
	Texture * result = GetImage(name);
	if (result == NULL)
	{
		result = Texture::CreateImage(name, path);
		if (result != NULL)
		{
			Log::d(TAG, TEXT("AddImage '%s' Create Image Success!\n"), name.c_str());
			sImageTextures[name] = result;
		}
	}

	return result;
}

Texture * TextureRegistry::AddCollider(String name, String path)
{
	Texture * result = GetCollider(name);
	if (result == NULL)
	{
		result = Texture::CreateCollider(name, path);
		if (result != NULL)
		{
			sColliderTextures.insert(make_pair(name, result));
		}
	}

	return result;
}

Texture * TextureRegistry::AddFont(String name, UINT width, UINT height, UINT weight, BOOL isItalic, DWORD quality, String faceName)
{
	Texture * result = GetFont(name);
	if (result == NULL)
	{
		result = Texture::CreateFont(name, width, height, weight, isItalic, quality, faceName);
		if (result != NULL)
		{
			sFontTextures.insert(make_pair(name, result));
		}
	}

	return result;
}

VOID TextureRegistry::ClearImages()
{
	Texture * tmp;

	for (std::map<String, Texture *>::iterator it = sImageTextures.begin(); it != sImageTextures.end(); it++)
	{
		tmp = it->second;
		DELETE_PTR(tmp);
	}

	sImageTextures.clear();
}

VOID TextureRegistry::ClearColliders()
{
	Texture * tmp;

	for (std::map<String, Texture *>::iterator it = sColliderTextures.begin(); it != sColliderTextures.end(); it++)
	{
		tmp = it->second;
		DELETE_PTR(tmp);
	}

	sColliderTextures.clear();
}

VOID TextureRegistry::ClearFonts()
{
	Texture * tmp;

	for (std::map<String, Texture *>::iterator it = sFontTextures.begin(); it != sFontTextures.end(); it++)
	{
		tmp = it->second;
		DELETE_PTR(tmp);
	}

	sFontTextures.clear();
}

VOID TextureRegistry::ClearAll()
{
	ClearImages();
	ClearColliders();
	ClearFonts();
}
