#include "DxLib.h"
#include "Game.h"
#include "SceneBase.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//��ʃ��[�h�̐ݒ�
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16);		//�𑜓x��1920*1080�Acolor��16bit��
	ChangeWindowMode(TRUE);								//�E�B���h�E���[�h��

	//DX���C�u����������
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	//�O���t�B�b�N�`���𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);

	SceneBase * firstScene = nullptr;
	GAME_CLASS.Loop(firstScene);

	GAME_CLASS.Finish();

	return 0;
}
