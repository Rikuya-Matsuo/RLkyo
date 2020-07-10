#include "DxLib.h"
#include "Game.h"
#include "SceneBase.h"

Game::Game():
	mCurrentCountIndex(0)
{
	mFlags.Set(BitFlagIndex::LoopIndex, true);

	mCount[0] = mCount[1] = GetNowCount();
}

Game::~Game()
{
}

void Game::Loop(SceneBase * firstScene)
{
	// シーン情報のセット
	mCurrentScene = firstScene;
	if (!mCurrentScene)
	{
		printfDx("Scene is not set\n");
		ScreenFlip();
		WaitKey();
		return;
	}

	// ゲームループ
	while (mFlags.Get(BitFlagIndex::LoopIndex))
	{
		// デルタタイム計算
		CalculateDeltaTime();

		// ゲーム終了
		mFlags.Set(BitFlagIndex::LoopIndex, false);
	}
}

void Game::Finish()
{
	if (mCurrentScene)
	{
		delete mCurrentScene;
	}
}

void Game::CalculateDeltaTime()
{
	// 添え字の定義、更新
	char prevCountIndex = mCurrentCountIndex;
	mCurrentCountIndex ^= 1;

	// 現在のカウントを取得
	mCount[mCurrentCountIndex] = GetNowCount();

	// 前フレームとのカウントの差を計算し、ミリ秒から秒単位に変換して記録
	int deltaCount = mCount[mCurrentCountIndex] - mCount[prevCountIndex];
	mDeltaTime = deltaCount / 1000.0f;
}
