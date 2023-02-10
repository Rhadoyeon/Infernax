#include "Stdafx.h"
#include "Unit.h"

void Unit::BelphegorInit(void)
{
	belphegor.FrameX = belphegor.FrameY = javelin.TrowFrameX = javelin.FrameX = javelin.TrowFrameX = 0;
	belphegor.BelphegorState = B_WALK;

	javelin.X = javelin.Y = 0;
	belphegor.X = 620;
	belphegor.Y = 240;
	belphegor.BossTimeCount = 0.0f;
	belphegor.Attack = belphegor.Pattern = belphegor.Die = false;
	belphegor.Count = belphegor.DieCount = 0;

	ChangeBoss = 0;
	BossPattern = 0;
}

void Unit::BelphegorUpdate(void)
{
	belphegor.Rc = RectMake(belphegor.X + 150, belphegor.Y, 222, 390);
	belphegor.AttackRc = RectMake(belphegor.X - 60, belphegor.Y, 666, 390);
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
		if(belphegor.FrameX == 12) ChangeBoss = 1;
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
		if (belphegor.ScreamFrameX > IMAGEMANAGER->findImage("벨페고르_외침")->getMaxFrameX()) belphegor.ScreamFrameX = 4;
		
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
				if (player.Rc.left > belphegor.Rc.right)
				{
					belphegor.FrameY = 1;
					belphegor.X += 1;
				}
			}

			// 걸어오고 나서 플레이어가 충돌용 렉트에 부딪히면 창이 날라온다.
			RECT temp;
			if (IntersectRect(&temp, &player.Rc, &belphegor.AttackRc)/*&& !&belphegor.Rc*/)
			{
				belphegor.Attack = true;
				belphegor.Count = 1;
				belphegor.BelphegorState = B_ATTACK;
			}
		}

		// 불값과 공격 카운트, 다이 카운트
		// 보스 공격 상태
		// 창던지기
		// 두번째 충돌 다른 패턴 소환하는 불공, 세번째 충돌 발차기....
		// 카운트가 점점 올라간 후 세번째 카운트일때 다시 0로 ㄱㄱ.
		// 플레이어가 어택
		// 다이 카운트 올라가게 한 후 일정 이상 일 경우 죽음.

		else if (belphegor.Attack)
		{
			if (belphegor.Count == 1)
			{
				if (belphegor.BelphegorState == B_ATTACK)
				{
					if (worldTimeCount % 17 == 0) javelin.TrowFrameX++;
					if (javelin.TrowFrameX > IMAGEMANAGER->findImage("벨페고르_창던지기")->getMaxFrameX()) javelin.TrowFrameX = 3;
					if (javelin.TrowFrameX == 3) belphegor.BelphegorState = B_WALK2;
				}

				// 던지는 모션이 max일때 창 없이 걷는 모션이 나온다.
				if (belphegor.BelphegorState == B_WALK2)
				{
					if (worldTimeCount % 25 == 0) belphegor.WalkFrameX++;
					if (belphegor.WalkFrameX > IMAGEMANAGER->findImage("벨페고르_걷기")->getMaxFrameX()) belphegor.WalkFrameX = 0;

					// 창이 바닥에 꽂힌 뒤에 보스는 플레이어를 따라가지 않고 창을 향해 간다
					if (belphegor.Rc.left - 150 - javelin.X > 0)
					{
						belphegor.X -= 1;
						belphegor.BelphegorState = B_TAKE;
					}

					if (belphegor.Rc.right - javelin.X <= 0)
					{
						belphegor.X += 1;
						belphegor.BelphegorState = B_TAKE;
					}
				}

				// 창 근처에 다다르면 보스는 줍는 모션을 취하고 창은 없어져야 한다.
				if (belphegor.BelphegorState == B_TAKE)
				{
					if (worldTimeCount % 17 == 0) javelin.TakeFrameX++;
					if (javelin.TakeFrameX > IMAGEMANAGER->findImage("벨페고르_창회수")->getMaxFrameX()) javelin.TakeFrameX = 4;
					if (javelin.TakeFrameX == 4)
					{
						belphegor.BelphegorState = B_WALK;
						belphegor.WalkFrameX = javelin.TrowFrameX = javelin.TakeFrameX = 0;
						belphegor.Count = 2;
					}
				}

				if (belphegor.BelphegorState == B_WALK)
				{
					belphegor.Attack = false;
				}
			}

			if (belphegor.Count == 2)
			{
				if (belphegor.BelphegorState = B_ATTACK2)
				{
					if (worldTimeCount % 17 == 0) javelin.TakeFrameX++;
					if (javelin.TakeFrameX > IMAGEMANAGER->findImage("벨페고르_소환포탈")->getMaxFrameX()) javelin.TakeFrameX = 3;
					if (javelin.TakeFrameX == 3)
					{
						if (worldTimeCount % 17 == 0) javelin.TakeFrameX++;
						if (javelin.TakeFrameX > IMAGEMANAGER->findImage("벨페고르_소환포탈2")->getMaxFrameX()) javelin.TakeFrameX = 0;
					}
				}
			}
			// 창을 주운 뒤 다시 플레이어를 따라가야하며 플레이어가 충돌용 렉트에 부딪히면 창을 던지는 공격이 나와야한다
			//if()
			// 공격이다
			// 창을 던졌다
			// 창이 없이 걷는다.
			// 창을 가지러 간다
			// 창을 회수하면
			// 공격 상태도 풀리고 상태도 walk로 바꾸고 플레이어를 바라본다.
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
}

void Unit::BelphegorRender(void)
{

#pragma region 보스 컷씬 랜더

	if (ChangeBoss == 0)
	{
		IMAGEMANAGER->findImage("벨페고르_컷씬")->frameRender(getMemDC(), belphegor.X, belphegor.Y - 40, belphegor.FrameX, 0);
	}

	if (ChangeBoss == 1)
	{
		IMAGEMANAGER->findImage("벨페고르_창던지기")->frameRender(getMemDC(), belphegor.X, belphegor.Y, javelin.TrowFrameX, 0);
	}

	else if (ChangeBoss == 2)
	{
		IMAGEMANAGER->findImage("벨페고르_외침")->frameRender(getMemDC(), belphegor.X, belphegor.Y, belphegor.ScreamFrameX, 0);
	}

	else if (ChangeBoss == 3)
	{
		IMAGEMANAGER->findImage("벨페고르_걷기")->frameRender(getMemDC(), belphegor.X, belphegor.Y, belphegor.WalkFrameX, 0);
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
		if (!belphegor.Attack)
		{
			if (belphegor.BelphegorState == B_WALK)
			{
				if (belphegor.FrameY == 1)
					IMAGEMANAGER->findImage("벨페고르_걷기_창")->frameRender(getMemDC(), belphegor.Rc.left - 55, belphegor.Rc.top, belphegor.WalkFrameX, belphegor.FrameY);
				else if (belphegor.FrameY == 0)
					IMAGEMANAGER->findImage("벨페고르_걷기_창")->frameRender(getMemDC(), belphegor.Rc.left - 55, belphegor.Rc.top, belphegor.WalkFrameX, belphegor.FrameY);
			}
		}
		else if (belphegor.Attack)
		{
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

			if (belphegor.Count == 2)
			{

			}
		}
		
		
		if (!belphegor.Attack)
		{
			if (belphegor.FrameY == 1)
			{
				javelin.X = belphegor.Rc.left + 300;
				javelin.Y = belphegor.Rc.top;
			}

			else if (belphegor.FrameY == 0)
			{
				javelin.X = belphegor.Rc.left - 300;
				javelin.Y = belphegor.Rc.top;
			}
		}

		if (javelin.TrowFrameX >= 2 && javelin.TakeFrameX <= 1)
			IMAGEMANAGER->findImage("벨페고르_창")->frameRender(getMemDC(), javelin.X, javelin.Y, javelin.FrameX, belphegor.FrameY);
	}
#pragma endregion
	//DrawRectMake(getMemDC(), RectMake(belphegor.JavelinX, belphegor.JavelinY, 10, 10));
}
