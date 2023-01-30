#include "Stdafx.h"
#include "Unit.h"

void Unit::enemyInit(void)
{
	zombieX = 0;
	zombieY = 570;
	zombieRC = RectMakeCenter(zombieX, zombieY, 55, 105);
	zombieFrameX = zombieFrameY = zombieDieFrameX = 0;

	enemyMoment.E_Hp = 0;
	enemyMoment.E_Die = false;
}

void Unit::enemyUpdate(void)
{
	if (bgMove >= 0)
	{
		if (worldTimeCount % 15 == 0) zombieFrameX++;
		if (zombieFrameX > IMAGEMANAGER->findImage("좀비_걷기")->getMaxFrameX()) zombieFrameX = 0;
	}

	// 좀비 오른쪽으로 무빙
	if (playerX > zombieRC.right && !enemyMoment.E_Die)
	{
		zombieFrameY = 1;
		zombieX += 1;
		//zombieRC.right += 1;
	}

	// 좀비 왼쪽으로 무빙
	else if (playerX < zombieRC.right && !enemyMoment.E_Die)
	{
		zombieFrameY = 0;
		zombieX -= 1;
		//zombieRC.right -= 1;
	}

	if (enemyMoment.E_Hp == 3)
	{
		enemyMoment.E_Die = true;
		if (zombieDieFrameX > IMAGEMANAGER->findImage("좀비_죽음")->getMaxFrameX()) zombieDieFrameX = 2;
	}

	zombieRC = RectMakeCenter(zombieX, zombieY, 55, 105);

}

void Unit::enemyRender(void)
{
	//DrawRectMake(getMemDC(), zombieRc);
	


	if (enemyMoment.E_Die)
	{
		IMAGEMANAGER->findImage("좀비_죽음")->frameRender(getMemDC(), zombieRC.left, zombieRC.top, zombieDieFrameX, zombieFrameY);

	}
	else
	{
		if (zombieFrameY == 1)	IMAGEMANAGER->findImage("좀비_걷기")->frameRender(getMemDC(),
			zombieRC.left, zombieRC.top - 8, zombieFrameX, zombieFrameY);
		else if (zombieFrameY == 0) IMAGEMANAGER->findImage("좀비_걷기")->frameRender(getMemDC(),
			zombieRC.left, zombieRC.top - 8, zombieFrameX, zombieFrameY);
	}
}