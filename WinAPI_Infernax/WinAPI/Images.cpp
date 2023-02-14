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
	IMAGEMANAGER->addFrameImage("�÷��̾�_�ȱ�", PLAYER"PlayerMove1.bmp", 252, 204, 4, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("�÷��̾�_����", PLAYER"PlayerJump1.bmp", 132, 198, 2, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("�÷��̾�_����", PLAYER"PlayerAttack.bmp", 456, 228, 2, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("�÷��̾�_�ɱ�", PLAYER"PlayerSitDown.bmp", 66, 132, 1, 2, true, COLORDEL);
	// �̱���
	//IMAGEMANAGER->addFrameImage("�÷��̾�_��ó", PLAYER"PlayerDeal.bmp", 342, 228, 2, 2, true, COLORDEL);
	//IMAGEMANAGER->addFrameImage("�÷��̾�_����", PLAYER"PlayerDie.bmp", 342, 228, 2, 2, true, COLORDEL);

#pragma region ���θ޴� & ���� & �κ��丮
	// ����
	IMAGEMANAGER->addFrameImage("����", BG"StartScene.bmp", 4255, 800, 3, 1, true, COLORDEL);
	IMAGEMANAGER->addImage("����", OBJ"Infernax.bmp", 951, 405, true, COLORDEL);
	IMAGEMANAGER->addImage("����_��", BG"StartCloudUp.bmp", 1716, 316, true, COLORDEL);
	IMAGEMANAGER->addImage("����_�Ʒ�", BG"StartCloudDown.bmp", 1287, 237, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("����_����", OBJ"ThunderL.bmp", 615, 321, 5, 1, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("����_������", OBJ"ThunderR.bmp", 1035, 309, 5, 1, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("�ѱ����", BG"PressAnyKey.bmp", 2628, 20, 6, 1, true, COLORDEL);

	// ���θ޴�
	IMAGEMANAGER->addImage("���Ӽ���", BG"MainSelect.bmp", 1280, 800, true, COLORDEL);
	IMAGEMANAGER->addImage("���Ӽ���", BG"MainSetting.bmp", 796, 605, true, COLORDEL);
	IMAGEMANAGER->addImage("���ÿ�����Ʈ", OBJ"SelectPoint.bmp", 21, 21, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("���θ޴�", OBJ"MainMenu.bmp", 312, 117, 2, 3, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("����ϱ�", OBJ"Continue.bmp", 260, 39, 2, 1, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("����", OBJ"Setting.bmp", 128, 38, 2, 1, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("�����", OBJ"Sound.bmp", 204, 37, 2, 1, true, COLORDEL);

	// ����
	IMAGEMANAGER->addImage("����_���", Village"VillageBG.bmp", 3800, 800, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("����", Village"Smith.bmp", 360, 123, 4, 1, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("������", Village"Magician.bmp", 108, 102, 2, 1, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("��ų����", Village"Skill.bmp", 108, 114, 2, 1, true, COLORDEL);

	// ����(��, ��ų, ����)
	IMAGEMANAGER->addImage("�������", Village"SmithBG.bmp", 1363, 1000, true, COLORDEL);
	IMAGEMANAGER->addImage("��", OBJ"Armer.bmp", 85, 86, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("������â", Village"BuySmith.bmp", 2560, 279, 2, 1, true, COLORDEL);
	IMAGEMANAGER->addImage("��ų����â", Village"BuySkill.bmp", 1280, 279, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("��������â", Village"BuyMagic.bmp", 2560, 279, 2, 1, true, COLORDEL);

	// �κ�(����, ����Ʈ, ĳ����)
	IMAGEMANAGER->addImage("����", INVEN"Magic.bmp", WINSIZE_X, WINSIZE_Y, true, COLORDEL);
	IMAGEMANAGER->addImage("����Ʈ", INVEN"Quest.bmp", WINSIZE_X, WINSIZE_Y, true, COLORDEL);
	IMAGEMANAGER->addImage("ĳ����", INVEN"Charicter.bmp", WINSIZE_X, WINSIZE_Y, true, COLORDEL);

#pragma endregion

#pragma region ��Ʋ�� 1-9
	// ��Ʋ��1
	IMAGEMANAGER->addImage("���1", BG"battleSceneBG.bmp", 4000, 1000, true, COLORDEL);
	IMAGEMANAGER->addImage("���2", BG"battleSceneBG1.bmp", 3588, 1000, true, COLORDEL);
	IMAGEMANAGER->addImage("����1", BG"battleSceneLAND1.bmp", 3200, 1000, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("���", OBJ"Crow.bmp", 90, 114, 2, 2, true, COLORDEL);
	// ��Ʋ�� 1 �� (����)
	IMAGEMANAGER->addFrameImage("����_�ȱ�", ENEMY"Zombie_Walk.bmp", 108, 444, 2, 4, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("����_����", ENEMY"ZombieDie.bmp", 270, 102, 3, 1, true, COLORDEL);

	// ��Ʋ��2
	IMAGEMANAGER->addImage("����2", BG"battleSceneLAND2.bmp", 2714, 800, true, COLORDEL);
	// ��Ʋ��2 ���� (�� ��) ���̸�
	IMAGEMANAGER->addFrameImage("����_�ȱ�", ENEMY"VomitBossWalk.bmp", 3720, 846, 8, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("����_�ұ�1", ENEMY"VomitBossFireAttack1.bmp", 234, 252, 2, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("����_�Ҳ�2", ENEMY"VomitBossFireAttack2.bmp", 120, 168, 2, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("����_���", ENEMY"VomitBossStay.bmp", 4650, 846, 10, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("����_����1", ENEMY"VomitBossDie1.bmp", 1800, 876, 2, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("����_����2", ENEMY"VomitBossDie2.bmp", 9000, 876, 10, 2, true, COLORDEL);

	// ��Ʋ��3
	IMAGEMANAGER->addImage("����3", BG"battleSceneLAND3.bmp", 2000, 1000, true, COLORDEL);
	IMAGEMANAGER->addImage("�ȼ�_����3", BG"PixelbattleSceneLAND3.bmp", 2000, 1000, true, COLORDEL);
	// ��Ʋ��3 �� (�ͽ�)
	// IMAGEMANAGER->addFrameImage("�ͽ�", ENEMY"Gost.bmp", 87, 210, 1, 2, true, COLORDEL);

	// ��Ʋ��4
	// ����� ����
	IMAGEMANAGER->addImage("��������", BG"BossMapBg.bmp", 2172, 800);
	IMAGEMANAGER->addFrameImage("�����_�ƾ�", ENEMY"BelphegorBossStand.bmp", 6444, 426, 12, 1, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("�����_�ȱ�", ENEMY"BelphegorBossWalk.bmp", 2664, 762, 4, 2, true, COLORDEL);
	// ����� ��ų1
	IMAGEMANAGER->addFrameImage("�����_â������", ENEMY"BelphegorBossJavelin.bmp", 2664, 762, 4, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("�����_â", ENEMY"BelphegorBossWeaponJavelin.bmp", 3027, 762, 4, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("�����_âȸ��", ENEMY"BelphegorBossJavelinTake.bmp", 3330, 762, 5, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("�����_���ֱ�", ENEMY"BelphegorBossWaite.bmp", 666, 762, 1, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("�������_â", ENEMY"BelphegorBossWeaponJavelinStay.bmp", 684, 504, 2, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("�����_�ȱ�_â", ENEMY"BelphegorBossWalk2.bmp", 1596, 762, 4, 2, true, COLORDEL);
	// ����� ��ų2
	IMAGEMANAGER->addFrameImage("�����_���", ENEMY"BelphegorBossScream.bmp", 2664, 762, 4, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("�����_���_â", ENEMY"BelphegorBossScream2.bmp", 2664, 762, 4, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("�����_��ȯ��Ż1", OBJ"Portal1.bmp", 855, 135, 3, 1, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("�����_��ȯ��Ż2", OBJ"Portal2.bmp", 855, 135, 3, 1, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("�����_��ȯ��Ż3", OBJ"Portal3.bmp", 2565, 270, 9, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("�����_ȭ����", OBJ"FireBall.bmp", 441, 126, 7, 2, true, COLORDEL);
	// ����� ��ų3
	IMAGEMANAGER->addFrameImage("�����_������", ENEMY"BelphegorBossKick.bmp", 2644, 792, 4, 2, true, COLORDEL);
	// ����� ����
	IMAGEMANAGER->addFrameImage("�����_����", ENEMY"BelphegorBossDie.bmp", 14256, 960, 16, 2, true, COLORDEL);

	// ��Ʋ��5 ��
	IMAGEMANAGER->addImage("���3", BG"battleSceneBG3.bmp", 2479, 1000, true, COLORDEL);
	IMAGEMANAGER->addImage("���4", BG"battleSceneBG4.bmp", 3983, 1000, true, COLORDEL);
	IMAGEMANAGER->addImage("����5", BG"battleSceneLAND7.bmp", 2520, 1575, true, COLORDEL);

	// ��Ʋ��6 ũ�μ� ����
	IMAGEMANAGER->addImage("ũ�μ����", BG"BossMapBg2.bmp", 1931, 1000, true, COLORDEL);
	IMAGEMANAGER->addImage("ũ�μ���������", BG"battleSceneLAND6.bmp", 2617, 1542, true, COLORDEL);
	// ũ�μ� ��ų1
	IMAGEMANAGER->addFrameImage("ũ�μ�_�����ȯ", ENEMY"CrocellBossSkill1.bmp", 1710, 459, 5, 1, true, COLORDEL);
	// ũ�μ� ��ų2
	IMAGEMANAGER->addFrameImage("ũ�μ�_ȭ����", ENEMY"CrocellBossSkill2.bmp", 1035, 459, 3, 1, true, COLORDEL);
	// ũ�μ� ����
	IMAGEMANAGER->addFrameImage("ũ�μ�_����", ENEMY"CrocellBossDie.bmp", 3948, 486, 7, 1, true, COLORDEL);
	// ũ�μ� �����ȯü
	IMAGEMANAGER->addFrameImage("�ذ�_�ȱ�", ENEMY"SkeletonWalk.bmp", 132, 216, 2, 2, true, COLORDEL);
	// ũ�μ� �Ѿ�
	IMAGEMANAGER->addImage("ũ�μ�_�Ѿ�", ENEMY"CrocellBossBullet.bmp", 33, 36, true, COLORDEL);

	// ��Ʋ��7 ��
	IMAGEMANAGER->addImage("����7", BG"battleSceneLAND9.bmp", 2500, 1000, true, COLORDEL);

	// ��Ʋ��8 ���� ����
	IMAGEMANAGER->addImage("�������1", BG"battleSceneBG5.bmp", 2498, 1000, true, COLORDEL);
	IMAGEMANAGER->addImage("�������2", BG"battleSceneBG6.bmp", 1847, 500, true, COLORDEL);
	IMAGEMANAGER->addImage("������������", BG"battleSceneLAND8.bmp", 1682, 1000, true, COLORDEL);

	// ��Ʋ��9 ����(����)

	// ��Ʋ��4 �� (���̷���) ��Ʋ��(����) �ذ� ����
	//IMAGEMANAGER->addImage("����4", BG"battleSceneLAND4.bmp", 2400, 1200, true, COLORDEL);
	//IMAGEMANAGER->addImage("�ȼ�_����4", BG"battleSceneLAND4.bmp", 2400, 1200, true, COLORDEL);
	//IMAGEMANAGER->addFrameImage("�ذ�_����", ENEMY"SkeletonAttack.bmp", 189, 110, 3, 2, true, COLORDEL);

#pragma endregion

	// ������Ʈ
	//IMAGEMANAGER->addImage("���ڰ�", OBJ"Cross.bmp", 120, 210, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("��������Ʈ", OBJ"EnemyDieEffect.bmp", 153, 114, 3, 1, true, COLORDEL);
	IMAGEMANAGER->addImage("���ĺ�", OBJ"BgBlack.bmp", WINSIZE_X, WINSIZE_Y, true, COLORDEL);
	IMAGEMANAGER->addImage("ȭ��Ʈ", OBJ"BgWhite.bmp", WINSIZE_X, WINSIZE_Y, true, COLORDEL);
	IMAGEMANAGER->addImage("����", OBJ"Select.bmp", 136, 136, true, COLORDEL);
}