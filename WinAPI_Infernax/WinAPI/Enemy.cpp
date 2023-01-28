#include "Stdafx.h"
#include "Unit.h"

void Unit::enemyInit(void)
{
	zombieX = 0;
	zombieY = 570;
	zombieRc = RectMakeCenter(zombieX, zombieY, 55, 105);
}

void Unit::enemyUpdate(void)
{
	if (bgMove >= 0)
	{
		if (worldTimeCount % 15 == 0) zombieFrameX++;
		if (zombieFrameX > IMAGEMANAGER->findImage("좀비")->getMaxFrameX()) zombieFrameX = 0;
	}

	if (playerX > zombieRc.right)
	{
		zombieFrameY = 1;
		zombieRc.left += 1;
		zombieRc.right += 1;
	}
	else if (playerX < zombieRc.left)
	{
		zombieFrameY = 0;
		zombieRc.left -= 1;
		zombieRc.right -= 1;
	}
}

void Unit::enemyRender(void)
{
	DrawRectMake(getMemDC(), zombieRc);
	
	if (zombieFrameY == 1)	IMAGEMANAGER->findImage("좀비")->frameRender(getMemDC(),
		zombieRc.left, zombieRc.top - 8, zombieFrameX, zombieFrameY);
	else if (zombieFrameY == 0) IMAGEMANAGER->findImage("좀비")->frameRender(getMemDC(),
		zombieRc.left, zombieRc.top - 8, zombieFrameX, zombieFrameY);

}