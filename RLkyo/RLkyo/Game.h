#pragma once
#include "BitFlag.h"

class Game final
{
public:
	~Game();

	static Game & GetInstance()
	{
		static Game instance;
		return instance;
	}

	void Loop(class SceneBase * firstScene);

private:
	Game();

	// ���Ԋ֘A
	float mDeltaTime;
	int mCount[2];
	char mCurrentCountIndex;

	// �r�b�g�t���O
	typedef uint8_t BitFlagType;
	BitFlag<BitFlagType> mFlags;

	enum BitFlagIndex
	{
		LoopIndex = 0,
		Invalid
	};

	// ���݂̃V�[���ւ̃|�C���^
	class SceneBase * mCurrentScene;
};

#define GAME_CLASS Game::GetInstance()
