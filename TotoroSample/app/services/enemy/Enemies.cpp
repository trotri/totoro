#include "Enemies.h"

using namespace totoro;
using namespace std;

Enemies::Enemies() : mPlayerWarcraft(NULL), mScoreBoard(NULL)
{
	ScheduleUpdate();
}

Enemies::~Enemies()
{
}

Enemies * Enemies::Create(String fileName, PlayerWarcraft * playerWarcraft)
{
	Enemies * result = new Enemies;
	if (result && result->_Initialize(fileName, playerWarcraft))
	{
		return result;
	}

	DELETE_PTR(result);
	return NULL;
}

BOOL Enemies::_Initialize(String fileName, PlayerWarcraft * playerWarcraft)
{
	if (fileName.IsEmpty())
	{
		Log::e(TAG, TEXT("_Initialize File Name Is Empty!\n"));
		return FALSE;
	}

	if (playerWarcraft == NULL)
	{
		Log::e(TAG, TEXT("_Initialize Player Warcraft Is NULL!\n"));
		return FALSE;
	}

	map<String, String> params = Text::GetCfg(fileName);
	for (map<String, String>::iterator it = params.begin(); it != params.end(); it++)
	{
		EnemyWarcraft * warcraft = EnemyWarcraft::Create((*it).second);
		if (warcraft == NULL)
		{
			continue;
		}

		AddChild(warcraft);
		mEnemyWarcrafts.push_back(warcraft);
	}

	mPlayerWarcraft = playerWarcraft;
	mScoreBoard = ScoreBoard::GetInstance();
	return TRUE;
}

BOOL Enemies::Update()
{
	if (GetAsyncKeyState(Cfg::KEY_RESET))
	{
		ResetEnemyWarcrafts();
		return TRUE;
	}

	UINT usingCnt = UpdateUsing();
	if (usingCnt <= 0)
	{
		ResetEnemyWarcrafts();
	}

	Hit();
	return TRUE;
}

VOID Enemies::Hit()
{
	if (!mPlayerWarcraft->IsDraw())
	{
		return ;
	}

	EnemyWarcraft * enemyWarcraft;
	PlayerBullet * playerBullet;
	EnemyBullet * enemyBullet;
	for (list<EnemyWarcraft *>::iterator itEnemy = mEnemyWarcrafts.begin(); itEnemy != mEnemyWarcrafts.end(); itEnemy++)
	{
		enemyWarcraft = (*itEnemy);
		if (enemyWarcraft == NULL || !enemyWarcraft->IsUsing() || !enemyWarcraft->IsDraw())
		{
			continue;
		}

		if (Collider::IsCollide(enemyWarcraft->GetBox(), mPlayerWarcraft->GetBox(), TRUE))
		{
			mPlayerWarcraft->Destroy();
			break;
		}

		for (list<EnemyBullet *>::iterator itBullet = enemyWarcraft->mBullets.begin(); itBullet != enemyWarcraft->mBullets.end(); itBullet++)
		{
			enemyBullet = (*itBullet);
			if (enemyBullet == NULL || !enemyBullet->IsUsing())
			{
				continue;
			}

			if (Collider::IsCollide(enemyBullet->GetPos(), mPlayerWarcraft->GetBox()))
			{
				mPlayerWarcraft->Destroy();
				enemyBullet->SetUsing(FALSE);
				break;
			}
		}

		for (list<PlayerBullet *>::iterator itBullet = mPlayerWarcraft->mBullets.begin(); itBullet != mPlayerWarcraft->mBullets.end(); itBullet++)
		{
			playerBullet = (*itBullet);
			if (playerBullet == NULL || !playerBullet->IsUsing() || !playerBullet->IsDraw())
			{
				continue;
			}

			if (Collider::IsCollide(playerBullet->GetPos(), enemyWarcraft->GetBox()))
			{
				enemyWarcraft->Destroy();
				mScoreBoard->AddScore();
				playerBullet->SetUsing(FALSE);
				break;
			}
		}
	}
}

UINT Enemies::UpdateUsing()
{
	UINT result = 0;

	EnemyWarcraft * warcraft;
	FLOAT posY;
	for (list<EnemyWarcraft *>::iterator it = mEnemyWarcrafts.begin(); it != mEnemyWarcrafts.end(); it++)
	{
		warcraft = (*it);
		if (warcraft == NULL)
		{
			continue;
		}

		posY = warcraft->GetPosY();
		if (posY > 0 && posY < Cfg::HEIGHT)
		{
			warcraft->SetUsing(TRUE);
		}
		else
		{
			warcraft->SetUsing(FALSE);
		}

		if (warcraft->IsUsing())
		{
			result++;
		}
	}

	return result;
}

BOOL Enemies::ResetEnemyWarcrafts()
{
	EnemyWarcraft * tmp;
	for (list<EnemyWarcraft *>::iterator it = mEnemyWarcrafts.begin(); it != mEnemyWarcrafts.end(); it++)
	{
		tmp = (*it);
		if (tmp == NULL)
		{
			continue;
		}

		tmp->Reset();
	}

	return TRUE;
}
