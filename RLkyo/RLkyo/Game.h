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

	// 時間関連
	float mDeltaTime;
	int mCount[2];
	char mCurrentCountIndex;

	// ビットフラグ
	typedef uint8_t BitFlagType;
	BitFlag<BitFlagType> mFlags;

	enum BitFlagIndex
	{
		LoopIndex = 0,
		Invalid
	};

	// 現在のシーンへのポインタ
	class SceneBase * mCurrentScene;
};

#define GAME_CLASS Game::GetInstance()
