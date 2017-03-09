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

#include "Activity.h"

using namespace totoro;

Activity::Activity() : mMoveType(MT_UNDEFINED), mMvVectorHelper(NULL)
{
}

Activity::~Activity()
{
	DELETE_PTR(mMvVectorHelper);
}

Activity * Activity::Create(String fileName)
{
	Activity * result = new Activity;
	if (result && result->_Initialize(fileName))
	{
		return result;
	}

	DELETE_PTR(result);
	return NULL;
}

Activity * Activity::CreateImage(String name, String path)
{
	Activity * result = new Activity;
	if (result && result->_InitializeImage(name, path))
	{
		return result;
	}

	DELETE_PTR(result);
	return NULL;
}

Activity * Activity::CreateFont(String name, UINT width, UINT height, UINT weight, BOOL isItalic, DWORD quality, String faceName)
{
	Activity * result = new Activity;
	if (result && result->_InitializeFont(name, width, height, weight, isItalic, quality, faceName))
	{
		return result;
	}

	DELETE_PTR(result);
	return NULL;
}

BOOL Activity::_Initialize(String fileName)
{
	if (!Basic::_Initialize(fileName))
	{
		return FALSE;
	}

	SetSrcPos(GetPos());
	return TRUE;
}

BOOL Activity::_InitializeImage(String name, String path)
{
	if (!Basic::_InitializeImage(name, path))
	{
		return FALSE;
	}

	SetSrcPos(GetPos());
	return TRUE;
}

BOOL Activity::_InitializeFont(String name, UINT width, UINT height, UINT weight, BOOL isItalic, DWORD quality, String faceName)
{
	if (!Basic::_InitializeFont(name, width, height, weight, isItalic, quality, faceName))
	{
		return FALSE;
	}

	SetSrcPos(GetPos());
	return TRUE;
}

BOOL Activity::Update()
{
	BOOL result = TRUE;

	switch (GetMoveType())
	{
	case MOVE_TYPE::MT_CURSOR:
		result = UpdateByCursor();
		break;
	case MOVE_TYPE::MT_KEYBOARD:
		result = UpdateByAsyncKeyboard();
		break;
	case MOVE_TYPE::MT_VECTORS:
		result = UpdateByVectors();
		break;
	default:
		break;
	}

	return result;
}

BOOL Activity::UpdateByCursor()
{
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		mCurrPos.x = GetPosX();
		mCurrPos.y = GetPosY();
		MOVE_WSAD moveWsad = MoveToPos(&mCurrPos, GetWindow()->GetCursorPos());
		SetMoveWsad(moveWsad);
		return SetPos(&mCurrPos);
	}

	return TRUE;
}

BOOL Activity::UpdateByAsyncKeyboard()
{
	FLOAT distance = GetRefreshIntervalDistance();
	mCurrPos.x = GetPosX();
	mCurrPos.y = GetPosY();

	if (GetAsyncKeyState('W') || GetAsyncKeyState(VK_UP))
	{
		mCurrPos.y -= distance;
		SetMoveWsad(MW_UP);
	}

	if (GetAsyncKeyState('S') || GetAsyncKeyState(VK_DOWN))
	{
		mCurrPos.y += distance;
		SetMoveWsad(MW_DOWN);
	}

	if (GetAsyncKeyState('A') || GetAsyncKeyState(VK_LEFT))
	{
		mCurrPos.x -= distance;
		SetMoveWsad(MW_LEFT);
	}

	if (GetAsyncKeyState('D') || GetAsyncKeyState(VK_RIGHT))
	{
		mCurrPos.x += distance;
		SetMoveWsad(MW_RIGHT);
	}

	return SetPos(&mCurrPos);
}

BOOL Activity::UpdateByVectors()
{
	if (mMvVectorHelper == NULL)
	{
		return FALSE;
	}

	mCurrPos.x = GetPosX();
	mCurrPos.y = GetPosY();
	CONST POSITION * destPos = mMvVectorHelper->GetDestVertex(&mCurrPos);
	if (destPos != NULL)
	{
		MOVE_WSAD moveWsad = MoveToPos(&mCurrPos, destPos);
		SetMoveWsad(moveWsad);
		return SetPos(&mCurrPos);
	}

	return TRUE;
}

Activity::MOVE_TYPE Activity::GetMoveType() CONST
{
	return mMoveType;
}

BOOL Activity::SetMoveType(MOVE_TYPE moveType)
{
	mMoveType = moveType;
	return TRUE;
}

MvVectorHelper * Activity::GetMvVectorHelper() CONST
{
	return mMvVectorHelper;
}

BOOL Activity::SetMvVectorHelper(MvVectorHelper * mvVectorHelper)
{
	if (mvVectorHelper == NULL)
	{
		return FALSE;
	}

	mMvVectorHelper = mvVectorHelper;
	SetPos(mMvVectorHelper->GetFirstVertex());
	return TRUE;
}

FLOAT Activity::GetSrcPosX() CONST
{
	return mSrcPos.x;
}

FLOAT Activity::GetSrcPosY() CONST
{
	return mSrcPos.y;
}

CONST POSITION * Activity::GetSrcPos() CONST
{
	return &mSrcPos;
}

BOOL Activity::SetSrcPos(CONST POSITION * pos)
{
	if (pos == NULL)
	{
		return FALSE;
	}

	return SetSrcPos(pos->x, pos->y);
}

BOOL Activity::SetSrcPos(FLOAT x, FLOAT y)
{
	mSrcPos.x = x;
	mSrcPos.y = y;
	return TRUE;
}
