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
	IMAGEMANAGER->addFrameImage("플레이어_걷기", PLAYER"PlayerMove1.bmp", 252, 204, 4, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("플레이어_점프", PLAYER"PlayerJump1.bmp", 132, 198, 2, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("플레이어_공격", PLAYER"PlayerAttack.bmp", 456, 228, 2, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("플레이어_앉기", PLAYER"PlayerSitDown.bmp", 66, 132, 1, 2, true, COLORDEL);
	// 미구현
	//IMAGEMANAGER->addFrameImage("플레이어_상처", PLAYER"PlayerDeal.bmp", 342, 228, 2, 2, true, COLORDEL);
	//IMAGEMANAGER->addFrameImage("플레이어_죽음", PLAYER"PlayerDie.bmp", 342, 228, 2, 2, true, COLORDEL);

#pragma region 메인메뉴 & 마을 & 인벤토리
	// 시작
	IMAGEMANAGER->addFrameImage("시작", BG"StartScene.bmp", 4255, 800, 3, 1, true, COLORDEL);
	IMAGEMANAGER->addImage("제목", OBJ"Infernax.bmp", 951, 405, true, COLORDEL);
	IMAGEMANAGER->addImage("구름_위", BG"StartCloudUp.bmp", 1716, 316, true, COLORDEL);
	IMAGEMANAGER->addImage("구름_아래", BG"StartCloudDown.bmp", 1287, 237, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("번개_왼쪽", OBJ"ThunderL.bmp", 615, 321, 5, 1, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("번개_오른쪽", OBJ"ThunderR.bmp", 1035, 309, 5, 1, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("넘김글자", BG"PressAnyKey.bmp", 2628, 20, 6, 1, true, COLORDEL);

	// 메인메뉴
	IMAGEMANAGER->addImage("게임선택", BG"MainSelect.bmp", 1280, 800, true, COLORDEL);
	IMAGEMANAGER->addImage("게임설정", BG"MainSetting.bmp", 796, 605, true, COLORDEL);
	IMAGEMANAGER->addImage("선택오브젝트", OBJ"SelectPoint.bmp", 21, 21, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("메인메뉴", OBJ"MainMenu.bmp", 312, 117, 2, 3, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("계속하기", OBJ"Continue.bmp", 260, 39, 2, 1, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("설정", OBJ"Setting.bmp", 128, 38, 2, 1, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("오디오", OBJ"Sound.bmp", 204, 37, 2, 1, true, COLORDEL);

	// 마을
	IMAGEMANAGER->addImage("마을_배경", Village"VillageBG.bmp", 3800, 800, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("장인", Village"Smith.bmp", 360, 123, 4, 1, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("마법사", Village"Magician.bmp", 108, 102, 2, 1, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("스킬상인", Village"Skill.bmp", 108, 114, 2, 1, true, COLORDEL);

	// 상점(방어구, 스킬, 여관)
	IMAGEMANAGER->addImage("무기상점", Village"SmithBG.bmp", 1363, 1000, true, COLORDEL);
	IMAGEMANAGER->addImage("방어구", OBJ"Armer.bmp", 85, 86, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("방어구구매창", Village"BuySmith.bmp", 2560, 279, 2, 1, true, COLORDEL);
	IMAGEMANAGER->addImage("스킬구매창", Village"BuySkill.bmp", 1280, 279, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("마법구매창", Village"BuyMagic.bmp", 2560, 279, 2, 1, true, COLORDEL);

	// 인벤(마법, 퀘스트, 캐릭터)
	IMAGEMANAGER->addImage("마법", INVEN"Magic.bmp", WINSIZE_X, WINSIZE_Y, true, COLORDEL);
	IMAGEMANAGER->addImage("퀘스트", INVEN"Quest.bmp", WINSIZE_X, WINSIZE_Y, true, COLORDEL);
	IMAGEMANAGER->addImage("캐릭터", INVEN"Charicter.bmp", WINSIZE_X, WINSIZE_Y, true, COLORDEL);

#pragma endregion

#pragma region 배틀씬 1-9
	// 배틀씬1
	IMAGEMANAGER->addImage("배경1", BG"battleSceneBG.bmp", 4000, 1000, true, COLORDEL);
	IMAGEMANAGER->addImage("배경2", BG"battleSceneBG1.bmp", 3588, 1000, true, COLORDEL);
	IMAGEMANAGER->addImage("전투1", BG"battleSceneLAND1.bmp", 3200, 1000, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("까마귀", OBJ"Crow.bmp", 90, 114, 2, 2, true, COLORDEL);
	// 배틀씬 1 적 (좀비)
	IMAGEMANAGER->addFrameImage("좀비_걷기", ENEMY"Zombie_Walk.bmp", 108, 444, 2, 4, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("좀비_죽음", ENEMY"ZombieDie.bmp", 270, 102, 3, 1, true, COLORDEL);

	// 배틀씬2
	IMAGEMANAGER->addImage("전투2", BG"battleSceneLAND2.bmp", 2714, 800, true, COLORDEL);
	// 배틀씬2 보스 (불 뿜) 파이몬
	IMAGEMANAGER->addFrameImage("보스_걷기", ENEMY"VomitBossWalk.bmp", 3720, 846, 8, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("보스_불길1", ENEMY"VomitBossFireAttack1.bmp", 234, 252, 2, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("보스_불꽃2", ENEMY"VomitBossFireAttack2.bmp", 120, 168, 2, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("보스_대기", ENEMY"VomitBossStay.bmp", 4650, 846, 10, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("보스_죽음1", ENEMY"VomitBossDie1.bmp", 1800, 876, 2, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("보스_죽음2", ENEMY"VomitBossDie2.bmp", 9000, 876, 10, 2, true, COLORDEL);

	// 배틀씬3
	IMAGEMANAGER->addImage("전투3", BG"battleSceneLAND3.bmp", 2000, 1000, true, COLORDEL);
	IMAGEMANAGER->addImage("픽셀_전투3", BG"PixelbattleSceneLAND3.bmp", 2000, 1000, true, COLORDEL);
	// 배틀씬3 적 (귀신)
	// IMAGEMANAGER->addFrameImage("귀신", ENEMY"Gost.bmp", 87, 210, 1, 2, true, COLORDEL);

	// 배틀씬4
	// 벨페고르 보스
	IMAGEMANAGER->addImage("벨페고르배경", BG"BossMapBg.bmp", 2172, 800);
	IMAGEMANAGER->addFrameImage("벨페고르_컷씬", ENEMY"BelphegorBossStand.bmp", 6444, 426, 12, 1, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("벨페고르_걷기", ENEMY"BelphegorBossWalk.bmp", 2664, 762, 4, 2, true, COLORDEL);
	// 벨페고르 스킬1
	IMAGEMANAGER->addFrameImage("벨페고르_창던지기", ENEMY"BelphegorBossJavelin.bmp", 2664, 762, 4, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("벨페고르_창", ENEMY"BelphegorBossWeaponJavelin.bmp", 3027, 762, 4, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("벨페고르_창회수", ENEMY"BelphegorBossJavelinTake.bmp", 3330, 762, 5, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("벨페고르_서있기", ENEMY"BelphegorBossWaite.bmp", 666, 762, 1, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("벨페고르의_창", ENEMY"BelphegorBossWeaponJavelinStay.bmp", 684, 504, 2, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("벨페고르_걷기_창", ENEMY"BelphegorBossWalk2.bmp", 1596, 762, 4, 2, true, COLORDEL);
	// 벨페고르 스킬2
	IMAGEMANAGER->addFrameImage("벨페고르_비명", ENEMY"BelphegorBossScream.bmp", 2664, 762, 4, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("벨페고르_비명_창", ENEMY"BelphegorBossScream2.bmp", 2664, 762, 4, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("벨페고르_소환포탈1", OBJ"Portal1.bmp", 855, 135, 3, 1, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("벨페고르_소환포탈2", OBJ"Portal2.bmp", 855, 135, 3, 1, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("벨페고르_소환포탈3", OBJ"Portal3.bmp", 2565, 270, 9, 2, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("벨페고르_화염구", OBJ"FireBall.bmp", 441, 126, 7, 2, true, COLORDEL);
	// 벨페고르 스킬3
	IMAGEMANAGER->addFrameImage("벨페고르_발차기", ENEMY"BelphegorBossKick.bmp", 2644, 792, 4, 2, true, COLORDEL);
	// 벨페고르 죽음
	IMAGEMANAGER->addFrameImage("벨페고르_죽음", ENEMY"BelphegorBossDie.bmp", 14256, 960, 16, 2, true, COLORDEL);

	// 배틀씬5 맵
	IMAGEMANAGER->addImage("배경3", BG"battleSceneBG3.bmp", 2479, 1000, true, COLORDEL);
	IMAGEMANAGER->addImage("배경4", BG"battleSceneBG4.bmp", 3983, 1000, true, COLORDEL);
	IMAGEMANAGER->addImage("전투5", BG"battleSceneLAND7.bmp", 2520, 1575, true, COLORDEL);

	// 배틀씬6 크로셀 보스
	IMAGEMANAGER->addImage("크로셀배경", BG"BossMapBg2.bmp", 1931, 1000, true, COLORDEL);
	IMAGEMANAGER->addImage("크로셀전투지형", BG"battleSceneLAND6.bmp", 2617, 1542, true, COLORDEL);
	// 크로셀 스킬1
	IMAGEMANAGER->addFrameImage("크로셀_좀비소환", ENEMY"CrocellBossSkill1.bmp", 1710, 459, 5, 1, true, COLORDEL);
	// 크로셀 스킬2
	IMAGEMANAGER->addFrameImage("크로셀_화염구", ENEMY"CrocellBossSkill2.bmp", 1035, 459, 3, 1, true, COLORDEL);
	// 크로셀 죽음
	IMAGEMANAGER->addFrameImage("크로셀_죽음", ENEMY"CrocellBossDie.bmp", 3948, 486, 7, 1, true, COLORDEL);
	// 크로셀 좀비소환체
	IMAGEMANAGER->addFrameImage("해골_걷기", ENEMY"SkeletonWalk.bmp", 132, 216, 2, 2, true, COLORDEL);
	// 크로셀 총알
	IMAGEMANAGER->addImage("크로셀_총알", ENEMY"CrocellBossBullet.bmp", 33, 36, true, COLORDEL);

	// 배틀씬7 맵
	IMAGEMANAGER->addImage("전투7", BG"battleSceneLAND9.bmp", 2500, 1000, true, COLORDEL);

	// 배틀씬8 고대웜 보스
	IMAGEMANAGER->addImage("고대웜배경1", BG"battleSceneBG5.bmp", 2498, 1000, true, COLORDEL);
	IMAGEMANAGER->addImage("고대웜배경2", BG"battleSceneBG6.bmp", 1847, 500, true, COLORDEL);
	IMAGEMANAGER->addImage("고대웜전투지형", BG"battleSceneLAND8.bmp", 1682, 1000, true, COLORDEL);

	// 배틀씬9 보스(미정)

	// 배틀씬4 적 (스켈레톤) 배틀씬(미정) 해골 등장
	//IMAGEMANAGER->addImage("전투4", BG"battleSceneLAND4.bmp", 2400, 1200, true, COLORDEL);
	//IMAGEMANAGER->addImage("픽셀_전투4", BG"battleSceneLAND4.bmp", 2400, 1200, true, COLORDEL);
	//IMAGEMANAGER->addFrameImage("해골_공격", ENEMY"SkeletonAttack.bmp", 189, 110, 3, 2, true, COLORDEL);

#pragma endregion

	// 오브젝트
	//IMAGEMANAGER->addImage("십자가", OBJ"Cross.bmp", 120, 210, true, COLORDEL);
	IMAGEMANAGER->addFrameImage("죽음이펙트", OBJ"EnemyDieEffect.bmp", 153, 114, 3, 1, true, COLORDEL);
	IMAGEMANAGER->addImage("알파블랙", OBJ"BgBlack.bmp", WINSIZE_X, WINSIZE_Y, true, COLORDEL);
	IMAGEMANAGER->addImage("화이트", OBJ"BgWhite.bmp", WINSIZE_X, WINSIZE_Y, true, COLORDEL);
	IMAGEMANAGER->addImage("선택", OBJ"Select.bmp", 136, 136, true, COLORDEL);
}