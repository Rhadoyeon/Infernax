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

	// ��Ʋ��1
	IMAGEMANAGER->addImage("���1", BG"battleSceneBG.bmp", 3006, 1000, true, COLORDEL);
	IMAGEMANAGER->addImage("���2", BG"battleSceneBG1.bmp", 3588, 1000, true, COLORDEL);
	IMAGEMANAGER->addImage("����1", BG"battleSceneLAND1.bmp", 3200, 1000, true, COLORDEL);

	// ��Ʋ��2
	IMAGEMANAGER->addImage("����2", BG"battleSceneLAND2.bmp", 2129, 800, true, COLORDEL);

	// ��
	IMAGEMANAGER->addFrameImage("����_�ȱ�", ENEMY"Zombie_Walk.bmp", 108, 444, 2, 4, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("����_����", ENEMY"ZombieDie.bmp", 270, 102, 3, 1, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("����_�ȱ�", ENEMY"VomitBoss.bmp", 8415, 840, 17, 2, true, COLORDEL);

	// ������Ʈ
	//IMAGEMANAGER->addImage("���ڰ�", OBJ"Cross.bmp", 120, 210, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("���", OBJ"Crow.bmp", 90, 114, 2, 2, true, COLORDEL);
	IMAGEMANAGER->addImage("���ĺ�", OBJ"BgBlack.bmp", WINSIZE_X, WINSIZE_Y, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("��������Ʈ", OBJ"EnemyDieEffect.bmp", 153, 114, 3, 1, true, COLORDEL);
}