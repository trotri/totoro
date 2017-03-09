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

#ifndef IGRAPHICS_H_
#define IGRAPHICS_H_

#include "..\ap\Defs.h"

namespace totoro
{
/**
 * IGraphics class file
 * 图形绘制接口
 *
 * @author 宋欢 <trotri@yeah.net>
 * @version $Id: IGraphics.h 1 2015-04-02 16:04:06Z huan.song $
 * @since 1.0
 */
class IGraphics
{
protected:
	TEXTURE_ID mAutoIncrementId;

public:
	IGraphics() : mAutoIncrementId(0) {}
	virtual ~IGraphics()
	{
		Clear();
	}

public:
	TEXTURE_ID GetAutoIncrementId()
	{
		return GetAutoIncrementId(FALSE);
	}

	TEXTURE_ID GetAutoIncrementId(BOOL autoIncrement)
	{
		if (autoIncrement)
		{
			++mAutoIncrementId;
		}

		return mAutoIncrementId;
	}

public:
	virtual BOOL Clear()
	{
		return FALSE;
	}

public:
	virtual BOOL BeginScene() = 0;
	virtual BOOL EndScene() = 0;
	virtual BOOL CreateImage(__inout LPTEXTURE_ATTRIBUTES Attrs) = 0;
	virtual BOOL CreateCollider(__inout LPTEXTURE_ATTRIBUTES Attrs) = 0;
	virtual BOOL CreateFont(__inout LPTEXTURE_ATTRIBUTES Attrs) = 0;
	virtual BOOL DrawImage(__in TEXTURE_ID Id, __in CONST SPRITE_ATTRIBUTES * Attrs) = 0;
	virtual BOOL DrawFont(__in TEXTURE_ID Id, __in CONST SPRITE_ATTRIBUTES * Attrs) = 0;
	virtual BOOL DrawLine(__in CONST POSITION * Begin, __in CONST POSITION * End, __in TCOLOR Color, __in FLOAT Width) = 0;
	virtual MOVE_WSAD MoveToPos(__inout POSITION * Pos, __in CONST POSITION * Dest, __in FLOAT Distance) = 0;
};

}

#endif /* !IGRAPHICS_H_ */
