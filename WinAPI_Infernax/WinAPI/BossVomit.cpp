#include "Stdafx.h"
#include "Unit.h"

void Unit::bossVomitInit(void)
{
	vomitBossX = 0.0f;
	vomitBossY = 552.0f;
	vomitBossRC = RectMakeCenter(vomitBossX, vomitBossY, 141, 140);
	vomitBossTwoRC = RectMakeCenter(vomitBossX, vomitBossY, 200, 140);

	vomitBossFrameX = vomitBossFrameY = vomitBossAttackFrameX = vomitBossAttackFrameY = vomitBossDieFrameX = vomitBossDieFrameY = 0;

	EnemyState = E_WALK;
	enemyMoment.BV_Hp = 0;
	enemyMoment.BV_Die = false;
}

void Unit::bossVomitUpdate(void)
{
	if (worldTimeCount % 25 == 0) vomitBossFrameX++;
	if (vomitBossFrameX > IMAGEMANAGER->findImage("����_�ȱ�")->getMaxFrameX()) vomitBossFrameX = 0;

	// ���� ���������� ����
	if (playerX > vomitBossRC.right && !enemyMoment.BV_Die)
	{
		EnemyState = E_WALK;
		vomitBossFrameY = 0;
		if (worldTimeCount % 2 == 0) vomitBossX += 2.0f;
		//vomitBossRC.right += 1;
	}

	// ���� �������� ����
	else if (playerX < vomitBossRC.left && !enemyMoment.BV_Die)
	{
		EnemyState = E_WALK;
		vomitBossFrameY = 1;
		if (worldTimeCount % 2 == 0) vomitBossX -= 2.0f;

		//if (playerX < WINSIZE_X / 2)
		//{
		//	if (enemyMoment.BV_Die && bgMove != 890.0f)
		//	{
		//		vomitBossRC.left -= 2;
		//		vomitBossRC.right -= 2;
		//	}
		//	bgMove -= 2.0f;
		//}
		//else
		//{
		//	playerX += 2;
		//	playerAttackX += 2;
		//}

		if (bgMove < 0) bgMove = 0.0f;
		if (bgMove == 0.0f)
		{
			playerX -= 2;
			playerAttackX -= 2;
		}

		//vomitBossRC.right -= 1;
	}

	RECT Btemp;
	if (playerFrameY == 0)
	{
		if (IntersectRect(&Btemp, &playerRC, &vomitBossTwoRC))
		{
			EnemyState = E_ATTACK;
			if (worldTimeCount % 20 == 0) vomitBossAttackFrameX++;
			if (vomitBossAttackFrameX >= IMAGEMANAGER->findImage("����_���")->getMaxFrameX()) vomitBossAttackFrameX = 9;
			if (vomitBossAttackFrameX == 9)
			{
				if (vomitBossAttackFrameX >= IMAGEMANAGER->findImage("����_�ұ�1")->getMaxFrameX()) vomitBossAttackFrameX = 0;
				if (vomitBossAttackFrameX >= IMAGEMANAGER->findImage("����_�Ҳ�2")->getMaxFrameX()) vomitBossAttackFrameX = 0;
			}
		}
	}
	else if (playerFrameY == 1)
	{
		if (IntersectRect(&Btemp, &playerRC, &vomitBossTwoRC))
		{
			EnemyState = E_ATTACK;
			if (worldTimeCount % 20 == 0) vomitBossAttackFrameX++;
			if (vomitBossAttackFrameX >= IMAGEMANAGER->findImage("����_���")->getMaxFrameX()) vomitBossAttackFrameX = 9;
			if (vomitBossAttackFrameX == 9)
			{
				if (vomitBossAttackFrameX >= IMAGEMANAGER->findImage("����_�ұ�1")->getMaxFrameX()) vomitBossAttackFrameX = 0;
				if (vomitBossAttackFrameX >= IMAGEMANAGER->findImage("����_�Ҳ�2")->getMaxFrameX()) vomitBossAttackFrameX = 0;
			}

		}
	}

	cout << bgMove << endl;

	vomitBossRC = RectMakeCenter(vomitBossX, vomitBossY, 141, 140);
	vomitBossTwoRC = RectMakeCenter(vomitBossX, vomitBossY, 200, 140);
}

void Unit::bossVomitRender(void)
{
	DrawRectMake(getMemDC(), vomitBossTwoRC);
	DrawRectMake(getMemDC(), vomitBossRC);
	IMAGEMANAGER->findImage("����_�ұ�1")->frameRender(getMemDC(), vomitBossRC.left - 100, vomitBossRC.top - 283, vomitBossAttackFrameX, vomitBossFrameY);
	IMAGEMANAGER->findImage("����_�Ҳ�2")->frameRender(getMemDC(), vomitBossRC.left - 100, vomitBossRC.top - 283, vomitBossAttackFrameX, vomitBossFrameY);


	if (EnemyState == E_WALK)
	{
		if (vomitBossFrameY == 1)	IMAGEMANAGER->findImage("����_�ȱ�")->frameRender(getMemDC(), vomitBossRC.left - 100, vomitBossRC.top - 283, vomitBossFrameX, vomitBossFrameY);
		else if (vomitBossFrameY == 0) IMAGEMANAGER->findImage("����_�ȱ�")->frameRender(getMemDC(), vomitBossRC.left - 180, vomitBossRC.top - 283, vomitBossFrameX, vomitBossFrameY);
	}

	if (EnemyState == E_ATTACK)
	{
		if (vomitBossFrameY == 1)	IMAGEMANAGER->findImage("����_���")->frameRender(getMemDC(), vomitBossRC.left - 100, vomitBossRC.top - 283, vomitBossAttackFrameX, vomitBossFrameY);
		else if (vomitBossFrameY == 0) IMAGEMANAGER->findImage("����_���")->frameRender(getMemDC(), vomitBossRC.left - 180, vomitBossRC.top - 283, vomitBossAttackFrameX, vomitBossFrameY);
	
		if (vomitBossAttackFrameX == 9)
		{
			if (vomitBossFrameY == 1)	IMAGEMANAGER->findImage("����_�ұ�1")->frameRender(getMemDC(), vomitBossRC.left - 100, vomitBossRC.top - 283, vomitBossAttackFrameX, vomitBossFrameY);
			else if (vomitBossFrameY == 0) IMAGEMANAGER->findImage("����_�ұ�1")->frameRender(getMemDC(), vomitBossRC.left - 180, vomitBossRC.top - 283, vomitBossAttackFrameX, vomitBossFrameY);

			if (vomitBossFrameY == 1)	IMAGEMANAGER->findImage("����_�Ҳ�2")->frameRender(getMemDC(), vomitBossRC.left - 100, vomitBossRC.top - 283, vomitBossAttackFrameX, vomitBossFrameY);
			else if (vomitBossFrameY == 0) IMAGEMANAGER->findImage("����_�Ҳ�2")->frameRender(getMemDC(), vomitBossRC.left - 180, vomitBossRC.top - 283, vomitBossAttackFrameX, vomitBossFrameY);
		}
	}
}