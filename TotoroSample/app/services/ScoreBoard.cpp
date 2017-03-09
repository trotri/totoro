#include "ScoreBoard.h"

using namespace totoro;

CONST TCHAR * ScoreBoard::TAG = TEXT("ScoreBoard");
CONST String ScoreBoard::NAME = TEXT("score_board");
CONST String ScoreBoard::TITLE_INI_PATH = TEXT("res\\layout\\score_board_title.ini");
CONST String ScoreBoard::SCORE_INI_PATH = TEXT("res\\layout\\score_board.ini");

ScoreBoard::ScoreBoard() : mBasic(NULL), mScore(0)
{
	_Initialize();
}

ScoreBoard::~ScoreBoard()
{
}

BOOL ScoreBoard::_Initialize()
{
	Basic * label = Basic::Create(TITLE_INI_PATH);
	label->SetTextW(L"·ÖÊý£º");
	AddChild(label);

	mBasic = Basic::Create(SCORE_INI_PATH);
	AddChild(mBasic);

	return TRUE;
}

UINT ScoreBoard::GetScore() CONST
{
	return mScore;
}

VOID ScoreBoard::SetScore(UINT score)
{
	mScore = score;
	wsprintf(mScoreStr, TEXT("%d"), mScore);
	mBasic->SetTextW(mScoreStr);
}

VOID ScoreBoard::AddScore()
{
	mScore++;
	SetScore(mScore);
}
