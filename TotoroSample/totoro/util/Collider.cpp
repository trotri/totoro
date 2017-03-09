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

#include "Collider.h"

using namespace totoro;

CONST TCHAR * Collider::TAG = TEXT("Collider");

Collider::Collider()
{
}

Collider::~Collider()
{
}

BOOL Collider::IsCollide(CONST POSITION * pos, CONST RECT4P * box)
{
	if (pos == NULL || box == NULL)
	{
		return FALSE;
	}

	FLOAT minX = box->leftTop.x;
	FLOAT maxX = box->rightBottom.x;
	FLOAT minY = box->leftTop.y;
	FLOAT maxY = box->rightBottom.y;

	if (pos->x >= minX && pos->x <= maxX && pos->y >= minY && pos->y <= maxY)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL Collider::IsCollide(CONST RECT4P * box1, CONST RECT4P * box2, BOOL isMutual)
{
	if (box1 == NULL || box2 == NULL)
	{
		return FALSE;
	}

	FLOAT minX = box2->leftTop.x;
	FLOAT maxX = box2->rightBottom.x;
	FLOAT minY = box2->leftTop.y;
	FLOAT maxY = box2->rightBottom.y;

	if (box1->leftTop.x >= minX && box1->leftTop.x <= maxX && box1->leftTop.y >= minY && box1->leftTop.y <= maxY)
	{
		return TRUE;
	}

	if (box1->leftBottom.x >= minX && box1->leftBottom.x <= maxX && box1->leftBottom.y >= minY && box1->leftBottom.y <= maxY)
	{
		return TRUE;
	}

	if (box1->rightTop.x >= minX && box1->rightTop.x <= maxX && box1->rightTop.y >= minY && box1->rightTop.y <= maxY)
	{
		return TRUE;
	}

	if (box1->rightBottom.x >= minX && box1->rightBottom.x <= maxX && box1->rightBottom.y >= minY && box1->rightBottom.y <= maxY)
	{
		return TRUE;
	}

	if (isMutual)
	{
		return IsCollide(box2, box1, FALSE);
	}

	return FALSE;
}

BOOL Collider::IsCollide(CONST POSITION * pos, Texture * texture, BOOL isAllowOutside)
{
	if (pos == NULL || texture == NULL)
	{
		Log::e(TAG, TEXT("IsCollide Pos or Texture Is NULL!\n"));
		return FALSE;
	}

	CONST DWORD * collidedBits = texture->GetCollidedBits();
	if (collidedBits == NULL)
	{
		Log::e(TAG, TEXT("IsCollide CollidedBits Is NULL!\n"));
		return FALSE;
	}

	CONST RECTWH * size = texture->GetSize();
	if (size == NULL)
	{
		Log::e(TAG, TEXT("IsCollide Size Is NULL!\n"));
		return FALSE;
	}

	if (size->width <= 0)
	{
		Log::e(TAG, TEXT("IsCollide Width Less Or Equal Than Zero!\n"));
		return FALSE;
	}

	if (size->height <= 0)
	{
		Log::e(TAG, TEXT("IsCollide Height Less Or Equal Than Zero!\n"));
		return FALSE;
	}

	if (pos->x < 0 || pos->x > size->width || pos->y < 0 || pos->y > size->height)
	{
		if (isAllowOutside)
		{
			Log::d(TAG, TEXT("IsCollide Outside And Is Allowed!\n"));
			return FALSE;
		}
		else
		{
			Log::d(TAG, TEXT("IsCollide Outside But Is Denied!\n"));
			return TRUE;
		}
	}

	ULONG index = static_cast<ULONG>(pos->y) * size->width + static_cast<ULONG>(pos->x);
	DWORD dwColor = collidedBits[index];
	if (dwColor == FINAL_COLLIDED_COLOR)
	{
		Log::d(TAG, TEXT("IsCollide Inside And Have a Collision!\n"));
		return TRUE;
	}

	// Log::d(TAG, TEXT("IsCollide Inside And No Collision!\n"));
	return FALSE;
}

BOOL Collider::IsEqual(CONST POSITION * pos1, CONST POSITION * pos2)
{
	FLOAT distance = GetDistance(pos1, pos2);
	if (distance >= 0 && distance < FINAL_POSITION_EQUAL_DISTANCE)
	{
		return TRUE;
	}

	return FALSE;
}

FLOAT Collider::GetDistance(CONST POSITION * pos1, CONST POSITION * pos2)
{
	if (pos1 == NULL || pos2 == NULL)
	{
		return -1;
	}

	FLOAT distance = sqrt(pow((pos1->x - pos2->x), 2.0f) + pow((pos1->y - pos2->y), 2.0f));
	return distance;
}
