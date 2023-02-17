#include "Stdafx.h"
#include "Unit.h"

void Unit::LeviathanInit(void)
{
	// �����ź
	BlueOceanFrame = 0;
	Leviathan.X = Leviathan.Y = 0;
	Leviathan.FrameX = Leviathan.FrameY = Leviathan.FireMotionFrameX = Leviathan.FireFrameX = Leviathan.DieFrameX = 0;
	Leviathan.Time = 0;
	Leviathan.currentTime = 0.0f;
	Leviathan.Pattern = Leviathan.Hp = Leviathan.gravity = 0;
	Leviathan.Down = Leviathan.Die = false;

	// ������
	LeviathanLaser.X = LeviathanLaser.Y = 0;
	LeviathanLaser.LaserFrameX = LeviathanLaser.LaserFrameX1 = 0;
	LeviathanLaser.shot = false;
	LeviathanLaser.change = true;
}

void Unit::LeviathanUpdate(void)
{
	Leviathan.Rc = RectMake(Leviathan.X + 800, Leviathan.Y + 300, 315, 393);
	LeviathanLaser.Rc = RectMake(LeviathanLaser.X, LeviathanLaser.Y, 800, 110);

	if (worldTimeCount % 30 == 0) BlueOceanFrame++;
	if (BlueOceanFrame > IMAGEMANAGER->findImage("������")->getMaxFrameX()) BlueOceanFrame = 0;
	Leviathan.currentTime = 1.0f;

	// ���
	if (Leviathan.Pattern == 0)
	{
		Leviathan.LeviathanState = L_STAY;
		if (worldTimeCount % 17 == 0) Leviathan.FrameX++;
		if (Leviathan.FrameX > IMAGEMANAGER->findImage("�����ź_���")->getMaxFrameX())
		{
			Leviathan.FrameX = 0;
			Leviathan.currentTime = TIMEMANAGER->getWorldTime();
		}

		if (TIMEMANAGER->getWorldTime() - Leviathan.currentTime > 2 && Leviathan.Pattern == 0)
		{
			Leviathan.Pattern = 1;
		}
	}

	// ȭ�� ������
	else if (Leviathan.Pattern == 1)
	{
		Leviathan.LeviathanState = L_ATTACK1;
		if (worldTimeCount % 10 == 0) Leviathan.FireMotionFrameX++;
		if (Leviathan.FireMotionFrameX > IMAGEMANAGER->findImage("�����ź_ȭ���ձ�")->getMaxFrameX()) Leviathan.FireMotionFrameX = 3;

		if (Leviathan.FireMotionFrameX >= 2)
		{
			if (worldTimeCount % 10 == 0) Leviathan.FireFrameX++;
			if (Leviathan.FireFrameX > IMAGEMANAGER->findImage("�����ź_��")->getMaxFrameX()) Leviathan.FireFrameX = 5;
		}

		if (Leviathan.FireFrameX == 5)
		{
			if (worldTimeCount % 17 == 0) Leviathan.FrameX++;
			if (Leviathan.FrameX > IMAGEMANAGER->findImage("�����ź_���")->getMaxFrameX())	Leviathan.FrameX = 0;

		}
		//if (Leviathan.FireMotionFrameX == 3)
		//{
		//	Leviathan.FireMotionFrameX = 0;
		//	Leviathan.Pattern = 2;
		//}
	}

	// ȭ�� ����
	//else if (Leviathan.Pattern == 2)
	//{

	//}

	//������ ������
	//else if (Leviathan.Pattern == 3)
	//{

	//}

}

void Unit::LeviathanRender(void)
{
	if (Leviathan.Pattern == 0)
	{
		if (Leviathan.LeviathanState == L_STAY)
		{
			IMAGEMANAGER->findImage("�����ź_���")->frameRender(getMemDC(), Leviathan.Rc.left, Leviathan.Rc.top, Leviathan.FrameX, 0);
		}
	}

	else if (Leviathan.Pattern == 1)
	{
		if (Leviathan.LeviathanState == L_ATTACK1)
		{
			IMAGEMANAGER->findImage("�����ź_ȭ���ձ�")->frameRender(getMemDC(), Leviathan.Rc.left, Leviathan.Rc.top, Leviathan.FireMotionFrameX, 0);
			IMAGEMANAGER->findImage("�����ź_��")->frameRender(getMemDC(), Leviathan.Rc.left, Leviathan.Rc.top, Leviathan.FireFrameX, 0);
			IMAGEMANAGER->findImage("�����ź_���")->frameRender(getMemDC(), Leviathan.Rc.left, Leviathan.Rc.top, Leviathan.FrameX, 0);
		}
	}

	//else if (Leviathan.Pattern == 2)
	//{

	//}

	//else if (Leviathan.Pattern == 3)
	//{

	//}

	//else if(Leviathan.Die)
	//IMAGEMANAGER->findImage("�����ź��������2")->render(getMemDC(), 0, -250);

	IMAGEMANAGER->findImage("������")->frameRender(getMemDC(), 0, 700, BlueOceanFrame, 0);
}
