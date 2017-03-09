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

#ifndef ACTIVITY_H_
#define ACTIVITY_H_

#include "Basic.h"
#include "MvVectorHelper.h"

namespace totoro
{
/**
 * Activity class file
 * 控制游戏元素移动类
 *
 * @author 宋欢 <trotri@yeah.net>
 * @version $Id: Activity.h 1 2015-04-06 19:22:06Z huan.song $
 * @since 1.0
 */
class Activity : public Basic
{
public:
	typedef enum _MOVE_TYPE {
		MT_CURSOR = 1,
		MT_KEYBOARD = 2,
		MT_VECTORS = 3,
		MT_UNDEFINED = 0x7fffffff
	} MOVE_TYPE;

private:
	MOVE_TYPE mMoveType;
	MvVectorHelper * mMvVectorHelper;
	POSITION mCurrPos;
	POSITION mSrcPos;

protected:
	Activity();

public:
	~Activity();

public:
	static Activity * Create(String fileName);
	static Activity * CreateImage(String name, String path);
	static Activity * CreateFont(String name, UINT width, UINT height, UINT weight, BOOL isItalic, DWORD quality, String faceName);

protected:
	BOOL _Initialize(String fileName);
	BOOL _InitializeImage(String name, String path);
	BOOL _InitializeFont(String name, UINT width, UINT height, UINT weight, BOOL isItalic, DWORD quality, String faceName);

public:
	BOOL Update();

public:
	virtual BOOL UpdateByCursor();
	virtual BOOL UpdateByAsyncKeyboard();
	virtual BOOL UpdateByVectors();

public:
	MOVE_TYPE GetMoveType() CONST;
	BOOL SetMoveType(MOVE_TYPE moveType);
	MvVectorHelper * GetMvVectorHelper() CONST;
	BOOL SetMvVectorHelper(MvVectorHelper * mvVectorHelper);
	FLOAT GetSrcPosX() CONST;
	FLOAT GetSrcPosY() CONST;
	CONST POSITION * GetSrcPos() CONST;
	BOOL SetSrcPos(CONST POSITION * pos);
	virtual BOOL SetSrcPos(FLOAT x, FLOAT y);
};

}

#endif /* !ACTIVITY_H_ */
