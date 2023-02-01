#include "Stdafx.h"
#include "Unit.h"

void Unit::bossVomitInit(void)
{
	vomitBossX = 0.0f;
	vomitBossY = 552.0f;
	vomitBossRC = RectMakeCenter(vomitBossX, vomitBossY, 141, 140);
	vomitBossTwoRC = RectMakeCenter(vomitBossX, vomitBossY, 400, 140);

	vomitBossFrameX = vomitBossFrameY = vomitBossAttackFrameX = vomitBossAttackFrameY = vomitBossDieFrameX = vomitBossDieFrameY = vomitBossFireFrameX = vomitBossFireFrameY = 0;

	enemy.State = E_WALK;
	enemyMoment.BV_Hp = 0;
	enemyMoment.BV_Die = false;

	_fireBoss = false;
	_fireTime = 0;
	_fireEnd = false;
	_fireEndTime = 0;
}

void Unit::bossVomitUpdate(void)
{
	if (worldTimeCount % 25 == 0) vomitBossFrameX++;
	if (vomitBossFrameX > IMAGEMANAGER->findImage("보스_걷기")->getMaxFrameX()) vomitBossFrameX = 0;

	// 보스 오른쪽으로 무빙
	if (!_fireBoss)
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

#pragma region 보스 & 플레이어 충돌
	RECT Btemp;
	if (player.FrameY == 0)
	{
		if (IntersectRect(&Btemp, &player.Rc, &vomitBossTwoRC) && !_fireEnd && !_fireBoss)
		{
			_fireBoss = true;
			_fireTime = 0;
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

	//충돌이 트루일때 불쏘기 트루줘서 불발싸
	if (_fireBoss)
	{
		_fireTime++;
		if (_fireTime > 300)
		{
			_fireBoss = false;
			_fireTime = 0;
			_fireEnd = true;
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

	if (_fireEnd)
	{
		_fireEndTime++;
		if (_fireEndTime > 300)
		{
			_fireEndTime = 0;
			_fireEnd = false;
		}
	}
#pragma endregion

	vomitBossRC = RectMakeCenter(vomitBossX, vomitBossY, 141, 140);
	vomitBossTwoRC = RectMakeCenter(vomitBossX, vomitBossY, 400, 140);
}

void Unit::bossVomitRender(void)
{
	DrawRectMake(getMemDC(), vomitBossTwoRC);
	DrawRectMake(getMemDC(), vomitBossRC);

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
}