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

#ifndef ILAYER_H_
#define ILAYER_H_

#include "INode.h"

namespace totoro
{
/**
 * ILayer class file
 * ²ã½Ó¿Ú
 *
 * @author ËÎ»¶ <trotri@yeah.net>
 * @version $Id: ILayer.h 1 2015-01-30 16:02:06Z huan.song $
 * @since 1.0
 */
class ILayer : public INode
{
public:
	CONST TCHAR * TAG = TEXT("ILayer");

protected:
	ILayer() {}

public:
	virtual ~ILayer() {}

public:
	virtual VOID Show()
	{
		INode * tmp = NULL;
		for (std::list<INode *>::iterator it = mChildren.begin(); it != mChildren.end(); it++)
		{
			tmp = *it;
			if (tmp)
			{
				tmp->ScheduleUpdate();
				tmp->ScheduleDraw();
			}
			else
			{
				Log::w(TAG, TEXT("Show '%s' Has Null Child!\n"), GetName().c_str());
			}
		}

		ScheduleUpdate();
		ScheduleDraw();
	}

	virtual VOID Hide()
	{
		INode * tmp = NULL;
		for (std::list<INode *>::iterator it = mChildren.begin(); it != mChildren.end(); it++)
		{
			tmp = *it;
			if (tmp)
			{
				tmp->UnScheduleUpdate();
				tmp->UnScheduleDraw();
			}
			else
			{
				Log::w(TAG, TEXT("Hide '%s' Has Null Child!\n"), GetName().c_str());
			}
		}

		UnScheduleUpdate();
		UnScheduleDraw();
	}

};

}

#endif /* !ILAYER_H_ */
