#pragma once

#include "..\..\totoro\ap\ILayer.h"
#include "Cfg.h"
#include "..\..\totoro\util\Text.h"
#include "..\..\totoro\service\Basic.h"
#include "..\..\totoro\form\CheckBox.h"
#include "..\..\totoro\form\ImageButton.h"
#include "..\..\totoro\graphics\Scene.h"

LRESULT CALLBACK DialogBtnOkProc(VOID * message);
LRESULT CALLBACK DialogBtnCancelProc(VOID * message);

/**
 * SettingDialog class file
 * 设置对话框类
 * @author 宋欢 <trotri@yeah.net>
 * @version $Id: SettingDialog.h 1 2015-04-06 19:22:06Z huan.song $
 * @package services
 * @since 1.0
 */
class SettingDialog : public totoro::ILayer
{
public:
	static CONST TCHAR * TAG;
	static CONST totoro::String NAME;
	static CONST totoro::String PATH;

public:
	totoro::Basic * mBackground;
	totoro::CheckBox * mAudioDisabled;
	totoro::CheckBox * mDoubleMuzzle;
	totoro::ImageButton * mBtnOk;
	totoro::ImageButton * mBtnCancel;

protected:
	SettingDialog();

public:
	~SettingDialog();

public:
	static SettingDialog * Create();

protected:
	BOOL _Initialize();

public:
	BOOL Update();
	VOID Show();
	VOID Hide();
	BOOL CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};
