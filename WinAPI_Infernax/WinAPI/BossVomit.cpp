#include "Stdafx.h"
#include "Unit.h"

void Unit::bossVomitInit(void)
{
	vomitBossX = 0;
	vomitBossY = 300;
	vomitBossRC = RectMakeCenter(vomitBossX, vomitBossY, 141, 140);
	vomitBossFrameX = vomitBossFrameY = vomitBossAttackFrameX = vomitBossAttackFrameY = vomitBossDieFrameX = vomitBossDieFrameY = 0;

	enemyMoment.E_Hp = 0;
	enemyMoment.E_Die = false;
}

void Unit::bossVomitUpdate(void)
{
	if (worldTimeCount % 25 == 0) vomitBossFrameX++;
	if (vomitBossFrameX > IMAGEMANAGER->findImage("보스_걷기")->getMaxFrameX()) vomitBossFrameX = 0;

	// 좀비 오른쪽으로 무빙
	if (playerX > vomitBossRC.right && !enemyMoment.E_Die)
	{
		vomitBossFrameY = 0;
		vomitBossRC.left += 1;
		vomitBossRC.right += 1;
	}

	// 좀비 왼쪽으로 무빙
	else if (playerX < vomitBossRC.left && !enemyMoment.E_Die)
	{
		vomitBossFrameY = 1;
		vomitBossRC.left -= 1;
		vomitBossRC.right -= 1;
	}

	//vomitBossRC = RectMakeCenter(vomitBossX, vomitBossY, 141, 140);

}

void Unit::bossVomitRender(void)
{
	DrawRectMake(getMemDC(), vomitBossRC);

	//IMAGEMANAGER->findImage("보스_걷기")->frameRender(getMemDC(), vomitBossRC.left, vomitBossRC.top, vomitBossFrameX, vomitBossFrameY);
	if (zombieFrameY == 1)	IMAGEMANAGER->findImage("보스_걷기")->frameRender(getMemDC(), vomitBossRC.left, vomitBossRC.top - 8, vomitBossFrameX, vomitBossFrameY);
	else if (zombieFrameY == 0) IMAGEMANAGER->findImage("보스_걷기")->frameRender(getMemDC(), vomitBossRC.left, vomitBossRC.top - 8, vomitBossFrameX, vomitBossFrameY);


}