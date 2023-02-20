#include "Stdafx.h"
#include "Unit.h"

void Unit::enemyInit(void)
{
#pragma region 좀비 변수 초기화
	zombie.X = 0;
	zombie.Y = 570;
	zombie.Rc = RectMakeCenter(zombie.X, zombie.Y, 55, 105);
	zombie.FrameX = zombie.FrameY = zombie.DieFrameX = 0;

	zombie.Hp = 0;
	zombie.Die = false;
	//SOUNDMANAGER->addSound("경로", "경로", true, true);
	//SOUNDMANAGER->addSound("경로", "경로", false, false);

#pragma endregion
}

void Unit::enemyUpdate(void)
{
#pragma region 좀비 이동
	if (!player.Inventory)
	{
		if (bgMove >= 0)
		{
			if (worldTimeCount % 15 == 0) zombie.FrameX++;
			if (zombie.FrameX > IMAGEMANAGER->findImage("좀비_걷기")->getMaxFrameX()) zombie.FrameX = 0;
		}

		// 좀비 오른쪽으로 무빙
		if (player.X > zombie.Rc.right && !zombie.Die)
		{
			zombie.FrameY = 1;
			zombie.X += 1;
		}

		// 좀비 왼쪽으로 무빙
		else if (player.X < zombie.Rc.right && !zombie.Die)
		{
			zombie.FrameY = 0;
			zombie.X -= 1;
		}
	}
#pragma endregion

#pragma region 적과의 충돌
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
		//if (!player.Right) if (!zombie.Die) IMAGEMANAGER->findImage("좀비_걷기")->frameRender(getMemDC(), zombie.Rc.left, zombie.Rc.top - 8, zombie.FrameX, 2);
		//if (player.Right) if (!zombie.Die) IMAGEMANAGER->findImage("좀비_걷기")->frameRender(getMemDC(), zombie.Rc.left, zombie.Rc.top - 8, zombie.FrameX, 3);
		if (zombie.DieFrameX > IMAGEMANAGER->findImage("좀비_죽음")->getMaxFrameX()) zombie.DieFrameX = 2;
	}
#pragma endregion

	zombie.Rc = RectMakeCenter(zombie.X, zombie.Y, 55, 105);

}

void Unit::enemyRender(void)
{
	//DrawRectMake(getMemDC(), zombieRc);
#pragma region 좀비 랜더
	if (zombie.Die)
	{
		IMAGEMANAGER->findImage("좀비_죽음")->frameRender(getMemDC(), zombie.Rc.left, zombie.Rc.top, zombie.DieFrameX, zombie.FrameY);
	}
	else
	{
		if (zombie.FrameY == 1)	IMAGEMANAGER->findImage("좀비_걷기")->frameRender(getMemDC(),
			zombie.Rc.left, zombie.Rc.top - 8, zombie.FrameX, zombie.FrameY);
		else if (zombie.FrameY == 0) IMAGEMANAGER->findImage("좀비_걷기")->frameRender(getMemDC(),
			zombie.Rc.left, zombie.Rc.top - 8, zombie.FrameX, zombie.FrameY);
	}
#pragma endregion
}