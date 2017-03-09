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

#include "Line2p.h"

using namespace totoro;

Line2p::Line2p() : mColor(0xFF000000), mWidth(1)
{
	mGraphics = DxGraphics::GetInstance();
}

Line2p::~Line2p()
{
}

BOOL Line2p::Draw()
{
	return mGraphics->DrawLine(GetBegin(), GetEnd(), GetColor(), GetWidth());
}

CONST POSITION * Line2p::GetBegin() CONST
{
	return &mBegin;
}

BOOL Line2p::SetBegin(FLOAT x, FLOAT y)
{
	mBegin.x = x;
	mBegin.y = y;
	return TRUE;
}

CONST POSITION * Line2p::GetEnd() CONST
{
	return &mEnd;
}

BOOL Line2p::SetEnd(FLOAT x, FLOAT y)
{
	mEnd.x = x;
	mEnd.y = y;
	return TRUE;
}

TCOLOR Line2p::GetColor() CONST
{
	return mColor;
}

BOOL Line2p::SetColor(TCOLOR color)
{
	mColor = color;
	return TRUE;
}

FLOAT Line2p::GetWidth() CONST
{
	return mWidth;
}

BOOL Line2p::SetWidth(FLOAT width)
{
	if (width < 0)
	{
		return FALSE;
	}

	mWidth = width;
	return TRUE;
}

MOVE_WSAD Line2p::MoveToPos(POSITION * pos, CONST POSITION * dest, FLOAT distance)
{
	return mGraphics->MoveToPos(pos, dest, distance);
}
