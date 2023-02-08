#include "Stdafx.h"
#include "Unit.h"

void Unit::BelphegorInit(void)
{
	belphegor.FrameX = belphegor.FrameY = belphegor.JavelinTrowFrameX = belphegor.JavelinFrameX = belphegor.JavelinTrowFrameX = 0;
	belphegor.BelphegorState = E_WALK;

	belphegor.JavelinX = belphegor.JavelinY = 0;
	belphegor.X = belphegor.Y = 0;
	belphegor.weaponGun = false;
}

void Unit::BelphegorUpdate(void)
{
	if (player.X < 150)
	{
		player.State = P_WALK;
		player.X += 2;

		if (player.X == 150)
		{
			player.State = P_STAND;
		}
	}

	if (player.X >= 150)
	{
		belphegor.BelphegorState = E_WALK;
		if (worldTimeCount % 15 == 0) belphegor.FrameX++;
		if (belphegor.FrameX > IMAGEMANAGER->findImage("벨페고르_컷씬")->getMaxFrameX()) belphegor.FrameX = 12;
	}

	if (belphegor.FrameX == 12)
	{
		belphegor.BelphegorState = E_ATTACK;
		if (worldTimeCount % 15 == 0) belphegor.JavelinTrowFrameX++;
		if (belphegor.JavelinTrowFrameX > IMAGEMANAGER->findImage("벨페고르_창던지기")->getMaxFrameX()) belphegor.JavelinTrowFrameX = 4;
		
		if (belphegor.JavelinTrowFrameX >= 3)
		{
			if (worldTimeCount % 7 == 0) belphegor.JavelinFrameX++;
			if (belphegor.JavelinFrameX > IMAGEMANAGER->findImage("벨페고르_창")->getMaxFrameX()) belphegor.JavelinFrameX = 4;
		}

		if (belphegor.JavelinTrowFrameX >= 3)	belphegor.JavelinX -= 2.0f;
		if (belphegor.JavelinTrowFrameX == 4)	belphegor.JavelinX += 2.0f;
	}

	if (belphegor.JavelinFrameX == 4)
	{
		if (worldTimeCount % 7 == 0) belphegor.FrameX++;
		if (belphegor.JavelinFrameX > IMAGEMANAGER->findImage("벨페고르_창")->getMaxFrameX()) belphegor.JavelinFrameX = 4;
	}
}

void Unit::BelphegorRender(void)
{
	if (belphegor.BelphegorState == E_WALK)
		IMAGEMANAGER->findImage("벨페고르_컷씬")->frameRender(getMemDC(), belphegor.X +620, belphegor.Y +200, belphegor.FrameX, 0);
	if (belphegor.BelphegorState == E_ATTACK)
	{
		IMAGEMANAGER->findImage("벨페고르_창던지기")->frameRender(getMemDC(), belphegor.X + 620, belphegor.Y + 240, belphegor.JavelinTrowFrameX, 0);
		if (belphegor.JavelinTrowFrameX >= 3)	IMAGEMANAGER->findImage("벨페고르_창")->frameRender(getMemDC(), belphegor.JavelinX + 150, belphegor.JavelinY + 240, belphegor.JavelinFrameX, 0);
	}

}
