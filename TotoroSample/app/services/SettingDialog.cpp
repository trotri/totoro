#include "SettingDialog.h"
#include "..\scenes\MainScene.h"

using namespace totoro;
using namespace std;

CONST TCHAR * SettingDialog::TAG = TEXT("SettingDialog");
CONST String SettingDialog::NAME = TEXT("setting_dialog");
CONST String SettingDialog::PATH = TEXT("res\\layout\\setting_dialog.ini");

SettingDialog::SettingDialog() : mBackground(NULL), mAudioDisabled(NULL), mDoubleMuzzle(NULL), mBtnOk(NULL), mBtnCancel(NULL)
{
	SetName(NAME);
	Hide();
	AddListener();
}

SettingDialog::~SettingDialog()
{
}

SettingDialog * SettingDialog::Create()
{
	SettingDialog * result = new SettingDialog;
	if (result && result->_Initialize())
	{
		return result;
	}

	DELETE_PTR(result);
	return NULL;
}

BOOL SettingDialog::_Initialize()
{
	map<String, String> params = Text::GetCfg(PATH);

	String key, value;
	for (map<String, String>::iterator it = params.begin(); it != params.end(); it++)
	{
		key = (*it).first;
		value = (*it).second;

		if (key == TEXT("background"))
		{
			mBackground = Basic::Create(value);
			AddChild(mBackground);
			continue;
		}

		if (key == TEXT("audio_disabled"))
		{
			mAudioDisabled = CheckBox::Create(value);
			AddChild(mAudioDisabled);
			continue;
		}

		if (key == TEXT("audio_disabled_text"))
		{
			Basic * audioDisabledText = Basic::Create(value);
			audioDisabledText->SetTextW(L"¾²Òô");
			AddChild(audioDisabledText);
		}

		if (key == TEXT("double_muzzle"))
		{
			mDoubleMuzzle = CheckBox::Create(value);
			AddChild(mDoubleMuzzle);
			continue;
		}

		if (key == TEXT("double_muzzle_text"))
		{
			Basic * doubleMuzzleText = Basic::Create(value);
			doubleMuzzleText->SetTextW(L"Ë«Ç¹¿Ú");
			AddChild(doubleMuzzleText);
		}

		if (key == TEXT("btn_ok"))
		{
			mBtnOk = ImageButton::Create(value);
			mBtnOk->SetMessage(this);
			mBtnOk->SetOnClickProc(DialogBtnOkProc);
			AddChild(mBtnOk);
			continue;
		}

		if (key == TEXT("btn_cancel"))
		{
			mBtnCancel = ImageButton::Create(value);
			mBtnCancel->SetMessage(this);
			mBtnCancel->SetOnClickProc(DialogBtnCancelProc);
			AddChild(mBtnCancel);
			continue;
		}
	}

	Hide();
	return TRUE;
}

BOOL SettingDialog::Update()
{
	return TRUE;
}

VOID SettingDialog::Show()
{
	mAudioDisabled->SetChecked(Cfg::IsAudioDisabled());
	mDoubleMuzzle->SetChecked(Cfg::IsDoubleMuzzle());
	ILayer::Show();
}

VOID SettingDialog::Hide()
{
	ILayer::Hide();
}

BOOL CALLBACK SettingDialog::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return FALSE;
}

LRESULT CALLBACK DialogBtnOkProc(VOID * message)
{
	SettingDialog * settingDialog = (SettingDialog *)message;
	Cfg::SetAudioDisabled(settingDialog->mAudioDisabled->IsChecked());
	Cfg::SetDoubleMuzzle(settingDialog->mDoubleMuzzle->IsChecked());
	settingDialog->Hide();
	return 0;
}

LRESULT CALLBACK DialogBtnCancelProc(VOID * message)
{
	SettingDialog * settingDialog = (SettingDialog *)message;
	settingDialog->Hide();
	return 0;
}
