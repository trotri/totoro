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

#include "MvVectorHelper.h"

using namespace totoro;

MvVectorHelper::MvVectorHelper() : mSize(0), mIndex(0), mDelay(0), mIsBackward(FALSE), mIsNeedBackward(TRUE)
{
}

MvVectorHelper::~MvVectorHelper()
{
	mMvVectors.clear();
}

MvVectorHelper * MvVectorHelper::Create(String fileName)
{
	MvVectorHelper * result = new MvVectorHelper;
	if (result && result->_Initialize(fileName))
	{
		return result;
	}

	DELETE_PTR(result);
	return NULL;
}

BOOL MvVectorHelper::_Initialize(String fileName)
{
	if (fileName.IsEmpty())
	{
		return FALSE;
	}

	std::map<String, std::vector<std::map<String, String>>> data = Text::GetCfgs(fileName);
	std::vector<std::map<String, String>> rows = data[TEXT("vector")];
	if (rows.empty())
	{
		return FALSE;
	}

	String sStartX, sStartY, sEndX, sEndY, sDelay;
	std::map<String, String> row;
	for (std::vector<std::map<String, String>>::iterator it = rows.begin(); it != rows.end(); it++)
	{
		row = (*it);

		sStartX = row[TEXT("start_x")];
		sStartY = row[TEXT("start_y")];
		sEndX   = row[TEXT("end_x")];
		sEndY   = row[TEXT("end_y")];
		sDelay  = row[TEXT("delay")];

		if (sStartX.IsEmpty() || sStartY.IsEmpty() || sEndX.IsEmpty() || sEndY.IsEmpty() || sDelay.IsEmpty())
		{
			continue;
		}

		MV_VECTOR mvVector;

		mvVector.start.x = sStartX.ToFloat();
		mvVector.start.y = sStartY.ToFloat();
		mvVector.end.x   = sEndX.ToFloat();
		mvVector.end.y   = sEndY.ToFloat();
		mvVector.delay   = sDelay.ToFloat();

		mMvVectors.push_back(mvVector);
	}

	if (mMvVectors.empty())
	{
		return FALSE;
	}

	mSize = mMvVectors.size();
	mDestVertex = mMvVectors[0].start;
	return TRUE;
}

CONST POSITION * MvVectorHelper::GetDestVertex(CONST POSITION * currPos)
{
	if (currPos == NULL)
	{
		return NULL;
	}

	if (!IsNeedBackward() && mIsBackward)
	{
		return NULL;
	}

	if (mIsBackward)
	{
		if (mIndex < 0)
		{
			mIndex = 0;
			mIsBackward = FALSE;
			return NULL;
		}
	}
	else
	{
		if (mIndex >= (INT) mSize)
		{
			mIndex = mSize - 1;
			mIsBackward = TRUE;
			return NULL;
		}
	}

	if (Collider::IsEqual(currPos, &mDestVertex))
	{
		mDestVertex = mIsBackward ? mMvVectors[mIndex].start : mMvVectors[mIndex].end;
	}

	if (mIsBackward)
	{
		if (mMvVectors[mIndex].delay > 0)
		{
			if (mDelay < mMvVectors[mIndex].delay)
			{
				mDelay += Window::GetInstance()->GetRefreshInterval();
				return NULL;
			}
		}
	}

	if (Collider::IsEqual(currPos, &mDestVertex))
	{
		if (!mIsBackward)
		{
			if (mMvVectors[mIndex].delay > 0)
			{
				if (mDelay < mMvVectors[mIndex].delay)
				{
					mDelay += Window::GetInstance()->GetRefreshInterval();
					return NULL;
				}
			}
		}

		mDelay = 0;
		mIsBackward ? mIndex-- : mIndex++;
		return NULL;
	}

	return &mDestVertex;
}

CONST POSITION * MvVectorHelper::GetFirstVertex() CONST
{
	if (mMvVectors.empty())
	{
		return NULL;
	}

	return &mMvVectors[0].start;
}

BOOL MvVectorHelper::IsNeedBackward() CONST
{
	return mIsNeedBackward;
}

BOOL MvVectorHelper::SetNeedBackward(BOOL isNeedBackward)
{
	mIsNeedBackward = isNeedBackward;
	return TRUE;
}

BOOL MvVectorHelper::Reset()
{
	mIndex = 0;
	mDelay = 0;
	mIsBackward = FALSE;
	mDestVertex = mMvVectors[0].start;
	return TRUE;
}
