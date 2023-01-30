#include "Stdafx.h"
#include "Unit.h"

void Unit::bossVomitInit(void)
{
	vomitBossX = 0;
	vomitBossY = 552;
	vomitBossRC = RectMakeCenter(vomitBossX, vomitBossY, 141, 140);
	vomitBossFrameX = vomitBossFrameY = vomitBossAttackFrameX = vomitBossAttackFrameY = vomitBossDieFrameX = vomitBossDieFrameY = 0;

	enemyMoment.BV_Hp = 0;
	enemyMoment.BV_Die = false;
}

void Unit::bossVomitUpdate(void)
{
	if (worldTimeCount % 25 == 0) vomitBossFrameX++;
	if (vomitBossFrameX > IMAGEMANAGER->findImage("º¸½º_°È±â")->getMaxFrameX()) vomitBossFrameX = 0;

	// º¸½º ¿À¸¥ÂÊÀ¸·Î ¹«ºù
	if (playerX > vomitBossRC.right + 200 && !enemyMoment.BV_Die)
	{
		vomitBossFrameY = 0;
		vomitBossX += 1;
		//vomitBossRC.right += 1;
	}

	// º¸½º ¿ÞÂÊÀ¸·Î ¹«ºù
	else if (playerX < vomitBossRC.left -200 && !enemyMoment.BV_Die)
	{
		vomitBossFrameY = 1;
		vomitBossX -= 1;
		//vomitBossRC.right -= 1;
	}

	vomitBossRC = RectMakeCenter(vomitBossX, vomitBossY, 141, 140);
}

void Unit::bossVomitRender(void)
{
	DrawRectMake(getMemDC(), vomitBossRC);

	//IMAGEMANAGER->findImage("º¸½º_°È±â")->frameRender(getMemDC(), vomitBossRC.left, vomitBossRC.top, vomitBossFrameX, vomitBossFrameY);
	if (vomitBossFrameY == 1)	IMAGEMANAGER->findImage("º¸½º_°È±â")->frameRender(getMemDC(), vomitBossRC.left - 100, vomitBossRC.top - 283, vomitBossFrameX, vomitBossFrameY);
	else if (vomitBossFrameY == 0) IMAGEMANAGER->findImage("º¸½º_°È±â")->frameRender(getMemDC(), vomitBossRC.left - 180, vomitBossRC.top - 283, vomitBossFrameX, vomitBossFrameY);


}