#include "Stdafx.h"
#include "Unit.h"

void Unit::enemyInit(void)
{
#pragma region ���� ���� �ʱ�ȭ
	zombie.X = 0;
	zombie.Y = 570;
	zombie.Rc = RectMakeCenter(zombie.X, zombie.Y, 55, 105);
	zombie.FrameX = zombie.FrameY = zombie.DieFrameX = 0;

	zombie.Hp = 0;
	zombie.Die = false;
	//SOUNDMANAGER->addSound("���", "���", true, true);
	//SOUNDMANAGER->addSound("���", "���", false, false);

#pragma endregion
}

void Unit::enemyUpdate(void)
{
#pragma region ���� �̵�
	if (!player.Inventory)
	{
		if (bgMove >= 0)
		{
			if (worldTimeCount % 15 == 0) zombie.FrameX++;
			if (zombie.FrameX > IMAGEMANAGER->findImage("����_�ȱ�")->getMaxFrameX()) zombie.FrameX = 0;
		}

		// ���� ���������� ����
		if (player.X > zombie.Rc.right && !zombie.Die)
		{
			zombie.FrameY = 1;
			zombie.X += 1;
		}

		// ���� �������� ����
		else if (player.X < zombie.Rc.right && !zombie.Die)
		{
			zombie.FrameY = 0;
			zombie.X -= 1;
		}
	}
#pragma endregion

#pragma region ������ �浹
	RECT temp;
	if (!player.Right)
	{
		if (IntersectRect(&temp, &player.AttackRc, &zombie.Rc))
		{
			if (temp.right - temp.left > 50)
			{
				zombie.Rc.left -= 100;
				zombie.Rc.right -= 100;


				if (zombie.Hp < 20) zombie.Hp++;
			}
		}
	}
	else if (player.Right)
	{
		if (IntersectRect(&temp, &player.AttackRc, &zombie.Rc))
		{
			if (temp.right - temp.left > 50)
			{
				zombie.Rc.left += 100;
				zombie.Rc.right += 100;

				if (zombie.Hp < 20) zombie.Hp++;
			}
		}
	}

	if (zombie.Hp == 20)
	{
		zombie.Die = true;
		//if (!player.Right) if (!zombie.Die) IMAGEMANAGER->findImage("����_�ȱ�")->frameRender(getMemDC(), zombie.Rc.left, zombie.Rc.top - 8, zombie.FrameX, 2);
		//if (player.Right) if (!zombie.Die) IMAGEMANAGER->findImage("����_�ȱ�")->frameRender(getMemDC(), zombie.Rc.left, zombie.Rc.top - 8, zombie.FrameX, 3);
		if (zombie.DieFrameX > IMAGEMANAGER->findImage("����_����")->getMaxFrameX()) zombie.DieFrameX = 2;
	}
#pragma endregion

	zombie.Rc = RectMakeCenter(zombie.X, zombie.Y, 55, 105);

}

void Unit::enemyRender(void)
{
	//DrawRectMake(getMemDC(), zombieRc);
#pragma region ���� ����
	if (zombie.Die)
	{
		IMAGEMANAGER->findImage("����_����")->frameRender(getMemDC(), zombie.Rc.left, zombie.Rc.top, zombie.DieFrameX, zombie.FrameY);
	}
	else
	{
		if (zombie.FrameY == 1)	IMAGEMANAGER->findImage("����_�ȱ�")->frameRender(getMemDC(),
			zombie.Rc.left, zombie.Rc.top - 8, zombie.FrameX, zombie.FrameY);
		else if (zombie.FrameY == 0) IMAGEMANAGER->findImage("����_�ȱ�")->frameRender(getMemDC(),
			zombie.Rc.left, zombie.Rc.top - 8, zombie.FrameX, zombie.FrameY);
	}
#pragma endregion
}