#include "Stdafx.h"
#include "MainGame.h"

#define BG "Resources/Images/Background/"
#define BOSS "Resources/Images/Boss/"
#define ENEMY "Resources/Images/Enemy/"
#define IMG "Resources/Images/"
#define PLAYERSKILL "Resources/Images/PlayerSkill/"
#define UI "Resources/Images/UI/"
#define DIALOG "Resources/Images/Dialog/"
#define PLAYER "Resources/Images/Player/"
#define OBJ "Resources/Images/Object/"
#define SHOP "Resources/Images/Shop/"
#define ENDING "Resources/Images/Ending/"
#define COLORDEL RGB(255, 0, 255)

void MainGame::Images(void)
{
	// �÷��̾�
	IMAGEMANAGER->addFrameImage("�÷��̾�", PLAYER"PlayerStand.bmp", 69, 198, 1, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("�÷��̾�_�ȱ�", PLAYER"PlayerMove1.bmp", 207, 204, 3, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("�÷��̾�_����", PLAYER"PlayerJump1.bmp", 132, 198, 2, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("�÷��̾�_����", PLAYER"PlayerAttack.bmp", 456, 228, 2, 2, true, COLORDEL);

	// �̱���
	IMAGEMANAGER->addFrameImage("�÷��̾�_�ɱ�", PLAYER"PlayerSitDown.bmp", 66, 132, 1, 2, true, COLORDEL);
	//IMAGEMANAGER->addFrameImage("�÷��̾�_��ó", PLAYER"PlayerDeal.bmp", 342, 228, 2, 2, true, COLORDEL);
	//IMAGEMANAGER->addFrameImage("�÷��̾�_����", PLAYER"PlayerDie.bmp", 342, 228, 2, 2, true, COLORDEL);

	// ��Ʋ��
	IMAGEMANAGER->addImage("���1", BG"battleSceneBG.bmp", 3006, 1000, true, COLORDEL);
	IMAGEMANAGER->addImage("���2", BG"battleSceneBG1.bmp", 3588, 1000, true, COLORDEL);
	IMAGEMANAGER->addImage("����1", BG"battleSceneLAND1.bmp", 3200, 1000, true, COLORDEL);

	// ������Ʈ
	//IMAGEMANAGER->addImage("���ڰ�", OBJ"Cross.bmp", 120, 210, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("���", OBJ"Crow.bmp", 90, 114, 2, 2, true, COLORDEL);
	IMAGEMANAGER->addImage("���ĺ�", OBJ"BgBlack.bmp", WINSIZE_X, WINSIZE_Y, true, COLORDEL);

	// ��
	IMAGEMANAGER->addFrameImage("����", ENEMY"Zombie.bmp", 108, 222, 2, 2, true, COLORDEL);

}