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

#ifndef TEXTURE_REGISTRY_H_
#define TEXTURE_REGISTRY_H_

#include "Texture.h"

namespace totoro
{
/**
 * TextureRegistry class file
 * ÌùÍ¼¼Ä´æÀà
 *
 * @author ËÎ»¶ <trotri@yeah.net>
 * @version $Id: TextureRegistry.h 1 2015-04-04 16:18:06Z huan.song $
 * @since 1.0
 */
class TextureRegistry
{
public:
	static CONST TCHAR * TAG;

private:
	static std::map<String, Texture *> sImageTextures;
	static std::map<String, Texture *> sColliderTextures;
	static std::map<String, Texture *> sFontTextures;

protected:
	TextureRegistry();
	virtual ~TextureRegistry();

public:
	static Texture * GetImage(String name);
	static Texture * GetCollider(String name);
	static Texture * GetFont(String name);
	static Texture * AddImage(String name, String path);
	static Texture * AddCollider(String name, String path);
	static Texture * AddFont(String name, UINT width, UINT height, UINT weight, BOOL isItalic, DWORD quality, String faceName);
	static VOID ClearImages();
	static VOID ClearColliders();
	static VOID ClearFonts();
	static VOID ClearAll();
};

}

#endif /* !TEXTURE_REGISTRY_H_ */
