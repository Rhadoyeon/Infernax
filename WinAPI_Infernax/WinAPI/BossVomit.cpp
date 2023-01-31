#include "Stdafx.h"
#include "Unit.h"

void Unit::bossVomitInit(void)
{
	vomitBossX = 0.0f;
	vomitBossY = 552.0f;
	vomitBossRC = RectMakeCenter(vomitBossX, vomitBossY, 141, 140);
	vomitBossTwoRC = RectMakeCenter(vomitBossX, vomitBossY, 200, 140);

	vomitBossFrameX = vomitBossFrameY = vomitBossAttackFrameX = vomitBossAttackFrameY = vomitBossDieFrameX = vomitBossDieFrameY = vomitBossFireFrameX = vomitBossFireFrameY = 0;

	EnemyState = E_WALK;
	enemyMoment.BV_Hp = 0;
	enemyMoment.BV_Die = false;
}

void Unit::bossVomitUpdate(void)
{
	if (worldTimeCount % 25 == 0) vomitBossFrameX++;
	if (vomitBossFrameX > IMAGEMANAGER->findImage("보스_걷기")->getMaxFrameX()) vomitBossFrameX = 0;

	// 보스 오른쪽으로 무빙
	if (player.X > vomitBossRC.right && !enemyMoment.BV_Die)
	{
		EnemyState = E_WALK;
		vomitBossFrameY = 0;
		if (worldTimeCount % 2 == 0) vomitBossX += 5.5f;
	}

	// 보스 왼쪽으로 무빙
	else if (player.X < vomitBossRC.left && !enemyMoment.BV_Die)
	{
		EnemyState = E_WALK;
		vomitBossFrameY = 1;
		if (worldTimeCount % 2 == 0) vomitBossX -= 5.5f;
	}

	RECT Btemp;
	if (player.FrameY == 0)
	{
		if (IntersectRect(&Btemp, &playerRC, &vomitBossTwoRC))
		{
			EnemyState = E_ATTACK;
			if (worldTimeCount % 20 == 0) vomitBossAttackFrameX++;
			if (vomitBossAttackFrameX >= IMAGEMANAGER->findImage("보스_대기")->getMaxFrameX()) vomitBossAttackFrameX = 9;
			if (vomitBossAttackFrameX == 9)
			{
				if (worldTimeCount % 7 == 0) vomitBossFireFrameX++;
				if (vomitBossFireFrameX > IMAGEMANAGER->findImage("보스_불길1")->getMaxFrameX()) vomitBossFireFrameX = 0;
				if (vomitBossFireFrameX > IMAGEMANAGER->findImage("보스_불꽃2")->getMaxFrameX()) vomitBossFireFrameX = 0;
			}
		}
		else vomitBossAttackFrameX = 0;
	}
	else if (player.FrameY == 1)
	{
		if (IntersectRect(&Btemp, &playerRC, &vomitBossTwoRC))
		{
			EnemyState = E_ATTACK;
			if (worldTimeCount % 20 == 0) vomitBossAttackFrameX++;
			if (vomitBossAttackFrameX >= IMAGEMANAGER->findImage("보스_대기")->getMaxFrameX()) vomitBossAttackFrameX = 9;
			if (vomitBossAttackFrameX == 9)
			{
				if (worldTimeCount % 7 == 0) vomitBossFireFrameX++;
				if (vomitBossFireFrameX > IMAGEMANAGER->findImage("보스_불길1")->getMaxFrameX()) vomitBossFireFrameX = 0;
				if (vomitBossFireFrameX > IMAGEMANAGER->findImage("보스_불꽃2")->getMaxFrameX()) vomitBossFireFrameX = 0;
			}
		}
		else vomitBossAttackFrameX = 0;
	}


	vomitBossRC = RectMakeCenter(vomitBossX, vomitBossY, 141, 140);
	vomitBossTwoRC = RectMakeCenter(vomitBossX, vomitBossY, 200, 140);
}

void Unit::bossVomitRender(void)
{
	DrawRectMake(getMemDC(), vomitBossTwoRC);
	DrawRectMake(getMemDC(), vomitBossRC);

	if (EnemyState == E_WALK)
	{
		if (vomitBossFrameY == 1)	IMAGEMANAGER->findImage("보스_걷기")->frameRender(getMemDC(), vomitBossRC.left - 100, vomitBossRC.top - 283, vomitBossFrameX, vomitBossFrameY);
		else if (vomitBossFrameY == 0) IMAGEMANAGER->findImage("보스_걷기")->frameRender(getMemDC(), vomitBossRC.left - 180, vomitBossRC.top - 283, vomitBossFrameX, vomitBossFrameY);
	}

	if (EnemyState == E_ATTACK)
	{
		if (vomitBossFrameY == 1)	IMAGEMANAGER->findImage("보스_대기")->frameRender(getMemDC(), vomitBossRC.left - 100, vomitBossRC.top - 283, vomitBossAttackFrameX, vomitBossFrameY);
		else if (vomitBossFrameY == 0) IMAGEMANAGER->findImage("보스_대기")->frameRender(getMemDC(), vomitBossRC.left - 180, vomitBossRC.top - 283, vomitBossAttackFrameX, vomitBossFrameY);
	
		if (vomitBossAttackFrameX == 9)
		{
			if (vomitBossFrameY == 1)	IMAGEMANAGER->findImage("보스_불길1")->frameRender(getMemDC(), vomitBossRC.left - 125, vomitBossRC.top + 12, vomitBossFireFrameX, vomitBossFrameY);
			else if (vomitBossFrameY == 0) IMAGEMANAGER->findImage("보스_불길1")->frameRender(getMemDC(), vomitBossRC.left + 195, vomitBossRC.top + 12, vomitBossFireFrameX, vomitBossFrameY);

			if (vomitBossFrameY == 1)	IMAGEMANAGER->findImage("보스_불꽃2")->frameRender(getMemDC(), vomitBossRC.left - 115 , vomitBossRC.top + 52, vomitBossFireFrameX, vomitBossFrameY);
			else if (vomitBossFrameY == 0) IMAGEMANAGER->findImage("보스_불꽃2")->frameRender(getMemDC(), vomitBossRC.left + 240, vomitBossRC.top + 52, vomitBossFireFrameX, vomitBossFrameY);
			
			if (vomitBossFrameY == 1)	IMAGEMANAGER->findImage("보스_불꽃2")->frameRender(getMemDC(), vomitBossRC.left - 170, vomitBossRC.top + 52, vomitBossFireFrameX, vomitBossFrameY);
			else if (vomitBossFrameY == 0) IMAGEMANAGER->findImage("보스_불꽃2")->frameRender(getMemDC(), vomitBossRC.left + 300, vomitBossRC.top + 52, vomitBossFireFrameX, vomitBossFrameY);
		}		
	}
}