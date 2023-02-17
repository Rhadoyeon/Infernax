#include "Stdafx.h"
#include "Unit.h"

void Unit::LeviathanInit(void)
{
	// 레비아탄
	BlueOceanFrame = 0;
	Leviathan.X = Leviathan.Y = 0;
	Leviathan.FrameX = Leviathan.FrameX1 = Leviathan.FireFrameX = Leviathan.DieFrameX = 0;
	Leviathan.Time = Leviathan.currentTime = 0;
	Leviathan.Pattern = Leviathan.Hp = Leviathan.gravity = 0;
	Leviathan.Down = Leviathan.Die = false;

	// 레이저
	LeviathanLaser.X = LeviathanLaser.Y = 0;
	LeviathanLaser.LaserFrameX = LeviathanLaser.LaserFrameX1 = 0;
	LeviathanLaser.shot = false;
	LeviathanLaser.change = true;
}

void Unit::LeviathanUpdate(void)
{
	if (worldTimeCount % 30 == 0) BlueOceanFrame++;
	if (BlueOceanFrame > IMAGEMANAGER->findImage("블루오션")->getMaxFrameX()) BlueOceanFrame = 0;

	if (Leviathan.Pattern == 0)
	{

	}

}

void Unit::LeviathanRender(void)
{
	

	//if(Leviathan.Die)
	//IMAGEMANAGER->findImage("레비아탄전투지형2")->render(getMemDC(), 0, -250);

	IMAGEMANAGER->findImage("블루오션")->frameRender(getMemDC(), 0, 700, BlueOceanFrame, 0);
}
