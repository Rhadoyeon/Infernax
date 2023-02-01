#include "Stdafx.h"
#include "Unit.h"

void Unit::bossVomitInit(void)
{
#pragma region �ʱ�ȭ
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
#pragma region ���� �̵�
	if (!enemyMoment.BV_Die)
	{
		if (worldTimeCount % 25 == 0) vomitBossFrameX++;
		if (vomitBossFrameX > IMAGEMANAGER->findImage("����_�ȱ�")->getMaxFrameX()) vomitBossFrameX = 0;

		// ���� ���������� ����
		if (!vomitBossFireBoss)
		{
			if (player.X > vomitBossRC.right && !enemyMoment.BV_Die)
			{
				enemy.State = E_WALK;
				vomitBossFrameY = 0;
				if (worldTimeCount % 2 == 0) vomitBossX += 1.5f;
			}

			// ���� �������� ����
			else if (player.X < vomitBossRC.left && !enemyMoment.BV_Die)
			{
				enemy.State = E_WALK;
				vomitBossFrameY = 1;
				if (worldTimeCount % 2 == 0) vomitBossX -= 1.5f;
			}
		}
#pragma endregion

#pragma region ���� ��ų & �÷��̾� �浹
		RECT Btemp;
		if (player.FrameY == 0)
		{
			if (IntersectRect(&Btemp, &player.Rc, &vomitBossTwoRC) && !vomitBossFireEnd && !vomitBossFireBoss)
			{
				// �浹�ɶ� fire�� true / �ð�, ������ �ʱ�ȭ
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
				if (vomitBossAttackFrameX >= IMAGEMANAGER->findImage("����_���")->getMaxFrameX()) vomitBossAttackFrameX = 9;

				if (vomitBossAttackFrameX == 9)
				{
					if (worldTimeCount % 7 == 0) vomitBossFireFrameX++;
					if (vomitBossFireFrameX > IMAGEMANAGER->findImage("����_�ұ�1")->getMaxFrameX()) vomitBossFireFrameX = 0;
					if (vomitBossFireFrameX > IMAGEMANAGER->findImage("����_�Ҳ�2")->getMaxFrameX()) vomitBossFireFrameX = 0;
				}
			}
		}

		// �浹�� true�϶� �� true�༭ �� �߻�
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
			if (vomitBossAttackFrameX >= IMAGEMANAGER->findImage("����_���")->getMaxFrameX()) vomitBossAttackFrameX = 9;
			if (vomitBossAttackFrameX == 9)
			{
				if (worldTimeCount % 7 == 0) vomitBossFireFrameX++;
				if (vomitBossFireFrameX > IMAGEMANAGER->findImage("����_�ұ�1")->getMaxFrameX()) vomitBossFireFrameX = 0;
				if (vomitBossFireFrameX > IMAGEMANAGER->findImage("����_�Ҳ�2")->getMaxFrameX()) vomitBossFireFrameX = 0;
			}
		}

		// 300�� �̻��� �Ǹ� End�� true / fire �ð��� �ʱ�ȭ
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

#pragma region	���� & �÷��̾� �浹
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
		if (vomitBossDieFrameX1 > IMAGEMANAGER->findImage("����_����1")->getMaxFrameX()) vomitBossDieFrameX1 = 1;

		if (vomitBossDieFrameX1 == 1)
		{
			if (worldTimeCount % 13 == 0) vomitBossDieFrameX2++;
			if (vomitBossDieFrameX2 > IMAGEMANAGER->findImage("����_����2")->getMaxFrameX()) vomitBossDieFrameX2 = 9;
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
#pragma region ���� ����
	if (enemy.State == E_WALK)
	{
		if (vomitBossFrameY == 1)	IMAGEMANAGER->findImage("����_�ȱ�")->frameRender(getMemDC(), vomitBossRC.left - 100, vomitBossRC.top - 283, vomitBossFrameX, vomitBossFrameY);
		else if (vomitBossFrameY == 0) IMAGEMANAGER->findImage("����_�ȱ�")->frameRender(getMemDC(), vomitBossRC.left - 180, vomitBossRC.top - 283, vomitBossFrameX, vomitBossFrameY);
	}

	if (enemy.State == E_ATTACK)
	{
		if (vomitBossFrameY == 1)	IMAGEMANAGER->findImage("����_���")->frameRender(getMemDC(), vomitBossRC.left - 100, vomitBossRC.top - 283, vomitBossAttackFrameX, vomitBossFrameY);
		else if (vomitBossFrameY == 0) IMAGEMANAGER->findImage("����_���")->frameRender(getMemDC(), vomitBossRC.left - 180, vomitBossRC.top - 283, vomitBossAttackFrameX, vomitBossFrameY);
	
		if (vomitBossAttackFrameX == 9)
		{
			if (vomitBossFrameY == 1)	IMAGEMANAGER->findImage("����_�ұ�1")->frameRender(getMemDC(), vomitBossRC.left - 125, vomitBossRC.top + 12, vomitBossFireFrameX, vomitBossFrameY);
			else if (vomitBossFrameY == 0) IMAGEMANAGER->findImage("����_�ұ�1")->frameRender(getMemDC(), vomitBossRC.left + 195, vomitBossRC.top + 12, vomitBossFireFrameX, vomitBossFrameY);

			if (vomitBossFrameY == 1)	IMAGEMANAGER->findImage("����_�Ҳ�2")->frameRender(getMemDC(), vomitBossRC.left - 115 , vomitBossRC.top + 52, vomitBossFireFrameX, vomitBossFrameY);
			else if (vomitBossFrameY == 0) IMAGEMANAGER->findImage("����_�Ҳ�2")->frameRender(getMemDC(), vomitBossRC.left + 240, vomitBossRC.top + 52, vomitBossFireFrameX, vomitBossFrameY);
			
			if (vomitBossFrameY == 1)	IMAGEMANAGER->findImage("����_�Ҳ�2")->frameRender(getMemDC(), vomitBossRC.left - 170, vomitBossRC.top + 52, vomitBossFireFrameX, vomitBossFrameY);
			else if (vomitBossFrameY == 0) IMAGEMANAGER->findImage("����_�Ҳ�2")->frameRender(getMemDC(), vomitBossRC.left + 300, vomitBossRC.top + 52, vomitBossFireFrameX, vomitBossFrameY);
		}		
	}
	if (enemyMoment.BV_Die)
	{
		if (enemy.State == E_DIE)
		{
			//if (vomitBossFrameY == 1)	IMAGEMANAGER->findImage("����_����1")->frameRender(getMemDC(), vomitBossRC.left - 300, vomitBossRC.top - 300, vomitBossDieFrameX1, vomitBossFrameY);
			//else if (vomitBossFrameY == 0) IMAGEMANAGER->findImage("����_����1")->frameRender(getMemDC(), vomitBossRC.left - 400, vomitBossRC.top - 300, vomitBossDieFrameX1, vomitBossFrameY);

			if (vomitBossFrameY == 1)	IMAGEMANAGER->findImage("����_����2")->frameRender(getMemDC(), vomitBossRC.left - 300, vomitBossRC.top - 300, vomitBossDieFrameX2, vomitBossFrameY);
			else if (vomitBossFrameY == 0) IMAGEMANAGER->findImage("����_����2")->frameRender(getMemDC(), vomitBossRC.left - 400, vomitBossRC.top - 300, vomitBossDieFrameX2, vomitBossFrameY);
			
		}
	}
#pragma endregion

}