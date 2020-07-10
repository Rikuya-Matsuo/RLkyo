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
	if (!mCurrentScene)
	{
		printfDx("Scene is not set\n");
		ScreenFlip();
		WaitKey();
		return;
	}

	// �Q�[�����[�v
	while (mFlags.Get(BitFlagIndex::LoopIndex))
	{
		// �f���^�^�C���v�Z
		CalculateDeltaTime();

		// �Q�[���I��
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
	// �Y�����̒�`�A�X�V
	char prevCountIndex = mCurrentCountIndex;
	mCurrentCountIndex ^= 1;

	// ���݂̃J�E���g���擾
	mCount[mCurrentCountIndex] = GetNowCount();

	// �O�t���[���Ƃ̃J�E���g�̍����v�Z���A�~���b����b�P�ʂɕϊ����ċL�^
	int deltaCount = mCount[mCurrentCountIndex] - mCount[prevCountIndex];
	mDeltaTime = deltaCount / 1000.0f;
}
