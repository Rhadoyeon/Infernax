#include "Stdafx.h"
#include "Unit.h"

void Unit::bossVomitInit(void)
{
#pragma region vomit boss �ʱ�ȭ
	vomitBoss.X = 0.0f;
	vomitBoss.Y = 552.0f;

	vomitBoss.FrameX = vomitBoss.FrameY = vomitBoss.AttackFrameX = vomitBoss.DieFrameX1 = vomitBoss.DieFrameX2 = vomitBoss.FireFrameX = 0;

	vomitBoss.State = E_WALK;
	vomitBoss.Hp = 0;
	vomitBoss.Die = false;
	vomitBoss.DieChange = false;

	vomitBoss.FireBoss = false;
	vomitBoss.FireTime = 0;
	vomitBoss.FireEnd = false;
	vomitBoss.FireEndTime = 0;
#pragma endregion
}

void Unit::bossVomitUpdate(void)
{
#pragma region ���� �̵�
	if (!vomitBoss.Die)
	{
		if (worldTimeCount % 25 == 0) vomitBoss.FrameX++;
		if (vomitBoss.FrameX > IMAGEMANAGER->findImage("����_�ȱ�")->getMaxFrameX()) vomitBoss.FrameX = 0;

		// ���� ���������� ����
		if (!vomitBoss.FireBoss)
		{
			if (player.X > vomitBoss.OneRc.right && !vomitBoss.Die)
			{
				vomitBoss.State = E_WALK;
				vomitBoss.FrameY = 0;
				if (worldTimeCount % 2 == 0) vomitBoss.X += 1.5f;
			}

			// ���� �������� ����
			else if (player.X < vomitBoss.OneRc.left && !vomitBoss.Die)
			{
				vomitBoss.State = E_WALK;
				vomitBoss.FrameY = 1;
				if (worldTimeCount % 2 == 0) vomitBoss.X -= 1.5f;
			}
		}
#pragma endregion

#pragma region ���� ��ų & �÷��̾� �浹
		RECT Btemp;
		if (player.FrameY == 0)
		{
			if (IntersectRect(&Btemp, &player.Rc, &vomitBoss.TwoRc) && !vomitBoss.FireEnd && !vomitBoss.FireBoss)
			{
				// �浹�ɶ� fire�� true / �ð�, ������ �ʱ�ȭ
				vomitBoss.FireBoss = true;
				vomitBoss.FireTime = 0;
				vomitBoss.AttackFrameX = 0;
			}
		}
		else if (player.FrameY == 1)
		{
			if (IntersectRect(&Btemp, &player.Rc, &vomitBoss.TwoRc))
			{
				vomitBoss.State = E_ATTACK;
				if (worldTimeCount % 20 == 0) vomitBoss.AttackFrameX++;
				if (vomitBoss.AttackFrameX >= IMAGEMANAGER->findImage("����_���")->getMaxFrameX()) vomitBoss.AttackFrameX = 9;

				if (vomitBoss.AttackFrameX == 9)
				{
					if (worldTimeCount % 7 == 0) vomitBoss.FireFrameX++;
					if (vomitBoss.FireFrameX > IMAGEMANAGER->findImage("����_�ұ�1")->getMaxFrameX()) vomitBoss.FireFrameX = 0;
					if (vomitBoss.FireFrameX > IMAGEMANAGER->findImage("����_�Ҳ�2")->getMaxFrameX()) vomitBoss.FireFrameX = 0;
				}
			}
		}

		// �浹�� true�϶� �� true�༭ �� �߻�
		if (vomitBoss.FireBoss)
		{
			vomitBoss.FireTime++;
			if (vomitBoss.FireTime > 300)
			{
				vomitBoss.FireBoss = false;
				vomitBoss.FireTime = 0;
				vomitBoss.FireEnd = true;
			}
			vomitBoss.State = E_ATTACK;
			if (worldTimeCount % 20 == 0) vomitBoss.AttackFrameX++;
			if (vomitBoss.AttackFrameX >= IMAGEMANAGER->findImage("����_���")->getMaxFrameX()) vomitBoss.AttackFrameX = 9;
			if (vomitBoss.AttackFrameX == 9)
			{
				if (worldTimeCount % 7 == 0) vomitBoss.FireFrameX++;
				if (vomitBoss.FireFrameX > IMAGEMANAGER->findImage("����_�ұ�1")->getMaxFrameX()) vomitBoss.FireFrameX = 0;
				if (vomitBoss.FireFrameX > IMAGEMANAGER->findImage("����_�Ҳ�2")->getMaxFrameX()) vomitBoss.FireFrameX = 0;
			}
		}

		// 300�� �̻��� �Ǹ� End�� true / fire �ð��� �ʱ�ȭ
		if (vomitBoss.FireEnd)
		{
			vomitBoss.FireEndTime++;
			if (vomitBoss.FireEndTime > 300)
			{
				vomitBoss.FireEndTime = 0;
				vomitBoss.FireEnd = false;
			}
		}
#pragma endregion

#pragma region	���� & �÷��̾� �浹
		RECT BPtemp;
		if (player.FrameY == 0)
		{
			if (IntersectRect(&BPtemp, &player.AttackRc, &vomitBoss.OneRc))
			{
				if (vomitBoss.Hp < 400)
				{
					vomitBoss.Hp++;
				}
			}
		}

		if (player.FrameY == 1)
		{
			if (IntersectRect(&BPtemp, &player.AttackRc, &vomitBoss.OneRc))
			{
				if (vomitBoss.Hp < 400)
				{
					vomitBoss.Hp++;
				}
			}
		}
	}

	if (vomitBoss.Hp == 400)
	{
		vomitBoss.Die = true;
		vomitBoss.State = E_DIE;
		vomitBoss.FireTime++;
		if (vomitBoss.FireTime < 300)
		{
			if (worldTimeCount % 13 == 0) vomitBoss.DieFrameX1++;
			if (vomitBoss.DieFrameX1 > IMAGEMANAGER->findImage("����_����1")->getMaxFrameX()) vomitBoss.DieFrameX1 = 0;
			vomitBoss.DieChange = true;
		}
	}
	if (vomitBoss.FireTime > 300)
	{
		vomitBoss.DieChange = false;
		if (worldTimeCount % 13 == 0) vomitBoss.DieFrameX2++;
		if (vomitBoss.DieFrameX2 > IMAGEMANAGER->findImage("����_����2")->getMaxFrameX()) vomitBoss.DieFrameX2 = 9;
	}

#pragma endregion
	vomitBoss.OneRc = RectMakeCenter(vomitBoss.X, vomitBoss.Y, 141, 140);
	vomitBoss.TwoRc = RectMakeCenter(vomitBoss.X, vomitBoss.Y, 400, 140);
}

void Unit::bossVomitRender(void)
{
	//DrawRectMake(getMemDC(), vomitBossTwoRC);
	//DrawRectMake(getMemDC(), vomitBossRC);
#pragma region ���� ����
	if (vomitBoss.State == E_WALK)
	{
		if (vomitBoss.FrameY == 1)	IMAGEMANAGER->findImage("����_�ȱ�")->frameRender(getMemDC(), vomitBoss.OneRc.left - 100, vomitBoss.OneRc.top - 283, vomitBoss.FrameX, vomitBoss.FrameY);
		else if (vomitBoss.FrameY == 0) IMAGEMANAGER->findImage("����_�ȱ�")->frameRender(getMemDC(), vomitBoss.OneRc.left - 180, vomitBoss.OneRc.top - 283, vomitBoss.FrameX, vomitBoss.FrameY);
	}

	if (vomitBoss.State == E_ATTACK)
	{
		if (vomitBoss.FrameY == 1)	IMAGEMANAGER->findImage("����_���")->frameRender(getMemDC(), vomitBoss.OneRc.left - 100, vomitBoss.OneRc.top - 283, vomitBoss.AttackFrameX, vomitBoss.FrameY);
		else if (vomitBoss.FrameY == 0) IMAGEMANAGER->findImage("����_���")->frameRender(getMemDC(), vomitBoss.OneRc.left - 180, vomitBoss.OneRc.top - 283, vomitBoss.AttackFrameX, vomitBoss.FrameY);

		if (vomitBoss.AttackFrameX == 9)
		{
			if (vomitBoss.FrameY == 1)	IMAGEMANAGER->findImage("����_�ұ�1")->frameRender(getMemDC(), vomitBoss.OneRc.left - 125, vomitBoss.OneRc.top + 12, vomitBoss.FireFrameX, vomitBoss.FrameY);
			else if (vomitBoss.FrameY == 0) IMAGEMANAGER->findImage("����_�ұ�1")->frameRender(getMemDC(), vomitBoss.OneRc.left + 195, vomitBoss.OneRc.top + 12, vomitBoss.FireFrameX, vomitBoss.FrameY);

			if (vomitBoss.FrameY == 1)	IMAGEMANAGER->findImage("����_�Ҳ�2")->frameRender(getMemDC(), vomitBoss.OneRc.left - 115, vomitBoss.OneRc.top + 52, vomitBoss.FireFrameX, vomitBoss.FrameY);
			else if (vomitBoss.FrameY == 0) IMAGEMANAGER->findImage("����_�Ҳ�2")->frameRender(getMemDC(), vomitBoss.OneRc.left + 240, vomitBoss.OneRc.top + 52, vomitBoss.FireFrameX, vomitBoss.FrameY);

			if (vomitBoss.FrameY == 1)	IMAGEMANAGER->findImage("����_�Ҳ�2")->frameRender(getMemDC(), vomitBoss.OneRc.left - 170, vomitBoss.OneRc.top + 52, vomitBoss.FireFrameX, vomitBoss.FrameY);
			else if (vomitBoss.FrameY == 0) IMAGEMANAGER->findImage("����_�Ҳ�2")->frameRender(getMemDC(), vomitBoss.OneRc.left + 300, vomitBoss.OneRc.top + 52, vomitBoss.FireFrameX, vomitBoss.FrameY);
		}
	}
	if (vomitBoss.Die)
	{
		if (vomitBoss.State == E_DIE)
		{
			if (vomitBoss.DieChange)
			{
				if (vomitBoss.FrameY == 1)	IMAGEMANAGER->findImage("����_����1")->frameRender(getMemDC(), vomitBoss.OneRc.left - 300, vomitBoss.OneRc.top - 300, vomitBoss.DieFrameX1, vomitBoss.FrameY);
				else if (vomitBoss.FrameY == 0) IMAGEMANAGER->findImage("����_����1")->frameRender(getMemDC(), vomitBoss.OneRc.left - 400, vomitBoss.OneRc.top - 300, vomitBoss.DieFrameX1, vomitBoss.FrameY);
			}
			else
			{
				if (vomitBoss.FrameY == 1)	IMAGEMANAGER->findImage("����_����2")->frameRender(getMemDC(), vomitBoss.OneRc.left - 300, vomitBoss.OneRc.top - 300, vomitBoss.DieFrameX2, vomitBoss.FrameY);
				else if (vomitBoss.FrameY == 0) IMAGEMANAGER->findImage("����_����2")->frameRender(getMemDC(), vomitBoss.OneRc.left - 400, vomitBoss.OneRc.top - 300, vomitBoss.DieFrameX2, vomitBoss.FrameY);
			}
		}
	}
#pragma endregion
}