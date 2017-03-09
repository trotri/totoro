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

#ifndef INODE_H_
#define INODE_H_

#include "Defs.h"
#include "Window.h"

namespace totoro
{
/**
 * INode class file
 * 角色接口
 *
 * @author 宋欢 <trotri@yeah.net>
 * @version $Id: INode.h 1 2015-01-30 16:00:06Z huan.song $
 * @since 1.0
 */
class INode
{
public:
	CONST TCHAR * TAG = TEXT("INode");

protected:
	String mName;
	INode * mParent;
	std::list<INode *> mChildren;
	BOOL mIsUpdate;
	BOOL mIsDraw;
	BOOL mIsPause;
	BOOL mIsPropagationListener;
	Window * mWindow;

protected:
	INode() : mName(TEXT("")), mParent(NULL), mIsUpdate(FALSE), mIsDraw(TRUE), mIsPause(FALSE), mIsPropagationListener(TRUE)
	{
		mWindow = Window::GetInstance();
		mChildren.clear();
	}

public:
	virtual ~INode()
	{
		ClearChildren();
	}

protected:
	/**
	 * 初始化，需子类实现该方法
	 */
	virtual BOOL _Initialize()
	{
		return FALSE;
	}

public:
	virtual BOOL Update()
	{
		return TRUE;
	}

	virtual BOOL Draw()
	{
		return TRUE;
	}

public:
	BOOL Visit()
	{
		if (IsUpdate() && !IsPause())
		{
			if (!Update())
			{
				Console::e(TEXT("%s::Visit '%s' Update Failure!\n"), TAG, GetName().c_str());
			}
			else
			{
				Console::d(TEXT("%s::Visit '%s' Update Success!\n"), TAG, GetName().c_str());
			}
		}

		if (IsDraw())
		{
			if (!Draw())
			{
				Console::e(TEXT("%s::Visit '%s' Draw Failure!\n"), TAG, GetName().c_str());
				return FALSE;
			}
			else
			{
				Console::d(TEXT("%s::Visit '%s' Draw Success!\n"), TAG, GetName().c_str());
			}
		}

		if (mChildren.empty())
		{
			Console::d(TEXT("%s::Visit '%s' Children Is Empty!\n"), TAG, GetName().c_str());
			return TRUE;
		}

		INode * tmp = NULL;
		for (std::list<INode *>::iterator it = mChildren.begin(); it != mChildren.end(); it++)
		{
			tmp = *it;
			if (tmp)
			{
				tmp->Visit();
			}
			else
			{
				Console::w(TEXT("%s::Visit '%s' Has Null Child!\n"), TAG, GetName().c_str());
			}
		}

		return TRUE;
	}

	String GetName() CONST
	{
		return mName;
	}

	BOOL SetName(String name)
	{
		if (name.IsEmpty())
		{
			return FALSE;
		}

		mName = name;
		return TRUE;
	}

	BOOL IsUpdate() CONST
	{
		return mIsUpdate;
	}

	VOID ScheduleUpdate()
	{
		mIsUpdate = TRUE;
	}

	VOID UnScheduleUpdate()
	{
		mIsUpdate = FALSE;
	}

	BOOL IsDraw() CONST
	{
		return mIsDraw;
	}

	VOID ScheduleDraw()
	{
		mIsDraw = TRUE;
	}

	VOID UnScheduleDraw()
	{
		mIsDraw = FALSE;
	}

	BOOL IsPause() CONST
	{
		return mIsPause;
	}

	BOOL Resume()
	{
		mIsPause = FALSE;

		INode * tmp = NULL;
		for (std::list<INode *>::iterator it = mChildren.begin(); it != mChildren.end(); it++)
		{
			tmp = *it;
			if (tmp)
			{
				tmp->Resume();
			}
		}

		return TRUE;
	}

	BOOL Pause()
	{
		mIsPause = TRUE;

		INode * tmp = NULL;
		for (std::list<INode *>::iterator it = mChildren.begin(); it != mChildren.end(); it++)
		{
			tmp = *it;
			if (tmp)
			{
				tmp->Pause();
			}
		}

		return TRUE;
	}

	BOOL SetParent(INode * node)
	{
		if (node == NULL)
		{
			return FALSE;
		}

		mParent = node;
		return TRUE;
	}

	std::list<INode *> GetChildren() CONST
	{
		return mChildren;
	}

	BOOL AddChild(INode * node)
	{
		if (node == NULL)
		{
			return FALSE;
		}

		if (!node->SetParent(this))
		{
			return FALSE;
		}

		mChildren.push_back(node);
		return TRUE;
	}

	BOOL RemoveChild(INode * node)
	{
		if (node == NULL)
		{
			return FALSE;
		}

		if (mChildren.empty())
		{
			return TRUE;
		}

		BOOL result = FALSE;

		INode * tmp = NULL;
		for (std::list<INode *>::iterator it = mChildren.begin(); it != mChildren.end(); it++)
		{
			tmp = *it;
			if (tmp == node)
			{
				DELETE_PTR(tmp);
				mChildren.erase(it);
				result = TRUE;
			}
		}

		return result;
	}

	BOOL ClearChildren()
	{
		if (mChildren.empty())
		{
			return TRUE;
		}

		INode * tmp = NULL;
		for (std::list<INode *>::iterator it = mChildren.begin(); it != mChildren.end(); it++)
		{
			tmp = *it;
			if (tmp)
			{
				DELETE_PTR(tmp);
			}
		}

		mChildren.clear();
		return TRUE;
	}

	BOOL IsPropagationListener() CONST
	{
		return mIsPropagationListener;
	}

	VOID ScheduleListener()
	{
		mIsPropagationListener = TRUE;
	}

	VOID UnScheduleListener()
	{
		mIsPropagationListener = FALSE;
	}

	Window * GetWindow() CONST
	{
		return mWindow;
	}

	FLOAT GetRefreshInterval() CONST
	{
		return GetWindow()->GetRefreshInterval();
	}

	BOOL AddListener()
	{
		return GetWindow()->AddListener(this);
	}

	virtual BOOL CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		return IsPropagationListener();
	}

};

}

#endif /* !INODE_H_ */
