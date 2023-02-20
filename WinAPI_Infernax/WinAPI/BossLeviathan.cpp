#include "Stdafx.h"
#include "Unit.h"

void Unit::LeviathanInit(void)
{
	// 레비아탄
	BlueOceanFrame = 0;
	Leviathan.X = Leviathan.Y = 0;
	Leviathan.FireX = Leviathan.FireY = 0;
	Leviathan.FrameX = Leviathan.FireMotionFrameX = Leviathan.FireFrameX = Leviathan.DownFrameX = Leviathan.LaserMotionX = Leviathan.DieFrameX = 0;
	Leviathan.Time = 0;
	Leviathan.currentTime1 = /*Leviathan.currentTime2 = Leviathan.currentTime3 =*/ 0.0f;
	Leviathan.Pattern = Leviathan.Hp = Leviathan.gravity = 0;
	Leviathan.Down = Leviathan.Die = Leviathan.Shake = false;

	// 레이저
	LeviathanLaser.X = LeviathanLaser.Y = 0;
	LeviathanLaser.LaserFrameX = LeviathanLaser.LaserFrameX1 = 0;
	LeviathanLaser.shot = false;
	LeviathanLaser.change = true;
}

void Unit::LeviathanUpdate(void)
{
	Leviathan.Rc = RectMake(Leviathan.X + 880, Leviathan.Y + 300, 120, 370);
	Leviathan.FireRc = RectMake(Leviathan.FireX + 720, Leviathan.FireY + 470, 150, 150);
	LeviathanLaser.Rc = RectMake(LeviathanLaser.X + 120, LeviathanLaser.Y + 412, 800, 110);

	if (worldTimeCount % 30 == 0) BlueOceanFrame++;
	if (BlueOceanFrame > IMAGEMANAGER->findImage("블루오션")->getMaxFrameX()) BlueOceanFrame = 0;
	Leviathan.currentTime1 /*= Leviathan.currentTime2 = Leviathan.currentTime3*/ = 3.0f;

	if (!Leviathan.Die)
	{
		// 대기
		if (Leviathan.Pattern == 0)
		{
			Leviathan.LeviathanState = L_STAY;
			if (worldTimeCount % 17 == 0) Leviathan.FrameX++;
			if (Leviathan.FrameX > IMAGEMANAGER->findImage("레비아탄_대기")->getMaxFrameX())
			{
				Leviathan.FrameX = 0;
				Leviathan.currentTime1 = TIMEMANAGER->getWorldTime();
			}

			if (TIMEMANAGER->getWorldTime() - Leviathan.currentTime1 > 2 && Leviathan.Pattern == 0 && !Leviathan.Die)
			{
				Leviathan.Pattern = 1;
			}
		}

		// 화염 오른쪽
		else if (Leviathan.Pattern == 1)
		{
			Leviathan.LeviathanState = L_ATTACK1;
			if (worldTimeCount % 10 == 0) Leviathan.FireMotionFrameX++;
			if (Leviathan.FireMotionFrameX > IMAGEMANAGER->findImage("레비아탄_화염뿜기")->getMaxFrameX()) Leviathan.FireMotionFrameX = 3;

			if (Leviathan.FireMotionFrameX >= 2)
			{
				if (worldTimeCount % 10 == 0) Leviathan.FireFrameX++;
				if (Leviathan.FireFrameX > IMAGEMANAGER->findImage("레비아탄_불")->getMaxFrameX()) Leviathan.FireFrameX = 6;
			}

			if (Leviathan.FireFrameX == 6 && Leviathan.Pattern == 1 && !Leviathan.Die)
			{
				Leviathan.FireFrameX = 0;
				Leviathan.FireMotionFrameX = 0;
				Leviathan.Pattern = 2;
			}
		}

		// 입수 오른쪽 아래
		else if (Leviathan.Pattern == 2)
		{
			//Leviathan.LeviathanState = L_DOWN;
			if (worldTimeCount % 17 == 0) Leviathan.DownFrameX++;
			if (Leviathan.DownFrameX > IMAGEMANAGER->findImage("레비아탄_입수")->getMaxFrameX())
			{
				Leviathan.DownFrameX = 2;
				Leviathan.Rc.top += Leviathan.gravity;
				Leviathan.Rc.bottom += Leviathan.gravity;
				Leviathan.Y += Leviathan.gravity;
				Leviathan.gravity += 5;
			}
			if (Leviathan.Y >= 500 && Leviathan.Pattern == 2 && !Leviathan.Die)
			{
				Leviathan.Pattern = 3;
				Leviathan.DownFrameX = 0;
			}
		}

		// 입수 끝 왼쪽 위로 올라옴
		else if (Leviathan.Pattern == 3)
		{
			//Leviathan.LeviathanState = L_UP;
			Leviathan.X = -520;
			if (worldTimeCount % 17 == 0) Leviathan.DownFrameX++;
			if (Leviathan.DownFrameX > IMAGEMANAGER->findImage("레비아탄_입수")->getMaxFrameX())
			{
				Leviathan.DownFrameX = 2;
				Leviathan.Rc.top -= Leviathan.gravity;
				Leviathan.Rc.bottom -= Leviathan.gravity;
				Leviathan.Y -= Leviathan.gravity;
				Leviathan.gravity -= 5;
			}

			if (Leviathan.Y == 0) Leviathan.gravity = 0;
			if (Leviathan.gravity == 0 && Leviathan.Pattern == 3 && !Leviathan.Die)
			{
				Leviathan.Pattern = 4;
				Leviathan.DownFrameX = 0;
			}
		}

		// 레비아탄 화염 스킬
		else if (Leviathan.Pattern == 4)
		{
			Leviathan.LeviathanState = L_ATTACK2;
			Leviathan.FireX = -220;

			if (worldTimeCount % 10 == 0) Leviathan.FireMotionFrameX++;
			if (Leviathan.FireMotionFrameX > IMAGEMANAGER->findImage("레비아탄_화염뿜기")->getMaxFrameX()) Leviathan.FireMotionFrameX = 3;

			if (Leviathan.FireMotionFrameX >= 2)
			{
				if (worldTimeCount % 10 == 0) Leviathan.FireFrameX++;
				if (Leviathan.FireFrameX > IMAGEMANAGER->findImage("레비아탄_불")->getMaxFrameX()) Leviathan.FireFrameX = 6;
			}

			if (Leviathan.FireFrameX == 6 && Leviathan.Pattern == 4 && !Leviathan.Die)
			{
				Leviathan.FireFrameX = 0;
				Leviathan.FireMotionFrameX = 0;
				Leviathan.Pattern = 5;
				Leviathan.FireX = 0;
			}

		}

		// 왼쪽 아래로 입수
		else if (Leviathan.Pattern == 5)
		{
			//Leviathan.LeviathanState = L_DOWN;
			Leviathan.X = -520;
			if (worldTimeCount % 17 == 0) Leviathan.DownFrameX++;
			if (Leviathan.DownFrameX > IMAGEMANAGER->findImage("레비아탄_입수")->getMaxFrameX())
			{
				Leviathan.DownFrameX = 2;
				Leviathan.Rc.top += Leviathan.gravity;
				Leviathan.Rc.bottom += Leviathan.gravity;
				Leviathan.Y += Leviathan.gravity;
				Leviathan.gravity += 5;
			}

			if (Leviathan.Y >= 500 && Leviathan.Pattern == 5 && !Leviathan.Die)
			{
				Leviathan.Pattern = 6;
				Leviathan.DownFrameX = 0;
			}
		}

		// 입수 끝 오른쪽 위로 올라옴
		else if (Leviathan.Pattern == 6)
		{
			//Leviathan.LeviathanState = L_UP;
			Leviathan.X = 0;
			if (worldTimeCount % 17 == 0) Leviathan.DownFrameX++;
			if (Leviathan.DownFrameX > IMAGEMANAGER->findImage("레비아탄_입수")->getMaxFrameX())
			{
				Leviathan.DownFrameX = 2;
				Leviathan.Rc.top -= Leviathan.gravity;
				Leviathan.Rc.bottom -= Leviathan.gravity;
				Leviathan.Y -= Leviathan.gravity;
				Leviathan.gravity -= 5;
			}

			if (Leviathan.Y == 0) Leviathan.gravity = 0;
			if (Leviathan.gravity == 0 && Leviathan.Pattern == 6 && !Leviathan.Die)
			{
				Leviathan.DownFrameX = 0;
				Leviathan.Pattern = 7;
			}
		}

		// 오른쪽에서 레이저 5초간
		else if (Leviathan.Pattern == 7)
		{
			Leviathan.LeviathanState = L_ATTACK3;
			if (worldTimeCount % 17 == 0) Leviathan.LaserMotionX++;
			if (Leviathan.LaserMotionX > IMAGEMANAGER->findImage("레비아탄_레이저")->getMaxFrameX())
			{
				Leviathan.LaserMotionX = 4;
				//Leviathan.currentTime2 = 5.0f;
				//Leviathan.currentTime1 = TIMEMANAGER->getWorldTime();
			}
			if (Leviathan.LaserMotionX == 4)
			{
				if (worldTimeCount % 17 == 0) LeviathanLaser.LaserFrameX++;
				if (LeviathanLaser.LaserFrameX > IMAGEMANAGER->findImage("레이저볼")->getMaxFrameX()) LeviathanLaser.LaserFrameX = 0;

				if (worldTimeCount % 17 == 0) LeviathanLaser.LaserFrameX1++;
				if (LeviathanLaser.LaserFrameX1 > IMAGEMANAGER->findImage("레비아탄_레이저스킬")->getMaxFrameX()) LeviathanLaser.LaserFrameX1 = 9;

				if (/*TIMEMANAGER->getWorldTime() - Leviathan.currentTime1 > 7 &&*/ LeviathanLaser.LaserFrameX1 == 9 && Leviathan.Pattern == 7 && !Leviathan.Die)
				{
					LeviathanLaser.LaserFrameX1 = 0;
					Leviathan.Pattern = 8;
					Leviathan.LaserMotionX = 0;
				}
			}
		}

		// 오른쪽 아래 입수
		else if (Leviathan.Pattern == 8)
		{
			//Leviathan.LeviathanState = L_DOWN;
			if (worldTimeCount % 17 == 0) Leviathan.DownFrameX++;
			if (Leviathan.DownFrameX > IMAGEMANAGER->findImage("레비아탄_입수")->getMaxFrameX())
			{
				Leviathan.DownFrameX = 2;
				Leviathan.Rc.top += Leviathan.gravity;
				Leviathan.Rc.bottom += Leviathan.gravity;
				Leviathan.Y += Leviathan.gravity;
				Leviathan.gravity += 5;
			}
			if (Leviathan.Y >= 500 && Leviathan.Pattern == 8 && !Leviathan.Die)
			{
				Leviathan.Pattern = 9;
				Leviathan.DownFrameX = 0;
			}
		}

		// 입수 끝. 왼쪽 위로 올라옴
		else if (Leviathan.Pattern == 9)
		{
			//Leviathan.LeviathanState = L_UP;
			Leviathan.X = -520;
			if (worldTimeCount % 17 == 0) Leviathan.DownFrameX++;
			if (Leviathan.DownFrameX > IMAGEMANAGER->findImage("레비아탄_입수")->getMaxFrameX())
			{
				Leviathan.DownFrameX = 2;
				Leviathan.Rc.top -= Leviathan.gravity;
				Leviathan.Rc.bottom -= Leviathan.gravity;
				Leviathan.Y -= Leviathan.gravity;
				Leviathan.gravity -= 5;
			}

			if (Leviathan.Y == 0) Leviathan.gravity = 0;
			if (Leviathan.gravity == 0 && Leviathan.Pattern == 9 && !Leviathan.Die)
			{
				Leviathan.Pattern = 10;
				Leviathan.DownFrameX = 0;
			}
		}

		// 왼쪽에서 레이저
		else if (Leviathan.Pattern == 10)
		{
			Leviathan.LeviathanState = L_ATTACK4;
			if (worldTimeCount % 17 == 0) Leviathan.LaserMotionX++;
			if (Leviathan.LaserMotionX > IMAGEMANAGER->findImage("레비아탄_레이저")->getMaxFrameX())
			{
				Leviathan.LaserMotionX = 4;
				//Leviathan.currentTime3 = 3.0f;
				//Leviathan.currentTime1 = TIMEMANAGER->getWorldTime();
			}
			if (Leviathan.LaserMotionX == 4)
			{
				if (worldTimeCount % 17 == 0) LeviathanLaser.LaserFrameX++;
				if (LeviathanLaser.LaserFrameX > IMAGEMANAGER->findImage("레이저볼")->getMaxFrameX()) LeviathanLaser.LaserFrameX = 0;

				if (worldTimeCount % 17 == 0) LeviathanLaser.LaserFrameX1++;
				if (LeviathanLaser.LaserFrameX1 > IMAGEMANAGER->findImage("레비아탄_레이저스킬")->getMaxFrameX()) LeviathanLaser.LaserFrameX1 = 9;

				if (/*TIMEMANAGER->getWorldTime() - Leviathan.currentTime1 > 7 &&*/ LeviathanLaser.LaserFrameX1 == 9 && Leviathan.Pattern == 10 && !Leviathan.Die)
				{
					LeviathanLaser.LaserFrameX1 = 0;
					Leviathan.LaserMotionX = 0;
					Leviathan.Pattern = 11;
				}
			}
		}

		// 왼쪽 아래로 입수
		else if (Leviathan.Pattern == 11)
		{
			//Leviathan.X = -520;
			if (worldTimeCount % 17 == 0) Leviathan.DownFrameX++;
			if (Leviathan.DownFrameX > IMAGEMANAGER->findImage("레비아탄_입수")->getMaxFrameX())
			{
				Leviathan.DownFrameX = 2;
				Leviathan.Rc.top += Leviathan.gravity;
				Leviathan.Rc.bottom += Leviathan.gravity;
				Leviathan.Y += Leviathan.gravity;
				Leviathan.gravity += 5;
			}

			if (Leviathan.Y >= 500 && Leviathan.Pattern == 11 && !Leviathan.Die)
			{
				Leviathan.Pattern = 12;
				Leviathan.DownFrameX = 0;
			}
		}

		// 입수 끝. 오른쪽 위로 올라옴
		else if (Leviathan.Pattern == 12)
		{
			//Leviathan.LeviathanState = L_UP;
			Leviathan.X = 0;
			if (worldTimeCount % 17 == 0) Leviathan.DownFrameX++;
			if (Leviathan.DownFrameX > IMAGEMANAGER->findImage("레비아탄_입수")->getMaxFrameX())
			{
				Leviathan.DownFrameX = 2;
				Leviathan.Rc.top -= Leviathan.gravity;
				Leviathan.Rc.bottom -= Leviathan.gravity;
				Leviathan.Y -= Leviathan.gravity;
				Leviathan.gravity -= 5;
			}

			if (Leviathan.Y == 0) Leviathan.gravity = 0;
			if (Leviathan.gravity == 0 && Leviathan.Pattern == 12 && !Leviathan.Die)
			{
				Leviathan.DownFrameX = 0;
				Leviathan.Pattern = 0;
			}
		}

		RECT Ltemp;
		if (IntersectRect(&Ltemp, &player.AttackRc, &Leviathan.Rc))
		{
			//Leviathan.Shake = false;
			if (Leviathan.Hp < 400) Leviathan.Hp++;
		}

	}

	if (Leviathan.Hp >= 400 && !Leviathan.Shake)
	{
		Leviathan.Die = true;
		Leviathan.LeviathanState = L_DIE;

		//Leviathan.Shake = true;
		//Leviathan.Rc.left -= 10;
		//Leviathan.Rc.left += 10;
		//Leviathan.Rc.right -= 10;
		//Leviathan.Rc.right += 10;
		//Leviathan.X -= 10;
		//Leviathan.X += 10;

		if (worldTimeCount % 17 == 0) Leviathan.DieFrameX++;
		if (Leviathan.DieFrameX > IMAGEMANAGER->findImage("레비아탄_죽음")->getMaxFrameX()) Leviathan.DieFrameX = 3;

		if (Leviathan.DieFrameX == 3 && Leviathan.Die)
		{
			Leviathan.Y += Leviathan.gravity;
			//Leviathan.gravity += 1;
			if (Leviathan.Y > 2000)
			{
				Leviathan.Shake = true;
				IMAGEMANAGER->findImage("레비아탄전투지형2")->getMemDC();
			}
		}
	}
}


void Unit::LeviathanRender(void)
{
	//DrawRectMake(getMemDC(), Leviathan.Rc);
	//DrawRectMake(getMemDC(), Leviathan.FireRc);
	//DrawRectMake(getMemDC(), LeviathanLaser.Rc);

	if (!Leviathan.Die)
	{
		if (Leviathan.Pattern == 0)
		{
			if (Leviathan.LeviathanState == L_STAY)
			{
				IMAGEMANAGER->findImage("레비아탄_대기")->frameRender(getMemDC(), Leviathan.Rc.left - 100, Leviathan.Rc.top - 10, Leviathan.FrameX, 0);
			}
		}

		else if (Leviathan.Pattern == 1)
		{
			if (Leviathan.LeviathanState == L_ATTACK1)
			{
				IMAGEMANAGER->findImage("레비아탄_화염뿜기")->frameRender(getMemDC(), Leviathan.Rc.left - 100, Leviathan.Rc.top - 10, Leviathan.FireMotionFrameX, 0);
				IMAGEMANAGER->findImage("레비아탄_불")->frameRender(getMemDC(), Leviathan.FireRc.left, Leviathan.FireRc.top - 83, Leviathan.FireFrameX, 0);
			}
		}

		else if (Leviathan.Pattern == 2)
		{
			//if(Leviathan.LeviathanState == L_DOWN)
			IMAGEMANAGER->findImage("레비아탄_입수")->frameRender(getMemDC(), Leviathan.Rc.left - 100, Leviathan.Rc.top, Leviathan.DownFrameX, 0);
		}

		else if (Leviathan.Pattern == 3)
		{
			//if(Leviathan.LeviathanState == L_UP)
			IMAGEMANAGER->findImage("레비아탄_입수")->frameRender(getMemDC(), Leviathan.Rc.left - 100, Leviathan.Rc.top, Leviathan.DownFrameX, 1);
		}

		else if (Leviathan.Pattern == 4)
		{
			if (Leviathan.LeviathanState == L_ATTACK2)
			{
				IMAGEMANAGER->findImage("레비아탄_화염뿜기")->frameRender(getMemDC(), Leviathan.Rc.left - 100, Leviathan.Rc.top - 10, Leviathan.FireMotionFrameX, 1);
				IMAGEMANAGER->findImage("레비아탄_불")->frameRender(getMemDC(), Leviathan.FireRc.left, Leviathan.FireRc.top - 83, Leviathan.FireFrameX, 1);
			}
		}

		else if (Leviathan.Pattern == 5)
		{
			//if (Leviathan.LeviathanState == L_DOWN)
			IMAGEMANAGER->findImage("레비아탄_입수")->frameRender(getMemDC(), Leviathan.Rc.left - 100, Leviathan.Rc.top, Leviathan.DownFrameX, 1);
		}

		else if (Leviathan.Pattern == 6)
		{
			//if (Leviathan.LeviathanState == L_UP)
			IMAGEMANAGER->findImage("레비아탄_입수")->frameRender(getMemDC(), Leviathan.Rc.left - 100, Leviathan.Rc.top, Leviathan.DownFrameX, 0);
		}

		else if (Leviathan.Pattern == 7)
		{
			if (Leviathan.LeviathanState == L_ATTACK3)
			{
				IMAGEMANAGER->findImage("레비아탄_레이저")->frameRender(getMemDC(), Leviathan.Rc.left - 100, Leviathan.Rc.top, Leviathan.LaserMotionX, 0);
				if (Leviathan.LaserMotionX == 4)
				{
					IMAGEMANAGER->findImage("레비아탄_레이저스킬")->frameRender(getMemDC(), LeviathanLaser.Rc.left - 820, LeviathanLaser.Rc.top, LeviathanLaser.LaserFrameX1, 0);
					IMAGEMANAGER->findImage("레이저볼")->frameRender(getMemDC(), Leviathan.Rc.left - 150, Leviathan.Rc.top + 80, LeviathanLaser.LaserFrameX, 0);
				}
			}
		}

		else if (Leviathan.Pattern == 8)
		{
			//if (Leviathan.LeviathanState == L_DOWN)
			IMAGEMANAGER->findImage("레비아탄_입수")->frameRender(getMemDC(), Leviathan.Rc.left - 100, Leviathan.Rc.top, Leviathan.DownFrameX, 0);
		}

		else if (Leviathan.Pattern == 9)
		{
			//if (Leviathan.LeviathanState == L_UP)
			IMAGEMANAGER->findImage("레비아탄_입수")->frameRender(getMemDC(), Leviathan.Rc.left - 100, Leviathan.Rc.top, Leviathan.DownFrameX, 1);
		}

		else if (Leviathan.Pattern == 10)
		{
			if (Leviathan.LeviathanState == L_ATTACK4)
			{
				IMAGEMANAGER->findImage("레비아탄_레이저")->frameRender(getMemDC(), Leviathan.Rc.left - 100, Leviathan.Rc.top, Leviathan.LaserMotionX, 1);
				if (Leviathan.LaserMotionX == 4)
				{
					IMAGEMANAGER->findImage("레비아탄_레이저스킬")->frameRender(getMemDC(), LeviathanLaser.Rc.left + 450, LeviathanLaser.Rc.top, LeviathanLaser.LaserFrameX1, 0);
					IMAGEMANAGER->findImage("레이저볼")->frameRender(getMemDC(), Leviathan.Rc.left + 100, Leviathan.Rc.top + 80, LeviathanLaser.LaserFrameX, 1);
				}
			}
		}

		else if (Leviathan.Pattern == 11)
		{
			IMAGEMANAGER->findImage("레비아탄_입수")->frameRender(getMemDC(), Leviathan.Rc.left - 100, Leviathan.Rc.top, Leviathan.DownFrameX, 1);
		}

		else if (Leviathan.Pattern == 12)
		{
			IMAGEMANAGER->findImage("레비아탄_입수")->frameRender(getMemDC(), Leviathan.Rc.left - 100, Leviathan.Rc.top, Leviathan.DownFrameX, 0);
		}
	}

	else if (Leviathan.Die)
	{
		if (Leviathan.LeviathanState == L_DIE)
		{
			/*if (Leviathan.X > -220) */
			if (!Leviathan.Shake)
				IMAGEMANAGER->findImage("레비아탄_죽음")->frameRender(getMemDC(), Leviathan.Rc.left - 100, Leviathan.Rc.top, Leviathan.DieFrameX, 0);
			//if (Leviathan.X <= 0) IMAGEMANAGER->findImage("레비아탄_죽음")->frameRender(getMemDC(), Leviathan.Rc.left - 600, Leviathan.Rc.top, Leviathan.DieFrameX, 1);
			if (Leviathan.Shake)
				IMAGEMANAGER->findImage("레비아탄전투지형2")->render(getMemDC(), -1050, -317);
		}
	}
	IMAGEMANAGER->findImage("블루오션")->frameRender(getMemDC(), 0, 700, BlueOceanFrame, 0);
}