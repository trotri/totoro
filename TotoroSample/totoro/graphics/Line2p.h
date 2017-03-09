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

#ifndef LINE2P_H_
#define LINE2P_H_

#include "dx\DxGraphics.h"

namespace totoro
{
/**
 * Line2p class file
 * 2点直线绘制类
 *
 * @author 宋欢 <trotri@yeah.net>
 * @version $Id: Line2p.h 1 2015-04-06 19:22:06Z huan.song $
 * @since 1.0
 */
class Line2p
{
public:
	CONST TCHAR * TAG = TEXT("Line2p");

private:
	IGraphics * mGraphics;
	POSITION mBegin;
	POSITION mEnd;
	TCOLOR mColor;
	FLOAT mWidth;

protected:
	Line2p();

public:
	virtual ~Line2p();

public:
	BOOL Draw();

public:
	CONST POSITION * GetBegin() CONST;
	BOOL SetBegin(FLOAT x, FLOAT y);
	CONST POSITION * GetEnd() CONST;
	BOOL SetEnd(FLOAT x, FLOAT y);
	TCOLOR GetColor() CONST;
	BOOL SetColor(TCOLOR color);
	FLOAT GetWidth() CONST;
	BOOL SetWidth(FLOAT width);
	MOVE_WSAD MoveToPos(POSITION * pos, CONST POSITION * dest, FLOAT distance);
};

}

#endif /* !LINE2P_H_ */
