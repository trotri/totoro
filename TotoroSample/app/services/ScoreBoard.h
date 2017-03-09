#pragma once

#include "..\..\totoro\ap\ILayer.h"
#include "..\..\totoro\service\Basic.h"

/**
 * ScoreBoard class file
 * º«∑÷∞Â¿‡
 *
 * @author ÀŒª∂ <trotri@yeah.net>
 * @version $Id: ScoreBoard.h 1 2015-04-06 19:22:06Z huan.song $
 * @since 1.0
 */
class ScoreBoard : public totoro::ILayer, public totoro::ISingleton<ScoreBoard>
{
public:
	static CONST TCHAR * TAG;
	static CONST totoro::String NAME;
	static CONST totoro::String TITLE_INI_PATH;
	static CONST totoro::String SCORE_INI_PATH;

private:
	totoro::Basic * mBasic;
	UINT mScore;
	TCHAR mScoreStr[4];

public:
	ScoreBoard();

public:
	~ScoreBoard();

protected:
	BOOL _Initialize();

public:
	UINT GetScore() CONST;
	VOID SetScore(UINT score);
	VOID AddScore();
};
