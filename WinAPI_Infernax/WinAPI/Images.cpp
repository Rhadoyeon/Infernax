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
	// 플레이어
	IMAGEMANAGER->addFrameImage("플레이어", PLAYER"PlayerStand.bmp", 69, 198, 1, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("플레이어_걷기", PLAYER"PlayerMove1.bmp", 207, 204, 3, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("플레이어_점프", PLAYER"PlayerJump1.bmp", 132, 198, 2, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("플레이어_공격", PLAYER"PlayerAttack.bmp", 456, 228, 2, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("플레이어_앉기", PLAYER"PlayerSitDown.bmp", 66, 132, 1, 2, true, COLORDEL);

	// 미구현
	//IMAGEMANAGER->addFrameImage("플레이어_상처", PLAYER"PlayerDeal.bmp", 342, 228, 2, 2, true, COLORDEL);
	//IMAGEMANAGER->addFrameImage("플레이어_죽음", PLAYER"PlayerDie.bmp", 342, 228, 2, 2, true, COLORDEL);

	// 시작
	IMAGEMANAGER->addFrameImage("시작", BG"StartScene.bmp", 4255, 800, 3, 1, true, COLORDEL);
	IMAGEMANAGER->addImage("구름_위", BG"StartCloudUp.bmp", 1287, 237, true, COLORDEL);
	IMAGEMANAGER->addImage("구름_아래", BG"StartCloudDown.bmp", 1287, 237, true, COLORDEL);

	// 배틀씬1
	IMAGEMANAGER->addImage("배경1", BG"battleSceneBG.bmp", 3006, 1000, true, COLORDEL);
	IMAGEMANAGER->addImage("배경2", BG"battleSceneBG1.bmp", 3588, 1000, true, COLORDEL);
	IMAGEMANAGER->addImage("전투1", BG"battleSceneLAND1.bmp", 3200, 1000, true, COLORDEL);

	// 배틀씬2
	IMAGEMANAGER->addImage("전투2", BG"battleSceneLAND2.bmp", 2714, 800, true, COLORDEL);

	// 적
	IMAGEMANAGER->addFrameImage("좀비_걷기", ENEMY"Zombie_Walk.bmp", 108, 444, 2, 4, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("좀비_죽음", ENEMY"ZombieDie.bmp", 270, 102, 3, 1, true, COLORDEL);

	// 보스
	IMAGEMANAGER->addFrameImage("보스_걷기", ENEMY"VomitBossWalk.bmp", 3720, 846, 8, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("보스_불길1", ENEMY"VomitBossFireAttack1.bmp", 234, 252, 2, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("보스_불꽃2", ENEMY"VomitBossFireAttack2.bmp", 120, 168, 2, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("보스_대기", ENEMY"VomitBossStay.bmp", 4650, 846, 10, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("보스_죽음1", ENEMY"VomitBossDie1.bmp", 1800, 876, 2, 2, true, COLORDEL);
	//IMAGEMANAGER->addFrameImage("보스_죽음1", ENEMY"VomitBossDie1.bmp", 10800, 876, 12, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("보스_죽음2", ENEMY"VomitBossDie2.bmp", 9000, 876, 10, 2, true, COLORDEL);

	// 마을
	IMAGEMANAGER->addImage("마을_배경", Village"VillageBG.bmp", 2714, 800, true, COLORDEL);

	// 오브젝트
	//IMAGEMANAGER->addImage("십자가", OBJ"Cross.bmp", 120, 210, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("죽음이펙트", OBJ"EnemyDieEffect.bmp", 153, 114, 3, 1, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("까마귀", OBJ"Crow.bmp", 90, 114, 2, 2, true, COLORDEL);
	IMAGEMANAGER->addImage("알파블랙", OBJ"BgBlack.bmp", WINSIZE_X, WINSIZE_Y, true, COLORDEL);
	IMAGEMANAGER->addImage("선택", OBJ"Select.bmp", 136, 136, true, COLORDEL);

	// 인벤(마법, 퀘스트, 캐릭터)
	IMAGEMANAGER->addImage("마법", INVEN"Magic.bmp", WINSIZE_X, WINSIZE_Y, true, COLORDEL);
	IMAGEMANAGER->addImage("퀘스트", INVEN"Quest.bmp", WINSIZE_X, WINSIZE_Y, true, COLORDEL);
	IMAGEMANAGER->addImage("캐릭터", INVEN"Charicter.bmp", WINSIZE_X, WINSIZE_Y, true, COLORDEL);
}