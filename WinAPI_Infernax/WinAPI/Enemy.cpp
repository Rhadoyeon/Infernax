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
		if (zombieFrameX > IMAGEMANAGER->findImage("Á»ºñ_°È±â")->getMaxFrameX()) zombieFrameX = 0;
	}

	// Á»ºñ ¿À¸¥ÂÊÀ¸·Î ¹«ºù
	if (playerX > zombieRC.right&& !enemyMoment.E_Die)
	{
		zombieFrameY = 1;
		zombieRC.left += 1;
		zombieRC.right += 1;
	}

	// Á»ºñ ¿ÞÂÊÀ¸·Î ¹«ºù
	else if (playerX < zombieRC.left&&!enemyMoment.E_Die)
	{
		zombieFrameY = 0;
		zombieRC.left -= 1;
		zombieRC.right -= 1;
	}

	if (enemyMoment.E_Hp == 3)
	{
		enemyMoment.E_Die = true;
		if (zombieDieFrameX > IMAGEMANAGER->findImage("Á»ºñ_Á×À½")->getMaxFrameX()) zombieDieFrameX = 2;
		if (zombieDieFrameX == 2);
	}

}

void Unit::enemyRender(void)
{
	//DrawRectMake(getMemDC(), zombieRc);
	


	if (enemyMoment.E_Die)
	{
		IMAGEMANAGER->findImage("Á»ºñ_Á×À½")->frameRender(getMemDC(), zombieRC.left, zombieRC.top, zombieDieFrameX, zombieFrameY);

	}
	else
	{
		if (zombieFrameY == 1)	IMAGEMANAGER->findImage("Á»ºñ_°È±â")->frameRender(getMemDC(),
			zombieRC.left, zombieRC.top - 8, zombieFrameX, zombieFrameY);
		else if (zombieFrameY == 0) IMAGEMANAGER->findImage("Á»ºñ_°È±â")->frameRender(getMemDC(),
			zombieRC.left, zombieRC.top - 8, zombieFrameX, zombieFrameY);
	}
}