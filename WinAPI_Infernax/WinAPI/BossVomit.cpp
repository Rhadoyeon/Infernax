#include "Stdafx.h"
#include "Unit.h"

void Unit::bossVomitInit(void)
{
#pragma region 초기화
	vomitBossX = 0.0f;
	vomitBossY = 552.0f;
	vomitBossRC = RectMakeCenter(vomitBossX, vomitBossY, 141, 140);
	vomitBossTwoRC = RectMakeCenter(vomitBossX, vomitBossY, 400, 140);

	vomitBossFrameX = vomitBossFrameY = vomitBossAttackFrameX = vomitBossAttackFrameY = vomitBossDieFrameX1 = vomitBossDieFrameX2 = vomitBossFireFrameX = vomitBossFireFrameY = 0;

	enemy.State = E_WALK;
	enemyMoment.BV_Hp = 0;
	enemyMoment.BV_Die = false;

	vomitBossFireBoss = false;
	vomitBossFireTime = 0;
	vomitBossFireEnd = false;
	vomitBossFireEndTime = 0;
#pragma endregion
}

void Unit::bossVomitUpdate(void)
{
#pragma region 보스 이동
	if (!enemyMoment.BV_Die)
	{
		if (worldTimeCount % 25 == 0) vomitBossFrameX++;
		if (vomitBossFrameX > IMAGEMANAGER->findImage("보스_걷기")->getMaxFrameX()) vomitBossFrameX = 0;

		// 보스 오른쪽으로 무빙
		if (!vomitBossFireBoss)
		{
			if (player.X > vomitBossRC.right && !enemyMoment.BV_Die)
			{
				enemy.State = E_WALK;
				vomitBossFrameY = 0;
				if (worldTimeCount % 2 == 0) vomitBossX += 1.5f;
			}

			// 보스 왼쪽으로 무빙
			else if (player.X < vomitBossRC.left && !enemyMoment.BV_Die)
			{
				enemy.State = E_WALK;
				vomitBossFrameY = 1;
				if (worldTimeCount % 2 == 0) vomitBossX -= 1.5f;
			}
		}
#pragma endregion

#pragma region 보스 스킬 & 플레이어 충돌
		RECT Btemp;
		if (player.FrameY == 0)
		{
			if (IntersectRect(&Btemp, &player.Rc, &vomitBossTwoRC) && !vomitBossFireEnd && !vomitBossFireBoss)
			{
				// 충돌될때 fire는 true / 시간, 프레임 초기화
				vomitBossFireBoss = true;
				vomitBossFireTime = 0;
				vomitBossAttackFrameX = 0;
			}
		}
		else if (player.FrameY == 1)
		{
			if (IntersectRect(&Btemp, &player.Rc, &vomitBossTwoRC))
			{
				enemy.State = E_ATTACK;
				if (worldTimeCount % 20 == 0) vomitBossAttackFrameX++;
				if (vomitBossAttackFrameX >= IMAGEMANAGER->findImage("보스_대기")->getMaxFrameX()) vomitBossAttackFrameX = 9;

				if (vomitBossAttackFrameX == 9)
				{
					if (worldTimeCount % 7 == 0) vomitBossFireFrameX++;
					if (vomitBossFireFrameX > IMAGEMANAGER->findImage("보스_불길1")->getMaxFrameX()) vomitBossFireFrameX = 0;
					if (vomitBossFireFrameX > IMAGEMANAGER->findImage("보스_불꽃2")->getMaxFrameX()) vomitBossFireFrameX = 0;
				}
			}
		}

		// 충돌이 true일때 불 true줘서 불 발사
		if (vomitBossFireBoss)
		{
			vomitBossFireTime++;
			if (vomitBossFireTime > 300)
			{
				vomitBossFireBoss = false;
				vomitBossFireTime = 0;
				vomitBossFireEnd = true;
			}
			enemy.State = E_ATTACK;
			if (worldTimeCount % 20 == 0) vomitBossAttackFrameX++;
			if (vomitBossAttackFrameX >= IMAGEMANAGER->findImage("보스_대기")->getMaxFrameX()) vomitBossAttackFrameX = 9;
			if (vomitBossAttackFrameX == 9)
			{
				if (worldTimeCount % 7 == 0) vomitBossFireFrameX++;
				if (vomitBossFireFrameX > IMAGEMANAGER->findImage("보스_불길1")->getMaxFrameX()) vomitBossFireFrameX = 0;
				if (vomitBossFireFrameX > IMAGEMANAGER->findImage("보스_불꽃2")->getMaxFrameX()) vomitBossFireFrameX = 0;
			}
		}

		// 300초 이상이 되면 End는 true / fire 시간은 초기화
		if (vomitBossFireEnd)
		{
			vomitBossFireEndTime++;
			if (vomitBossFireEndTime > 300)
			{
				vomitBossFireEndTime = 0;
				vomitBossFireEnd = false;
			}
		}
#pragma endregion

#pragma region	보스 & 플레이어 충돌
		RECT BPtemp;
		if (player.FrameY == 0)
		{
			if (IntersectRect(&BPtemp, &player.AttackRc, &vomitBossRC))
			{
				if (enemyMoment.BV_Hp < 400)
				{
					enemyMoment.BV_Hp++;
				}
			}
		}

		if (player.FrameY == 1)
		{
			if (IntersectRect(&BPtemp, &player.AttackRc, &vomitBossRC))
			{
				if (enemyMoment.BV_Hp < 400)
				{
					enemyMoment.BV_Hp++;
				}
			}
		}
	}
	
	if (enemyMoment.BV_Hp == 400)
	{
		enemyMoment.BV_Die = true;
		enemy.State = E_DIE;
		if (worldTimeCount % 13 == 0) vomitBossDieFrameX1++;
		if (vomitBossDieFrameX1 > IMAGEMANAGER->findImage("보스_죽음1")->getMaxFrameX()) vomitBossDieFrameX1 = 1;

		if (vomitBossDieFrameX1 == 1)
		{
			if (worldTimeCount % 13 == 0) vomitBossDieFrameX2++;
			if (vomitBossDieFrameX2 > IMAGEMANAGER->findImage("보스_죽음2")->getMaxFrameX()) vomitBossDieFrameX2 = 9;
		}
	}
#pragma endregion
	vomitBossRC = RectMakeCenter(vomitBossX, vomitBossY, 141, 140);
	vomitBossTwoRC = RectMakeCenter(vomitBossX, vomitBossY, 400, 140);
}

void Unit::bossVomitRender(void)
{
	//DrawRectMake(getMemDC(), vomitBossTwoRC);
	//DrawRectMake(getMemDC(), vomitBossRC);
#pragma region 보스 랜더
	if (enemy.State == E_WALK)
	{
		if (vomitBossFrameY == 1)	IMAGEMANAGER->findImage("보스_걷기")->frameRender(getMemDC(), vomitBossRC.left - 100, vomitBossRC.top - 283, vomitBossFrameX, vomitBossFrameY);
		else if (vomitBossFrameY == 0) IMAGEMANAGER->findImage("보스_걷기")->frameRender(getMemDC(), vomitBossRC.left - 180, vomitBossRC.top - 283, vomitBossFrameX, vomitBossFrameY);
	}

	if (enemy.State == E_ATTACK)
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
	if (enemyMoment.BV_Die)
	{
		if (enemy.State == E_DIE)
		{
			//if (vomitBossFrameY == 1)	IMAGEMANAGER->findImage("보스_죽음1")->frameRender(getMemDC(), vomitBossRC.left - 300, vomitBossRC.top - 300, vomitBossDieFrameX1, vomitBossFrameY);
			//else if (vomitBossFrameY == 0) IMAGEMANAGER->findImage("보스_죽음1")->frameRender(getMemDC(), vomitBossRC.left - 400, vomitBossRC.top - 300, vomitBossDieFrameX1, vomitBossFrameY);

			if (vomitBossFrameY == 1)	IMAGEMANAGER->findImage("보스_죽음2")->frameRender(getMemDC(), vomitBossRC.left - 300, vomitBossRC.top - 300, vomitBossDieFrameX2, vomitBossFrameY);
			else if (vomitBossFrameY == 0) IMAGEMANAGER->findImage("보스_죽음2")->frameRender(getMemDC(), vomitBossRC.left - 400, vomitBossRC.top - 300, vomitBossDieFrameX2, vomitBossFrameY);
			
		}
	}
#pragma endregion

}