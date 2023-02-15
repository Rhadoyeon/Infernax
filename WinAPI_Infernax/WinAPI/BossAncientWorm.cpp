#include "Stdafx.h"
#include "Unit.h"

void Unit::AncientWormInit(void)
{
	AncientWorm.X = AncientWorm.Y = 0;
	AncientWorm.FrameX = AncientWorm.FrameX1 = AncientWorm.RockfallFrameX = AncientWorm.DieFrameX = 0;
	AncientWorm.Time = AncientWorm.Pattern = 0;
	AncientWorm.Hp = 0;
	AncientWorm.Die = false;
	AncientWorm.currentTime = 3.0f;

	Laser.X = Laser.Y = 0;
	Laser.LaserFrameX = Laser.LaserFrameX1 = 0;
	Laser.shot = false;
	Laser.change = true;

	FireBall.X = FireBall.Y = 0;
	AncientWorm.FireballFrameX = AncientWorm.FireballFrameX1 = 0;
	//FireBall.gravity = 0.0f;
	FireBall.shot = false;
}

void Unit::AncientWormUpdate(void)
{
	AncientWorm.Rc = RectMake(AncientWorm.X + 795, AncientWorm.Y + 200, 390, 420);
	Laser.Rc = RectMake(Laser.X, Laser.Y + 425, 800, 110);
	FireBall.BulletRc = RectMake(FireBall.X, FireBall.Y, 63, 63);

	//cout << TIMEMANAGER->getWorldTime() << endl;

	//if (player.X <= 120)
	//{
	//	AncientWorm.Pattern = 0;
	//}

	if (AncientWorm.Pattern == 0)
	{
		AncientWorm.AncientWormState = A_ATTACK1;
		if (worldTimeCount % 30 == 0) AncientWorm.FrameX++;

		if (AncientWorm.FrameX > IMAGEMANAGER->findImage("����")->getMaxFrameX()) AncientWorm.FrameX = 3;
		if (AncientWorm.FrameX == 3)
		{
			AncientWorm.FrameX = 0;
			AncientWorm.Pattern = 1;
			//AncientWorm.currentTime = TIMEMANAGER->getWorldTime();
		}
	}

	else if (AncientWorm.Pattern == 1)
	{
		AncientWorm.AncientWormState = A_ATTACK2;
		if (worldTimeCount % 17 == 0) AncientWorm.FrameX1++;
		if (AncientWorm.FrameX1 > IMAGEMANAGER->findImage("����_��O")->getMaxFrameX()) AncientWorm.FrameX1 = 0;

		if (worldTimeCount % 17 == 0) Laser.LaserFrameX++;
		if (Laser.LaserFrameX > IMAGEMANAGER->findImage("����_��������")->getMaxFrameX()) Laser.LaserFrameX = 0;

		if (worldTimeCount % 17 == 0) Laser.LaserFrameX1++;
		if (Laser.LaserFrameX1 > IMAGEMANAGER->findImage("����_������")->getMaxFrameX())
		{
			Laser.LaserFrameX1 = 2;
			if (!Laser.change) AncientWorm.currentTime = TIMEMANAGER->getWorldTime();
			Laser.change = true;
		}

		if (TIMEMANAGER->getWorldTime() - AncientWorm.currentTime > 3)
			if (Laser.LaserFrameX1 == 2 && Laser.change)
			{
				//cout << "����?" << endl; // ��
				Laser.change = false;
				//AncientWorm.currentTime = TIMEMANAGER->getWorldTime();

			}

		if (!Laser.change/*TIMEMANAGER->getWorldTime() - AncientWorm.currentTime > 10*/ /*TIMEMANAGER->getWorldTime() - AncientWorm.currentTime > 5*/)
		{
			//cout << "�� �ȵ���" << endl;
			//if (worldTimeCount % 17 == 0) AncientWorm.FrameX1++;
			//if (AncientWorm.FrameX1 > IMAGEMANAGER->findImage("����_��O")->getMaxFrameX()) AncientWorm.FrameX1 = 0;
			//if (worldTimeCount % 17 == 0) Laser.LaserFrameX1++;
			//if (Laser.LaserFrameX1 > IMAGEMANAGER->findImage("����_������")->getMaxFrameX()) Laser.LaserFrameX1 = 1;
			AncientWorm.Pattern = 2;
			for (int i = 0; i < 10; i++)
			{
				float FireBallX = RND->getFromFloatTo(800.0f, 850.0f);
				float FireBallY = RND->getFromFloatTo(230.0f, 300.0f);

				vABullet.push_back({ FireBallX, FireBallY, RectMakeCenter(FireBallX, FireBallY, 21, 21), 0.5, false });
			}
		}
		//if (Laser.LaserFrameX1 == 3)
		//{
		//	if (worldTimeCount % 17 == 0) AncientWorm.FrameX1++;
		//	if (AncientWorm.FrameX1 > IMAGEMANAGER->findImage("����_��O")->getMaxFrameX()) AncientWorm.FrameX1 = 0;
		//	if (worldTimeCount % 17 == 0) Laser.LaserFrameX1++;
		//	if (Laser.LaserFrameX1 > IMAGEMANAGER->findImage("����_������")->getMaxFrameX()) Laser.LaserFrameX1 = 1;
		//	if (Laser.LaserFrameX1 == 0)
		//	{
		//		AncientWorm.Pattern = 2;
		//		//AncientWorm.currentTime + 1 < TIMEMANAGER->getWorldTime();
		//	}
		//}
	}

	else if (AncientWorm.Pattern == 2)
	{
		AncientWorm.AncientWormState = A_ATTACK3;

		for (int i = 0; i < 10; i++)
		{
			//vABullet[i].X += cosf(vABullet[i].gravity);
			//vABullet[i].Y -= sinf(vABullet[i].gravity);
			//vABullet[i].X -= 1.5;
			//vABullet[i].Y += 2.0;
			//AncientWorm.Y = FireBall.gravity += 0.3f; ������ ��������.
			
			getDistance(850.0f, 230.0f, 750.0f, 230.0f); 
			FireBall.X -= 0.1;
			FireBall.gravity = 0.1f;

			//FireBall.Y += 0.3f;
			//vABullet[i].BulletRc = RectMakeCenter(FireBall.X + 500, FireBall.Y, 21, 21); // ������ ��������. ������ ����ϸ� �ɵ�

			FireBall.Y += FireBall.gravity;

			vABullet[i].BulletRc = RectMakeCenter(vABullet[i].X + FireBall.X, vABullet[i].Y + FireBall.Y, 21, 21);
		}

		if (worldTimeCount % 17 == 0) AncientWorm.FrameX1++;
		if (AncientWorm.FrameX1 > IMAGEMANAGER->findImage("����_��O")->getMaxFrameX()) AncientWorm.FrameX1 = 0;

		if (worldTimeCount % 17 == 0) AncientWorm.FireballFrameX++;
		if (AncientWorm.FireballFrameX > IMAGEMANAGER->findImage("����_ȭ����")->getMaxFrameX()) AncientWorm.FireballFrameX = 0;
	}
}

void Unit::AncientWormRender(void)
{
	//DrawRectMake(getMemDC(), AncientWorm.Rc);
	//DrawRectMake(getMemDC(), Laser.Rc);
	// 2��
	// �������� 5���̻� ������ 2�������� �Ѿ��.
	// ȭ������ 3�ʰ� ���ϰ� ������������ �Ѿ��.
	// 3��
	// ���Ͱ� ���Ʒ��� �Դٰ��� �ϴٰ� �Ʒ��� ���������Ѵ�.
	// �Ʒ��� �������� ������ ���������Ѵ�.
	// ������ �� �������� �ٽ� 1�� �������� �Ѿ��.

	if (AncientWorm.Pattern == 0)
	{
		if (AncientWorm.AncientWormState == A_ATTACK1)
		{
			IMAGEMANAGER->findImage("����")->frameRender(getMemDC(), AncientWorm.Rc.left, AncientWorm.Rc.top, AncientWorm.FrameX, 0);
		}
	}

	else if (AncientWorm.Pattern == 1)
	{
		if (AncientWorm.AncientWormState == A_ATTACK2)
		{
			IMAGEMANAGER->findImage("����_��O")->frameRender(getMemDC(), AncientWorm.Rc.left, AncientWorm.Rc.top, AncientWorm.FrameX1, 0);
			IMAGEMANAGER->findImage("����_������")->frameRender(getMemDC(), Laser.Rc.left - 810, Laser.Rc.top - 8, Laser.LaserFrameX1, 0);
			IMAGEMANAGER->findImage("����_��������")->frameRender(getMemDC(), AncientWorm.Rc.left - 90, AncientWorm.Rc.top + 180, Laser.LaserFrameX, 0);
		}
	}

	else if (AncientWorm.Pattern == 2)
	{
		if (AncientWorm.AncientWormState == A_ATTACK3)
		{
			IMAGEMANAGER->findImage("����_��O")->frameRender(getMemDC(), AncientWorm.Rc.left, AncientWorm.Rc.top, AncientWorm.FrameX1, 0);
			
			for (int i = 0; i < 10; i++)
			{
				IMAGEMANAGER->findImage("����_ȭ����")->frameRender(getMemDC(), vABullet[i].BulletRc.left, vABullet[i].BulletRc.top + 200, AncientWorm.FireballFrameX, 0);
			}
		}
	}
}
