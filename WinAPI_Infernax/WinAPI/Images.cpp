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
	// 플레이어
	IMAGEMANAGER->addFrameImage("플레이어", PLAYER"PlayerStand.bmp", 69, 198, 1, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("플레이어_걷기", PLAYER"PlayerMove1.bmp", 207, 204, 3, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("플레이어_점프", PLAYER"PlayerJump1.bmp", 132, 198, 2, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("플레이어_공격", PLAYER"PlayerAttack.bmp", 456, 228, 2, 2, true, COLORDEL);

	// 미구현
	IMAGEMANAGER->addFrameImage("플레이어_앉기", PLAYER"PlayerSitDown.bmp", 66, 132, 1, 2, true, COLORDEL);
	//IMAGEMANAGER->addFrameImage("플레이어_상처", PLAYER"PlayerDeal.bmp", 342, 228, 2, 2, true, COLORDEL);
	//IMAGEMANAGER->addFrameImage("플레이어_죽음", PLAYER"PlayerDie.bmp", 342, 228, 2, 2, true, COLORDEL);

	// 배틀씬1
	IMAGEMANAGER->addImage("배경1", BG"battleSceneBG.bmp", 3006, 1000, true, COLORDEL);
	IMAGEMANAGER->addImage("배경2", BG"battleSceneBG1.bmp", 3588, 1000, true, COLORDEL);
	IMAGEMANAGER->addImage("전투1", BG"battleSceneLAND1.bmp", 3200, 1000, true, COLORDEL);

	// 배틀씬2
	IMAGEMANAGER->addImage("전투2", BG"battleSceneLAND2.bmp", 2129, 800, true, COLORDEL);

	// 적
	IMAGEMANAGER->addFrameImage("좀비_걷기", ENEMY"Zombie_Walk.bmp", 108, 444, 2, 4, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("좀비_죽음", ENEMY"ZombieDie.bmp", 270, 102, 3, 1, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("보스_걷기", ENEMY"VomitBoss.bmp", 8415, 840, 17, 2, true, COLORDEL);

	// 오브젝트
	//IMAGEMANAGER->addImage("십자가", OBJ"Cross.bmp", 120, 210, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("까마귀", OBJ"Crow.bmp", 90, 114, 2, 2, true, COLORDEL);
	IMAGEMANAGER->addImage("알파블랙", OBJ"BgBlack.bmp", WINSIZE_X, WINSIZE_Y, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("죽음이펙트", OBJ"EnemyDieEffect.bmp", 153, 114, 3, 1, true, COLORDEL);
}