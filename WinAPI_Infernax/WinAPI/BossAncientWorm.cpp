#include "Stdafx.h"
#include "Unit.h"

void Unit::AncientWormInit(void)
{
	//고대웜
	AncientWorm.X = AncientWorm.Y = 0;
	AncientWorm.FrameX = AncientWorm.FrameX1 = AncientWorm.RockfallFrameX = AncientWorm.DieFrameX = 0;
	AncientWorm.Time = AncientWorm.Pattern = 0;
	AncientWorm.Hp = 0;
	AncientWorm.gravity = 0.0f;
	AncientWorm.Die = AncientWorm.UpDown = false;
	AncientWorm.currentTime = 0.0f;

	//레이저
	AncientWormLaser.X = AncientWormLaser.Y = 0;
	AncientWormLaser.LaserFrameX = AncientWormLaser.LaserFrameX1 = 0;
	AncientWormLaser.shot = false;
	AncientWormLaser.change = true;

	//화염구
	FireBall.X = FireBall.Y = 0;
	AncientWorm.FireballFrameX = AncientWorm.FireballFrameX1 = 0;
	FireBall.shot = false;

	RedOceanFrame = 0;
}

void Unit::AncientWormUpdate(void)
{
	// 고대웜 & 레이저 & 파이어볼 렉트
	AncientWorm.Rc = RectMake(AncientWorm.X + 795, AncientWorm.Y + 200, 390, 420);
	AncientWormLaser.Rc = RectMake(AncientWormLaser.X, AncientWormLaser.Y + 425, 800, 110);
	//FireBall.BulletRc = RectMake(FireBall.X, FireBall.Y, 189, 189);

	if (worldTimeCount % 30 == 0) RedOceanFrame++;
	if (RedOceanFrame > IMAGEMANAGER->findImage("레드오션")->getMaxFrameX()) RedOceanFrame = 0;

	if (!AncientWorm.Die)
	{
		// 패턴1 공격을 하지 않는 준비 상태 / 프레임이 다 돌아가면 다음 패턴으로 돌아가는 준비 동작
		if (AncientWorm.Pattern == 0)
		{
			AncientWorm.AncientWormState = A_ATTACK1;
			if (worldTimeCount % 30 == 0) AncientWorm.FrameX++;
			if (AncientWorm.FrameX > IMAGEMANAGER->findImage("고대웜")->getMaxFrameX()) AncientWorm.FrameX = 3;

			// 웜의 프레임이 맥스 일때 패턴은 1로 / 프레임은 0으로 초기화
			if (AncientWorm.FrameX == 3 && AncientWorm.Pattern == 0 && !AncientWorm.Die)
			{
				AncientWorm.FrameX = 0;
				AncientWorm.Pattern = 1;
				AncientWorm.currentTime = 5.0f;
				AncientWorm.currentTime = TIMEMANAGER->getWorldTime();
			}
		}

		// 패턴2 레이저를 쏜다. / 레이저를 총 7초간 쏜 후에 레이저는 사라진다.
		else if (AncientWorm.Pattern == 1)
		{
			AncientWorm.AncientWormState = A_ATTACK2;
			if (worldTimeCount % 17 == 0) AncientWorm.FrameX1++;
			if (AncientWorm.FrameX1 > IMAGEMANAGER->findImage("고대웜_입O")->getMaxFrameX()) AncientWorm.FrameX1 = 0;

			if (worldTimeCount % 17 == 0) AncientWormLaser.LaserFrameX++;
			if (AncientWormLaser.LaserFrameX > IMAGEMANAGER->findImage("고대웜_레이저볼")->getMaxFrameX()) AncientWormLaser.LaserFrameX = 0;

			if (worldTimeCount % 17 == 0) AncientWormLaser.LaserFrameX1++;
			if (AncientWormLaser.LaserFrameX1 > IMAGEMANAGER->findImage("고대웜_레이저")->getMaxFrameX())
			{
				AncientWormLaser.LaserFrameX1 = 2;
			}

			// 일정 시간이 지나고 레이저에서 화염구 패턴으로 바꿔준다.
			if (TIMEMANAGER->getWorldTime() - AncientWorm.currentTime > 5 && AncientWorm.Pattern == 1 && !AncientWorm.Die)
			{
				AncientWorm.Pattern = 2;

				// 화염구 생성
				for (int i = 0; i < 20; i++)
				{
					float FireBallX = RND->getFromFloatTo(800.0f, 850.0f);
					float FireBallY = RND->getFromFloatTo(230.0f, 300.0f);

					int OneShot = i * 10; //RND->getFromIntTo(10, 12);

					vABullet.push_back({ FireBallX, FireBallY, RectMakeCenter(FireBallX + 100, FireBallY + 200, 63, 63), 0, 0.0f, 0, OneShot, false });
				}
			}
		}

		// 패턴3. 화염구 공격 / 화염구는 포물선을 그리며 날라간다.
		else if (AncientWorm.Pattern == 2)
		{
			AncientWorm.AncientWormState = A_ATTACK3;

			if (worldTimeCount % 17 == 0) AncientWorm.FrameX1++;
			if (AncientWorm.FrameX1 > IMAGEMANAGER->findImage("고대웜_입O")->getMaxFrameX()) AncientWorm.FrameX1 = 0;

			if (worldTimeCount % 17 == 0) AncientWorm.FireballFrameX++;
			if (AncientWorm.FireballFrameX > IMAGEMANAGER->findImage("고대웜_화염구")->getMaxFrameX()) AncientWorm.FireballFrameX = 0;

			// 화염구 발사
			for (int i = 0; i < vABullet.size(); i++)
			{
				//vABullet[i].X -= 1.5;
				//vABullet[i].Y += 2.0;
				//AncientWorm.Y = FireBall.gravity += 0.3f; 고대웜이 밑으로 내려간다.
				//FireBall.Y += 0.3f;
				//vABullet[i].BulletRc = RectMakeCenter(FireBall.X + 500, FireBall.Y, 21, 21); // 위에서 떨어진다. 낙석때 사용하면 될듯			
				//getDistance(850.0f, 230.0f, 750.0f, 230.0f); 
				//FireBall.X -= 0.1;
				//FireBall.gravity = 0.1f;
				//FireBall.Y += FireBall.gravity;
				//vABullet[i].X = cosf(vABullet[i].gravity);
				//vABullet[i].Y = sinf(vABullet[i].gravity) * FireBall.gravity;
				//FireBall.X -= 0.1;
				//FireBall.gravity += 0.3f;
				//FireBall.Y += FireBall.gravity;

				vABullet[i].count++;
				if (vABullet[i].count > vABullet[i].oneShot)
				{
					vABullet[i].X -= RND->getFromFloatTo(6.0f, 9.0f);
					vABullet[i].Y += vABullet[i].gravity;

					vABullet[i].gravity += 0.1f; // 중력값 점점 더해줘서 포물선 그리도록.
					vABullet[i].BulletRc = RectMakeCenter(vABullet[i].X, vABullet[i].Y + 200, 63, 63);

					if (vABullet[i].count > 200 + vABullet[i].oneShot) vABullet.erase(vABullet.begin() + i); // 카운트가 200되면 자동으로 사라지게
					else i++;

					// 사이즈가 0이 될때(화염구가 모두 사라질때) 패턴은 3으로 변경된다.
					if (vABullet.size() == 0 && AncientWorm.Pattern == 2 && !AncientWorm.Die)
					{
						AncientWorm.Pattern = 3;
					}
				}

				//새 x좌표 = 회전중심점x + cos(angle) × 반지름길이
				//새 y좌표 = 회전중심점y + sin(angle) × 반지름길이
				//vABullet[i].X = cosf(vABullet[i].gravity);
				//vABullet[i].Y = -sinf(vABullet[i].gravity);
				//if (FireBall.Y + FireBall.gravity)
				//{
				//	if (FireBall.X > 850)
				//	{
				//		FireBall.X -= 0.1
				//	}
				//}
			}
		}

		// 패턴4. 고대웜이 아래로 내려가 바닥에 부딪히면 벽돌들이 내려온다.
		else if (AncientWorm.Pattern == 3)
		{
			AncientWorm.AncientWormState = A_ATTACK4;
			if (worldTimeCount % 20 == 0) AncientWorm.FrameX++;
			if (AncientWorm.FrameX > IMAGEMANAGER->findImage("고대웜")->getMaxFrameX()) AncientWorm.FrameX = 0;

			// 웜의 바닥이 중력값을 받아 내려온다.
			if (AncientWorm.Rc.bottom <= WINSIZE_Y)
			{
				AncientWorm.UpDown = true;
				AncientWorm.Rc.top += AncientWorm.gravity;
				AncientWorm.Rc.bottom += AncientWorm.gravity;
				AncientWorm.Y += AncientWorm.gravity;
				AncientWorm.gravity += 5;
			}
			//cout << AncientWorm.Y << endl;
			//if (AncientWorm.UpDown = true && AncientWorm.Rc.bottom < 0)
			//{
			//	int temp= -AncientWorm.Rc.bottom;
			//	AncientWorm.Rc.bottom = 0;
			//	AncientWorm.Rc.top += temp;
			//	AncientWorm.Y += temp;
			//}

			// UpDown이 true일때 벽돌 생성
			if (AncientWorm.UpDown)
			{
				if (AncientWorm.Y >= 100)
				{
					for (int i = 0; i < 10; i++)
					{
						int X = RND->getFromIntTo(0, 800);
						int Y = RND->getFromIntTo(-800, -100);

						vRock.push_back({ X, Y, RectMakeCenter(X, Y, 47, 47), 0, 0.0f, 0.0f });
					}
					AncientWorm.UpDown = false;
				}
			}

			// UpDown이 false일때 벽돌은 랜덤값을 받아 내려온다.
			if (!AncientWorm.UpDown)
			{
				IMAGEMANAGER->findImage("고대웜_벽돌")->getMemDC();
				for (int i = 0; i < vRock.size();)
				{
					vRock[i].count++;
					vRock[i].Y += RND->getFromFloatTo(0.0f, 10.0f);

					vRock[i].Rc = RectMakeCenter(vRock[i].X, vRock[i].Y, 47, 47);

					if (vRock[i].count >= 800) vRock.erase(vRock.begin() + i);
					else i++;
				}

				// 사이즈가 0이 될때 웜을 다시 제자리에 올려주고 패턴 0으로 간다.
				if (vRock.size() == 0 && AncientWorm.Pattern == 3 && !AncientWorm.Die)
				{
					AncientWorm.Rc.top -= 200;
					AncientWorm.Rc.bottom -= 200;
					AncientWorm.Y -= 200;

					AncientWorm.Pattern = 0;
				}
			}
		}

		RECT AWtemp;
		if (IntersectRect(&AWtemp, &player.AttackRc, &AncientWorm.Rc))
		{
			if (AncientWorm.Hp < 400) AncientWorm.Hp++;
		}

	}

	// 임시 이미지 바꿔야함
	if (AncientWorm.Hp == 400)
	{
		AncientWorm.Die = true;
		AncientWorm.AncientWormState = A_DIE;
		if (worldTimeCount % 10 == 0) AncientWorm.FrameX++;
		if (AncientWorm.FrameX > IMAGEMANAGER->findImage("고대웜")->getMaxFrameX()) AncientWorm.FrameX = 0;
	}
}

void Unit::AncientWormRender(void)
{
	//DrawRectMake(getMemDC(), AncientWorm.Rc);
	//DrawRectMake(getMemDC(), Laser.Rc);
	//for (int i = 0; i < vABullet.size(); i++) DrawRectMake(getMemDC(), vABullet[i].BulletRc);
	//for (int i = 0; i < vRock.size(); i++) DrawRectMake(getMemDC(), vRock[i].Rc);

	if (!AncientWorm.Die)
	{
		if (AncientWorm.Pattern == 0)
		{
			if (AncientWorm.AncientWormState == A_ATTACK1)
			{
				IMAGEMANAGER->findImage("고대웜")->frameRender(getMemDC(), AncientWorm.Rc.left, AncientWorm.Rc.top, AncientWorm.FrameX, 0);
			}
		}

		else if (AncientWorm.Pattern == 1)
		{
			if (AncientWorm.AncientWormState == A_ATTACK2)
			{
				IMAGEMANAGER->findImage("고대웜_입O")->frameRender(getMemDC(), AncientWorm.Rc.left, AncientWorm.Rc.top, AncientWorm.FrameX1, 0);
				IMAGEMANAGER->findImage("고대웜_레이저")->frameRender(getMemDC(), AncientWormLaser.Rc.left - 810, AncientWormLaser.Rc.top - 8, AncientWormLaser.LaserFrameX1, 0);
				IMAGEMANAGER->findImage("고대웜_레이저볼")->frameRender(getMemDC(), AncientWorm.Rc.left - 90, AncientWorm.Rc.top + 180, AncientWormLaser.LaserFrameX, 0);
			}
		}

		else if (AncientWorm.Pattern == 2)
		{
			if (AncientWorm.AncientWormState == A_ATTACK3)
			{
				IMAGEMANAGER->findImage("고대웜_입O")->frameRender(getMemDC(), AncientWorm.Rc.left, AncientWorm.Rc.top, AncientWorm.FrameX1, 0);

				for (int i = 0; i < vABullet.size(); i++)
				{
					if (vABullet[i].count > vABullet[i].oneShot)
					{
						IMAGEMANAGER->findImage("고대웜_화염구")->frameRender(getMemDC(), vABullet[i].BulletRc.left, vABullet[i].BulletRc.top, AncientWorm.FireballFrameX, 0);
					}
				}
			}
		}

		else if (AncientWorm.Pattern == 3)
		{
			if (AncientWorm.AncientWormState == A_ATTACK4)
			{
				IMAGEMANAGER->findImage("고대웜")->frameRender(getMemDC(), AncientWorm.Rc.left, AncientWorm.Rc.top, AncientWorm.FrameX, 0);
				for (int i = 0; i < vRock.size(); i++)
				{
					IMAGEMANAGER->findImage("고대웜_벽돌")->render(getMemDC(), vRock[i].Rc.left, vRock[i].Rc.top);
				}
			}
		}
	}

	if (AncientWorm.Die)
	{
		if (AncientWorm.AncientWormState == A_DIE)
		{
			IMAGEMANAGER->findImage("고대웜")->frameRender(getMemDC(), AncientWorm.Rc.left, AncientWorm.Rc.top, AncientWorm.FrameX, 0);
		}
	}
	IMAGEMANAGER->findImage("레드오션")->frameRender(getMemDC(), 0, 720, RedOceanFrame, 0);

}