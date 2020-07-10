#include "DxLib.h"
#include "Game.h"
#include "SceneBase.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//画面モードの設定
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16);		//解像度を1920*1080、colorを16bitに
	ChangeWindowMode(TRUE);								//ウィンドウモードに

	//DXライブラリ初期化
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	//グラフィック描画先を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);

	SceneBase * firstScene = nullptr;
	GAME_CLASS.Loop(firstScene);

	GAME_CLASS.Finish();

	return 0;
}
