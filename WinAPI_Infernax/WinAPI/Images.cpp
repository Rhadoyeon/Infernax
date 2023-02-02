#include "Stdafx.h"
#include "MainGame.h"
#include "Unit.h"

#define BG "Resources/Images/Background/"
#define BOSS "Resources/Images/Boss/"
#define ENEMY "Resources/Images/Enemy/"
#define PLAYERSKILL "Resources/Images/PlayerSkill/"
#define Village "Resources/Images/Village/"
#define UI "Resources/Images/UI/"
#define DIALOG "Resources/Images/Dialog/"
#define PLAYER "Resources/Images/Player/"
#define OBJ "Resources/Images/Object/"
#define INVEN "Resources/Images/Inven/"
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
	IMAGEMANAGER->addFrameImage("�÷��̾�_�ɱ�", PLAYER"PlayerSitDown.bmp", 66, 132, 1, 2, true, COLORDEL);

	// �̱���
	//IMAGEMANAGER->addFrameImage("�÷��̾�_��ó", PLAYER"PlayerDeal.bmp", 342, 228, 2, 2, true, COLORDEL);
	//IMAGEMANAGER->addFrameImage("�÷��̾�_����", PLAYER"PlayerDie.bmp", 342, 228, 2, 2, true, COLORDEL);

	// ����
	IMAGEMANAGER->addFrameImage("����", BG"StartScene.bmp", 4255, 800, 3, 1, true, COLORDEL);
	IMAGEMANAGER->addImage("����_��", BG"StartCloudUp.bmp", 1287, 237, true, COLORDEL);
	IMAGEMANAGER->addImage("����_�Ʒ�", BG"StartCloudDown.bmp", 1287, 237, true, COLORDEL);

	// ��Ʋ��1
	IMAGEMANAGER->addImage("���1", BG"battleSceneBG.bmp", 3006, 1000, true, COLORDEL);
	IMAGEMANAGER->addImage("���2", BG"battleSceneBG1.bmp", 3588, 1000, true, COLORDEL);
	IMAGEMANAGER->addImage("����1", BG"battleSceneLAND1.bmp", 3200, 1000, true, COLORDEL);

	// ��Ʋ��2
	IMAGEMANAGER->addImage("����2", BG"battleSceneLAND2.bmp", 2714, 800, true, COLORDEL);

	// ��
	IMAGEMANAGER->addFrameImage("����_�ȱ�", ENEMY"Zombie_Walk.bmp", 108, 444, 2, 4, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("����_����", ENEMY"ZombieDie.bmp", 270, 102, 3, 1, true, COLORDEL);

	// ����
	IMAGEMANAGER->addFrameImage("����_�ȱ�", ENEMY"VomitBossWalk.bmp", 3720, 846, 8, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("����_�ұ�1", ENEMY"VomitBossFireAttack1.bmp", 234, 252, 2, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("����_�Ҳ�2", ENEMY"VomitBossFireAttack2.bmp", 120, 168, 2, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("����_���", ENEMY"VomitBossStay.bmp", 4650, 846, 10, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("����_����1", ENEMY"VomitBossDie1.bmp", 1800, 876, 2, 2, true, COLORDEL);
	//IMAGEMANAGER->addFrameImage("����_����1", ENEMY"VomitBossDie1.bmp", 10800, 876, 12, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("����_����2", ENEMY"VomitBossDie2.bmp", 9000, 876, 10, 2, true, COLORDEL);

	// ����
	IMAGEMANAGER->addImage("����_���", Village"VillageBG.bmp", 2714, 800, true, COLORDEL);

	// ������Ʈ
	//IMAGEMANAGER->addImage("���ڰ�", OBJ"Cross.bmp", 120, 210, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("��������Ʈ", OBJ"EnemyDieEffect.bmp", 153, 114, 3, 1, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("���", OBJ"Crow.bmp", 90, 114, 2, 2, true, COLORDEL);
	IMAGEMANAGER->addImage("���ĺ�", OBJ"BgBlack.bmp", WINSIZE_X, WINSIZE_Y, true, COLORDEL);
	IMAGEMANAGER->addImage("����", OBJ"Select.bmp", 136, 136, true, COLORDEL);

	// �κ�(����, ����Ʈ, ĳ����)
	IMAGEMANAGER->addImage("����", INVEN"Magic.bmp", WINSIZE_X, WINSIZE_Y, true, COLORDEL);
	IMAGEMANAGER->addImage("����Ʈ", INVEN"Quest.bmp", WINSIZE_X, WINSIZE_Y, true, COLORDEL);
	IMAGEMANAGER->addImage("ĳ����", INVEN"Charicter.bmp", WINSIZE_X, WINSIZE_Y, true, COLORDEL);
}