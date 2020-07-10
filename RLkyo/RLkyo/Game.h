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

	void Finish();

	// デルタタイム取得
	float GetDeltaTime() const { return mDeltaTime; }

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

	// デルタタイムの計算
	void CalculateDeltaTime();
};

#define GAME_CLASS Game::GetInstance()
