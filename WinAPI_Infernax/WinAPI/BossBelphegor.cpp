#include "Stdafx.h"
#include "Unit.h"

void Unit::BelphegorInit(void)
{
	belphegor.FrameX = belphegor.FrameY = javelin.TrowFrameX = javelin.FrameX = javelin.TrowFrameX = 0;
	belphegor.SkillFrameX = belphegor.ScreamFrameX = belphegor.WalkFrameX = 0;
	belphegor.StandFrameX = belphegor.KickFrameX = belphegor.DieFrameX = 0;

	belphegor.BossTimeCount = /*belphegor.Time =*/ 0.0f;
	belphegor.Attack = belphegor.Pattern = belphegor.Die = false;
	belphegor.Hp = belphegor.Count = /*belphegor.DieCount = belphegor.WalkCount =*/ 0;

	belphegor.BelphegorState = B_WALK;
	javelin.X = javelin.Y = 0;
	belphegor.X = 620;
	belphegor.Y = 240;

	potal.FireballRc = RectMake(belphegor.X - 350, belphegor.Y - 150, 63, 64);

	potal.FrameX1 = potal.FrameX2 = 0;
	potal.FireBallFrameX = 0;

	//ChangeBoss = 0;

	//BelphegorPattern();
}

void Unit::BelphegorUpdate(void)
{
	belphegor.Rc = RectMake(belphegor.X + 150, belphegor.Y, 222, 390);
	belphegor.AttackRc = RectMake(belphegor.X - 60, belphegor.Y, 666, 390);
	javelin.Rc = RectMake(belphegor.X - 100, belphegor.Y + 255, 254, 127);
	// if(!belphegor.Attack) belphegor.JavelinRc = RectMake(belphegor.X + 180, belphegor.Y + 133, 348, 254);

#pragma region 보스 컷씬 업데이트

	//if (player.X < 150)
	//{
	//	player.State = P_WALK;
	//	player.X += 2;
	//	if (player.X == 150)
	//	{
	//		player.State = P_STAND;
	//	}
	//}

	// 보스 일어서기
	if (ChangeBoss == 0)
	{
		if (player.X >= 150)
		{
			if (worldTimeCount % 17 == 0) belphegor.FrameX++;
			if (belphegor.FrameX > IMAGEMANAGER->findImage("벨페고르_컷씬")->getMaxFrameX()) belphegor.FrameX = 12;
		}
		if (belphegor.FrameX == 12) ChangeBoss = 1;
	}

	// 보스 창던지기
	if (ChangeBoss == 1)
	{
		if (worldTimeCount % 17 == 0) javelin.TrowFrameX++;
		if (javelin.TrowFrameX > IMAGEMANAGER->findImage("벨페고르_창던지기")->getMaxFrameX()) javelin.TrowFrameX = 3;
		if (javelin.TrowFrameX == 3) ChangeBoss = 2;
	}

	// 창날라가는 프레임
	if (javelin.TrowFrameX >= 2)
	{
		if (worldTimeCount % 5 == 0) javelin.FrameX++;
		if (javelin.FrameX > IMAGEMANAGER->findImage("벨페고르_창")->getMaxFrameX()) javelin.FrameX = 3;
	}

	// 보스 소리치기
	if (ChangeBoss == 2)
	{
		if (worldTimeCount % 17 == 0) belphegor.ScreamFrameX++;
		if (belphegor.ScreamFrameX > IMAGEMANAGER->findImage("벨페고르_비명")->getMaxFrameX()) belphegor.ScreamFrameX = 4;

		belphegor.BossTimeCount++;
		if (belphegor.BossTimeCount < 100)
		{
			if (belphegor.ScreamFrameX == 4) ChangeBoss = 3;
		}
	}

	// 보스 걷기
	if (ChangeBoss == 3)
	{
		belphegor.X -= 0.8f;
		if (worldTimeCount % 25 == 0) belphegor.WalkFrameX++;
		if (belphegor.WalkFrameX > IMAGEMANAGER->findImage("벨페고르_걷기")->getMaxFrameX()) belphegor.WalkFrameX = 4;

		if (belphegor.X > -310)
		{
			belphegor.X -= 1.0;
		}

		if (belphegor.X < -350)
		{
			belphegor.WalkFrameX++;
			if (belphegor.WalkFrameX == 4)
			{
				ChangeBoss = 4;
			}
		}

		if (belphegor.WalkFrameX == 4)
		{
			ChangeBoss = 4;
		}
	}

	// 보스 창회수
	if (ChangeBoss == 4)
	{
		belphegor.BelphegorState = B_TAKE;
		if (worldTimeCount % 17 == 0) javelin.TakeFrameX++;
		if (javelin.TakeFrameX > IMAGEMANAGER->findImage("벨페고르_창회수")->getMaxFrameX())
		{
			belphegor.SkillFrameX = javelin.FrameX = javelin.TrowFrameX = 0;
			belphegor.ScreamFrameX = belphegor.WalkFrameX = belphegor.StandFrameX = javelin.TakeFrameX = javelin.StayFrameX = 0;
			ChangeBoss++;
			belphegor.BelphegorState = B_WALK;
		}
	}
#pragma endregion

#pragma region 보스 전투 업데이트
	if (!belphegor.Die)
	{
		// 보스 전투 시작
		if (ChangeBoss == 5)
		{
			// 공격이다 <-> 아니다 불값
			if (!belphegor.Attack)
			{
				// 전투를 시작 하면 보스는 플레이어에게 걸어온다.
				if (belphegor.BelphegorState == B_WALK)
				{
					if (worldTimeCount % 25 == 0) belphegor.WalkFrameX++;
					if (belphegor.WalkFrameX > IMAGEMANAGER->findImage("벨페고르_걷기_창")->getMaxFrameX()) belphegor.WalkFrameX = 0;

					// 왼쪽
					if (player.Rc.right < belphegor.Rc.left)
					{
						belphegor.FrameY = 0;
						belphegor.X -= 1;
					}

					// 오른쪽
					else if (player.Rc.left > belphegor.Rc.right)
					{
						belphegor.FrameY = 1;
						belphegor.X += 1;
					}
				}

				// 걸어오고 나서 플레이어가 충돌용 렉트에 부딪히면 창이 날라온다.
				RECT temp;
				if (IntersectRect(&temp, &player.Rc, &belphegor.AttackRc) && belphegor.Count == 0 && !belphegor.Die)
				{
					belphegor.Attack = true;
					belphegor.Count = 1;
					//belphegor.Count = qBelphegor.front();
					//qBelphegor.pop();
					//if (qBelphegor.empty()) BelphegorPattern();
				}

			}

			// 전투가 true 일때 패턴 4개
			if (belphegor.Attack)
			{
				// 창던지기
				if (belphegor.Count == 1)
				{
					belphegor.BelphegorState = B_ATTACK;
				}
				// 걷기
				else if (belphegor.Count == 2)
				{
					belphegor.BelphegorState = B_ATTACK2;
				}
				// 화염구 소환
				else if (belphegor.Count == 3)
				{
					belphegor.BelphegorState = B_ATTACK3;
				}
				// 발차기
				else if (belphegor.Count == 4)
				{
					belphegor.BelphegorState = B_ATTACK4;
				}
			}

			// 패턴1 창던지기
			if (belphegor.BelphegorState == B_ATTACK)
			{
				if (worldTimeCount % 17 == 0) javelin.TrowFrameX++;
				if (javelin.TrowFrameX > IMAGEMANAGER->findImage("벨페고르_창던지기")->getMaxFrameX()) javelin.TrowFrameX = 3;
				if (javelin.TrowFrameX == 3) belphegor.BelphegorState = B_WALK2;

				// 던지는 모션이 max일때 창 없이 걷는 모션이 나온다.
				if (belphegor.BelphegorState == B_WALK2)
				{
					if (worldTimeCount % 25 == 0) belphegor.WalkFrameX++;
					if (belphegor.WalkFrameX > IMAGEMANAGER->findImage("벨페고르_걷기")->getMaxFrameX()) belphegor.WalkFrameX = 0;

					// 창이 바닥에 꽂힌 뒤에 보스는 플레이어를 따라가지 않고 창을 향해 간다
					if (belphegor.Rc.left - 150 - javelin.X > 0)
					{
						//belphegor.X -= 1;
						belphegor.BelphegorState = B_TAKE;
					}

					if (belphegor.Rc.right - javelin.X <= 0)
					{
						//belphegor.X += 1;
						belphegor.BelphegorState = B_TAKE;
					}
				}

				// 창 근처에 다다르면 보스는 줍는 모션을 취하고 창은 없어져야 한다.
				if (belphegor.BelphegorState == B_TAKE)
				{
					if (worldTimeCount % 17 == 0) javelin.TakeFrameX++;
					if (javelin.TakeFrameX > IMAGEMANAGER->findImage("벨페고르_창회수")->getMaxFrameX()) javelin.TakeFrameX = 4;
					if (javelin.TakeFrameX == 4 && belphegor.Count == 1 && !belphegor.Die)
					{
						javelin.TrowFrameX = javelin.TakeFrameX = 0;
						belphegor.Count = 2;
						//belphegor.Count = qBelphegor.front();
						//qBelphegor.pop();
						//if (qBelphegor.empty()) BelphegorPattern();
					}
					//belphegor.BelphegorState = B_WALK;
					//belphegor.WalkFrameX = javelin.TrowFrameX = javelin.TakeFrameX = 0;
					//if (belphegor.BelphegorState != B_WALK)
					//{
					//	belphegor.WalkCount = TIMEMANAGER->getWorldTime();
					//}
					//else
					//{
					//	if (belphegor.WalkCount + 6.0f <= TIMEMANAGER->getWorldTime())
					//	{
					//		belphegor.Count = 2;
					//	}
					//	if (belphegor.Count == 2)
					//	{
					//		belphegor.BelphegorState = B_ATTACK2;
					//	}
					//}
				}
			}

			// 패턴2 걷기 후 다시 렉트와 충돌되면 다른 패턴으로 넘어간다.
			else if (belphegor.BelphegorState == B_ATTACK2)
			{
				if (worldTimeCount % 25 == 0) belphegor.WalkFrameX++;
				if (belphegor.WalkFrameX > IMAGEMANAGER->findImage("벨페고르_걷기_창")->getMaxFrameX()) belphegor.WalkFrameX = 0;

				// 왼쪽
				if (player.Rc.right < belphegor.Rc.left)
				{
					belphegor.FrameY = 0;
					belphegor.X -= 1;
				}
				// 오른쪽
				else if (player.Rc.left > belphegor.Rc.right)
				{
					belphegor.FrameY = 1;
					belphegor.X += 1;
				}

				if (player.Rc.right + 50 >= belphegor.Rc.left || player.Rc.left - 50 <= belphegor.Rc.right && belphegor.Count == 2 && !belphegor.Die)
				{
					belphegor.Count = 3;
				}
			}

			// 패턴3 화염구를 던진다.
			else if (belphegor.BelphegorState == B_ATTACK3)
			{
				if (worldTimeCount % 17 == 0) belphegor.ScreamFrameX++;
				if (belphegor.ScreamFrameX > IMAGEMANAGER->findImage("벨페고르_비명_창")->getMaxFrameX()) belphegor.ScreamFrameX = 3;

				if (worldTimeCount % 10 == 0) potal.FrameX1++;
				if (potal.FrameX1 > IMAGEMANAGER->findImage("벨페고르_소환포탈3")->getMaxFrameX()) potal.FrameX1 = 8;

				if (potal.FrameX1 >= 1)
				{
					if (worldTimeCount % 10 == 0) potal.FireBallFrameX++;
					if (potal.FireBallFrameX > IMAGEMANAGER->findImage("벨페고르_화염구")->getMaxFrameX()) potal.FireBallFrameX = 0;
					potal.FireballRc.bottom += 6;
					potal.FireballRc.top += 6;
				}

				if (potal.FrameX1 == 8 && belphegor.Count == 3 && !belphegor.Die)
				{
					potal.FrameX1--;
					belphegor.ScreamFrameX = potal.FrameX1 = potal.FireBallFrameX = 0;
					belphegor.Count = 4;
				}
				//if (belphegor.BelphegorState != B_ATTACK2)
				//{
				//	belphegor.WalkCount = TIMEMANAGER->getWorldTime();
				//}
				//else
				//{
				//	if (belphegor.WalkCount + 6.0f <= TIMEMANAGER->getWorldTime())
				//	{
				//		belphegor.Count = 4;
				//	}
				//}
			}

			// 패턴4 발차기
			else if (belphegor.BelphegorState == B_ATTACK4)
			{
				if (worldTimeCount % 17 == 0) belphegor.KickFrameX++;
				if (belphegor.KickFrameX > IMAGEMANAGER->findImage("벨페고르_발차기")->getMaxFrameX()) belphegor.KickFrameX = 3;

				if (belphegor.KickFrameX == 3 && belphegor.Count == 4 && !belphegor.Die)
				{
					belphegor.KickFrameX = 0;
					// belphegor.WalkCount = TIMEMANAGER->getWorldTime();
					belphegor.Count = 1;
				}
				//if (belphegor.BelphegorState != B_ATTACK2)
				//{
				//	belphegor.WalkCount = TIMEMANAGER->getWorldTime();
				//}
				//else
				//{
				//	if (belphegor.WalkCount + 6.0f <= TIMEMANAGER->getWorldTime())
				//	{
				//		belphegor.Count = 1;
				//	}
				//}
			}
			RECT BPGtemp;
			if (player.FrameY == 0)
			{
				if (IntersectRect(&BPGtemp, &player.AttackRc, &belphegor.Rc))
				{
					if (belphegor.Hp < 400)
					{
						belphegor.Hp++;
					}
				}
			}

			if (player.FrameY == 1)
			{
				if (IntersectRect(&BPGtemp, &player.AttackRc, &belphegor.Rc))
				{
					if (belphegor.Hp < 400)
					{
						belphegor.Hp++;
					}
				}
			}

			if(belphegor.Hp == 400)
			{
				belphegor.Die = true;
			}

		}
	}
	else if (belphegor.Die)
	{
		belphegor.BelphegorState = B_DIE;
		if (worldTimeCount % 25 == 0) belphegor.DieFrameX++;
		if (belphegor.DieFrameX > IMAGEMANAGER->findImage("벨페고르_죽음")->getMaxFrameX()) belphegor.DieFrameX = 16;
	}
}

//if (ChangeBoss == 5)
//{	
//	// 어택 안 할때는 보스 걷기
//	if (!belphegor.Attack)
//	{
//		if (belphegor.BelphegorState != E_WALK2)
//		{
//			belphegor.BelphegorState = E_WALK;
//			if (worldTimeCount % 25 == 0) belphegor.WalkFrameX++;
//			if (belphegor.WalkFrameX > IMAGEMANAGER->findImage("벨페고르_걷기_창")->getMaxFrameX()) belphegor.WalkFrameX = 0;
//			if (player.Rc.right < belphegor.Rc.left)
//			{
//				belphegor.FrameY = 0;
//				belphegor.X -= 1;
//			}
//			if (player.Rc.left > belphegor.Rc.right)
//			{
//				belphegor.FrameY = 1;
//				belphegor.X += 1;
//			}
//		}
//		// else
//		// {
//		// 	if (worldTimeCount % 25 == 0) belphegor.WalkFrameX++;
//		// 	if (belphegor.WalkFrameX > IMAGEMANAGER->findImage("벨페고르_걷기_창")->getMaxFrameX()) belphegor.WalkFrameX = 0;
//		// 
//		// 	if (belphegor.X - belphegor.JavelinX > 0)
//		// 	{
//		// 		belphegor.X -= 1;
//		// 	}
//		// 
//		// 	if (belphegor.X - belphegor.JavelinX <= 0)
//		// 	{
//		// 		belphegor.BelphegorState = E_TAKE;
//		// 	}
//		// }
//		// 
//		// 
//		// 자벨린 회수하러 가기
//		//else
//		//{
//		//	if (belphegor.JavelinX < belphegor.Rc.left)
//		//	{
//		//		belphegor.X -= 1;
//		//		//cout << "자벨린 ㄱ" << endl;
//		//	}
//		//	if (belphegor.JavelinX > belphegor.Rc.right)
//		//	{
//		//		belphegor.X += 1;
//		//		//cout << "자벨린 ㄱ" << endl;
//		//	}
//		//	//cout << "지벨린" << belphegor.JavelinX << endl;
//		//	//cout << "보스" << belphegor.Rc.left << endl;
//		//}
//	}
//	// 어택이 true가 되면 어택모션 후 창 던지는 프레임
//	else if (belphegor.Attack)
//	{
//		belphegor.BelphegorState = E_ATTACK;
//		if (worldTimeCount % 17 == 0) belphegor.JavelinTrowFrameX++;
//		if (belphegor.JavelinTrowFrameX > IMAGEMANAGER->findImage("벨페고르_창던지기")->getMaxFrameX())
//		{
//			belphegor.BelphegorState = E_WALK2;
//		}
//	}
//	// 충돌 렉트(플레이어와 충돌용 보스 렉트) 충돌하면 보스가 창을 던지는 모션
//	RECT Belphe;
//	if (IntersectRect(&Belphe, &player.Rc, &belphegor.AttackRc))
//	{
//		belphegor.Attack = true;
//	}
//	// 던지는 모션이 맥스 프레임일때 어택 false, 창 없는 보스 걷기 모션
//	if (belphegor.BelphegorState == E_WALK2)
//	{
//		belphegor.Attack = false;
//		if (worldTimeCount % 25 == 0) belphegor.WalkFrameX++;
//		if (belphegor.WalkFrameX > IMAGEMANAGER->findImage("벨페고르_걷기")->getMaxFrameX()) belphegor.WalkFrameX = 0;
//		if (belphegor.X - belphegor.JavelinX > 0)
//		{
//			belphegor.X -= 1;
//		}
//		if (belphegor.X - belphegor.JavelinX <= 0)
//		{
//			belphegor.BelphegorState = E_TAKE;
//		}
//		if (player.Rc.right < belphegor.Rc.left)
//		{
//			belphegor.FrameY = 0;
//		}
//		if (player.Rc.left > belphegor.Rc.right)
//		{
//			belphegor.FrameY = 1;
//		}
//	}
//}

#pragma endregion


void Unit::BelphegorRender(void)
{

#pragma region 보스 컷씬 랜더

	if (ChangeBoss == 0)
	{
		IMAGEMANAGER->findImage("벨페고르_컷씬")->frameRender(getMemDC(), belphegor.X, belphegor.Y - 40, belphegor.FrameX, 0);
	}

	else if (ChangeBoss == 1)
	{
		IMAGEMANAGER->findImage("벨페고르_창던지기")->frameRender(getMemDC(), belphegor.X, belphegor.Y, javelin.TrowFrameX, 0);
	}

	else if (ChangeBoss == 2)
	{
		IMAGEMANAGER->findImage("벨페고르_비명")->frameRender(getMemDC(), belphegor.X, belphegor.Y, belphegor.ScreamFrameX, 0);
	}

	else if (ChangeBoss == 3)
	{
		IMAGEMANAGER->findImage("벨페고르_걷기")->frameRender(getMemDC(), belphegor.X + 37, belphegor.Y, belphegor.WalkFrameX, 0);
	}

	else if (ChangeBoss == 4)
	{
		IMAGEMANAGER->findImage("벨페고르_창회수")->frameRender(getMemDC(), belphegor.X, belphegor.Y, javelin.TakeFrameX, 0);
	}

	if (javelin.TrowFrameX >= 2 && javelin.TakeFrameX <= 1 && ChangeBoss < 5)
	{
		IMAGEMANAGER->findImage("벨페고르_창")->frameRender(getMemDC(), javelin.X + 400, belphegor.Y, javelin.FrameX, 0);
	}


#pragma endregion

#pragma region 보스 전투 랜더
	// 0 일때 오른쪽 -> 왼쪽
	// 1 일때 왼쪽 -> 오른쪽
	if (ChangeBoss == 5)
	{
		// 공격 하지 않을때 / 창을 들고 걷는다.
		if (!belphegor.Attack)
		{
			if (belphegor.BelphegorState == B_WALK)
			{
				if (belphegor.FrameY == 1)
					IMAGEMANAGER->findImage("벨페고르_걷기_창")->frameRender(getMemDC(), belphegor.Rc.left - 40, belphegor.Rc.top, belphegor.WalkFrameX, belphegor.FrameY);
				else if (belphegor.FrameY == 0)
					IMAGEMANAGER->findImage("벨페고르_걷기_창")->frameRender(getMemDC(), belphegor.Rc.left - 55, belphegor.Rc.top, belphegor.WalkFrameX, belphegor.FrameY);
			}
		}
		// 공격을 시작할때 / 패턴 = 창던지기, 화염구 소환, 발차기
		else if (belphegor.Attack)
		{
			// 패턴1 창던지기
			if (belphegor.Count == 1)
			{
				if (belphegor.BelphegorState == B_ATTACK)
				{
					if (belphegor.FrameY == 1)
						IMAGEMANAGER->findImage("벨페고르_창던지기")->frameRender(getMemDC(), belphegor.Rc.left - 155, belphegor.Rc.top, javelin.TrowFrameX, belphegor.FrameY);
					else if (belphegor.FrameY == 0)
						IMAGEMANAGER->findImage("벨페고르_창던지기")->frameRender(getMemDC(), belphegor.Rc.left - 105, belphegor.Rc.top, javelin.TrowFrameX, belphegor.FrameY);
				}

				if (belphegor.BelphegorState == B_WALK2)
				{
					if (belphegor.FrameY == 1)
						IMAGEMANAGER->findImage("벨페고르_걷기")->frameRender(getMemDC(), belphegor.Rc.left - 65, belphegor.Rc.top, belphegor.WalkFrameX, belphegor.FrameY);
					else if (belphegor.FrameY == 0)
						IMAGEMANAGER->findImage("벨페고르_걷기")->frameRender(getMemDC(), belphegor.Rc.left - 105, belphegor.Rc.top, belphegor.WalkFrameX, belphegor.FrameY);
				}

				if (belphegor.BelphegorState == B_TAKE)
				{
					if (belphegor.FrameY == 1)
						IMAGEMANAGER->findImage("벨페고르_창회수")->frameRender(getMemDC(), belphegor.Rc.left - 195, belphegor.Rc.top, javelin.TakeFrameX, belphegor.FrameY);
					else if (belphegor.FrameY == 0)
						IMAGEMANAGER->findImage("벨페고르_창회수")->frameRender(getMemDC(), belphegor.Rc.left - 155, belphegor.Rc.top, javelin.TakeFrameX, belphegor.FrameY);
				}
			}

			//패턴2 걷기
			else if (belphegor.Count == 2)
			{
				if (belphegor.BelphegorState == B_ATTACK2)
				{
					if (belphegor.FrameY == 1)
						IMAGEMANAGER->findImage("벨페고르_걷기_창")->frameRender(getMemDC(), belphegor.Rc.left - 55, belphegor.Rc.top, belphegor.WalkFrameX, belphegor.FrameY);
					else if (belphegor.FrameY == 0)
						IMAGEMANAGER->findImage("벨페고르_걷기_창")->frameRender(getMemDC(), belphegor.Rc.left - 55, belphegor.Rc.top, belphegor.WalkFrameX, belphegor.FrameY);
				}
			}

			//패턴3 화염구 소환하기
			else if (belphegor.Count == 3)
			{
				if (belphegor.BelphegorState == B_ATTACK3)
				{
					if (belphegor.FrameY == 1)
						IMAGEMANAGER->findImage("벨페고르_비명_창")->frameRender(getMemDC(), belphegor.Rc.left - 193, belphegor.Rc.top, belphegor.ScreamFrameX, belphegor.FrameY);
					else if (belphegor.FrameY == 0)
						IMAGEMANAGER->findImage("벨페고르_비명_창")->frameRender(getMemDC(), belphegor.Rc.left - 156, belphegor.Rc.top, belphegor.ScreamFrameX, belphegor.FrameY);

					if (belphegor.FrameY == 1)
						IMAGEMANAGER->findImage("벨페고르_화염구")->frameRender(getMemDC(), potal.FireballRc.left, potal.FireballRc.top, potal.FireBallFrameX, belphegor.FrameY);
					else if (belphegor.FrameY == 0)
						IMAGEMANAGER->findImage("벨페고르_화염구")->frameRender(getMemDC(), potal.FireballRc.left, potal.FireballRc.top + 70, potal.FireBallFrameX, belphegor.FrameY);

					if (belphegor.FrameY == 1)
						IMAGEMANAGER->findImage("벨페고르_소환포탈3")->frameRender(getMemDC(), belphegor.Rc.left + 330, belphegor.Rc.top - 220, potal.FrameX1, belphegor.FrameY);
					else if (belphegor.FrameY == 0)
						IMAGEMANAGER->findImage("벨페고르_소환포탈3")->frameRender(getMemDC(), belphegor.Rc.left - 250, belphegor.Rc.top - 220, potal.FrameX1, belphegor.FrameY);
					//if (belphegor.ChangePotal)
					//{
					//	if (belphegor.FrameY == 1)
					//		IMAGEMANAGER->findImage("벨페고르_소환포탈1")->frameRender(getMemDC(), belphegor.Rc.left - 200, belphegor.Rc.top, potal.FrameX1, belphegor.FrameY);
					//	else if (belphegor.FrameY == 0)
					//		IMAGEMANAGER->findImage("벨페고르_소환포탈1")->frameRender(getMemDC(), belphegor.Rc.left - 200, belphegor.Rc.top - 200, potal.FrameX1, belphegor.FrameY);
					//}
					//else
					//{
					//	if (belphegor.FrameY == 1)
					//		IMAGEMANAGER->findImage("벨페고르_소환포탈2")->frameRender(getMemDC(), belphegor.Rc.left - 200, belphegor.Rc.top, potal.FrameX2, belphegor.FrameY);
					//	else if (belphegor.FrameY == 0)
					//		IMAGEMANAGER->findImage("벨페고르_소환포탈2")->frameRender(getMemDC(), belphegor.Rc.left - 200, belphegor.Rc.top - 200, potal.FrameX2, belphegor.FrameY);
					//}
				}
			}

			// 패턴4 발차기
			else if (belphegor.Count == 4)
			{
				if (belphegor.BelphegorState == B_ATTACK4)
				{
					if (belphegor.FrameY == 1)
						IMAGEMANAGER->findImage("벨페고르_발차기")->frameRender(getMemDC(), belphegor.Rc.left - 230, belphegor.Rc.top - 15, belphegor.KickFrameX, belphegor.FrameY);
					else if (belphegor.FrameY == 0)
						IMAGEMANAGER->findImage("벨페고르_발차기")->frameRender(getMemDC(), belphegor.Rc.left - 125, belphegor.Rc.top - 15, belphegor.KickFrameX, belphegor.FrameY);
				}
			}
		}

		// 보스가 창을 던졌을 시 창 고정
		if (!belphegor.Attack)
		{
			if (belphegor.FrameY == 1)
			{
				javelin.Rc.left = belphegor.Rc.left + 300;
				javelin.Rc.top = belphegor.Rc.top;
			}

			else if (belphegor.FrameY == 0)
			{
				javelin.Rc.left = belphegor.Rc.left - 300;
				javelin.Rc.top = belphegor.Rc.top;
			}
		}

		// 벨페고르의 창은 앞에 나와있어야 하므로 따로 밖으로 빼준다.
		if (javelin.TrowFrameX >= 2 && javelin.TakeFrameX <= 1)
		{
			if (belphegor.FrameY == 1)
				IMAGEMANAGER->findImage("벨페고르_창")->frameRender(getMemDC(), javelin.Rc.left + 500, javelin.Rc.top - 255, javelin.FrameX, belphegor.FrameY);
			if (belphegor.FrameY == 0)
				IMAGEMANAGER->findImage("벨페고르_창")->frameRender(getMemDC(), javelin.Rc.left - 50, javelin.Rc.top - 255, javelin.FrameX, belphegor.FrameY);
		}
	}

	if (belphegor.Die)
	{
		if (belphegor.BelphegorState == B_DIE)
		{
			if (belphegor.FrameY == 1)
				IMAGEMANAGER->findImage("벨페고르_죽음")->frameRender(getMemDC(), belphegor.Rc.left - 320, belphegor.Rc.top - 60, belphegor.DieFrameX, belphegor.FrameY);
			if (belphegor.FrameY == 0)
				IMAGEMANAGER->findImage("벨페고르_죽음")->frameRender(getMemDC(), belphegor.Rc.left - 270, belphegor.Rc.top - 60, belphegor.DieFrameX, belphegor.FrameY);
		}
	}
#pragma endregion
	//DrawRectMake(getMemDC(), RectMake(belphegor.JavelinX, belphegor.JavelinY, 10, 10));
}

//void Unit::BelphegorPattern(void)
//{
//	qBelphegor.push(1);
//	qBelphegor.push(2);
//	qBelphegor.push(3);
//	qBelphegor.push(2);
//	qBelphegor.push(4);
//	qBelphegor.push(2);
//}
