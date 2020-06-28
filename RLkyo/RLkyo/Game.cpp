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
	// �V�[�����̃Z�b�g
	mCurrentScene = firstScene;
	if (mCurrentScene == nullptr)
	{
		printfDx("Scene is not set\n");
		ScreenFlip();
		WaitKey();
		return;
	}

	while (mFlags.Get(BitFlagIndex::LoopIndex))
	{
		mFlags.Set(BitFlagIndex::LoopIndex, false);
	}
}
