#include "Stdafx.h"
#include "Unit.h"

void Unit::playerInit(void)
{
	SOUNDMANAGER->addSound("플레이어_타격", "Resources/Sounds/PlayerHit.wav", false, false);
	SOUNDMANAGER->addSound("플레이어_점프", "Resources/Sounds/PlayerJump.wav", false, false);

#pragma region 플레이어 변수 초기화
	player.X = 900;
	player.Y = 570;

	player.FrameX = player.FrameY = player.JumpFrameX = 0;
	villageMove = false;

	player.State = P_STAND;
	player.Inven = MAGIC;

	player.Die = player.Jump = player.JumpCount = player.Inventory = player.Move = /*player.MoveCheck*/ false;

	player.moveControl = 0;

	player.colliChkDown = false;

	player.Speed = player.Gravity = 0.0f;
	player.Rc = RectMakeCenter(player.X, player.Y, 69, 103);

	bgMove3 = 720;
#pragma endregion

	for (int i = 0; i < _countof(playerCrash); i++)
	{
		playerCrash[i] = false;
	}
}

void Unit::playerUpdate(void)
{
	player.Rc = RectMakeCenter(player.X, player.Y, 69, 103);
	player.DownRc = RectMakeCenter(player.Rc.left + 33, player.Rc.top + 97, 10, 10);

#pragma region 픽셀 충돌
	//	// 업
	//	for (int i = player.UpRc.left - 10; i < player.UpRc.right + 10; i++)
	//	{
	//		COLORREF UpColor = GetPixel(IMAGEMANAGER->findImage("픽셀_전투3")->getMemDC(),
	//			i + bgMove3, player.UpRc.top + 200);
	//
	//		int UpR = GetRValue(UpColor);
	//		int UpG = GetGValue(UpColor);
	//		int UpB = GetBValue(UpColor);
	//
	//
	//		if (UpR == 255 && UpG == 0 && UpB == 0)
	//		{
	//			player.colliChkUp = true;
	//		}
	//
	//		else
	//		{
	//			player.colliChkUp = false;
	//			//player.Gravity -= 0.5f;
	//		}
	//
	//		if (player.colliChkUp)
	//		{
	//			player.Y += 0.1f;
	//		}
	//	}
		// 다운
	for (int i = player.DownRc.left - 10; i < player.DownRc.right + 10; i++)
	{
		COLORREF DownColor = GetPixel(IMAGEMANAGER->findImage("픽셀_전투3")->getMemDC(),
			i + bgMove3, player.DownRc.bottom + 200);

		int DownR = GetRValue(DownColor);
		int DownG = GetGValue(DownColor);
		int DownB = GetBValue(DownColor);


		if (DownR == 255 && DownG == 0 && DownB == 0)
		{
			player.colliChkDown = true;
		}

		else
		{
			player.colliChkDown = false;
			//player.Gravity -= 0.5f;
		}

		if (player.colliChkDown)
		{
			player.Y += 0.00001f;
			//player.Gravity -= 0.2f;
		}
	}
	//	// 오른쪽
	//	for (int i = player.RightRc.top - 10; i < player.RightRc.bottom + 10; i++)
	//	{
	//
	//		COLORREF RightColor = GetPixel(IMAGEMANAGER->findImage("픽셀_전투3")->getMemDC(),
	//			player.RightRc.right + bgMove3 + 20, i + 200);
	//
	//		int RightR = GetRValue(RightColor);
	//		int RightG = GetGValue(RightColor);
	//		int RightB = GetBValue(RightColor);
	//
	//
	//		if (RightR == 255 && RightG == 0 && RightB == 0)
	//		{
	//			player.colliChkRight = true;
	//		}
	//
	//		else
	//		{
	//			player.colliChkRight = false;
	//		}
	//
	//		if (player.colliChkRight)
	//		{
	//			player.X += 0.1f;
	//		}
	//	}
	//
	//	// 왼쪽
	//	for (int i = player.LeftRc.top - 10; i < player.LeftRc.bottom + 10; i++)
	//	{
	//
	//		COLORREF LeftColor = GetPixel(IMAGEMANAGER->findImage("픽셀_전투3")->getMemDC(),
	//			player.LeftRc.left + bgMove3, i + 200);
	//
	//		int LeftR = GetRValue(LeftColor);
	//		int LeftG = GetGValue(LeftColor);
	//		int LeftB = GetBValue(LeftColor);
	//
	//
	//		if (LeftR == 255 && LeftG == 0 && LeftB == 0)
	//		{
	//			player.colliChkLeft = true;
	//		}
	//		else
	//		{
	//			player.colliChkLeft = false;
	//		}
	//
	//		if (player.colliChkLeft)
	//		{
	//			player.X += 0.1f;
	//		}
	//	}
#pragma endregion

#pragma region 키 입력 시 플레이어 이동

	if (!villageMove)
	{
		if (player.X > WINSIZE_X / 2)
		{
			player.Move = true;
		}
		if (player.X < WINSIZE_X / 2)
		{
			player.Move = false;
		}

		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			//player.MoveCheck = false;
			player.X -= 2;
			player.State = P_WALK;
			player.Right = false;
		}

		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			player.State = P_STAND;
		}

		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			//player.MoveCheck = false;
			player.X += 2;
			player.State = P_WALK;
			player.Right = true;
		}

		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			player.State = P_STAND;
		}
	}

	if (villageMove)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			player.X -= 2;
			player.State = P_WALK;
			player.Right = false;

			if (WINSIZE_X / 2 < player.X)
			{
				bgMove += 2.0f;
				bgMove3 += 2.0f;
			}
			//else
			//{
			//	player.State = P_WALK;
			//	player.Right = false;
			//	bgMove += 2.0f;
			//	bgMove3 += 2.0f;
			//}
		}

		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			player.State = P_STAND;
		}


		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			player.X += 2;
			player.State = P_WALK;
			player.Right = true;

			if (WINSIZE_X / 2 > player.X)
			{
				bgMove -= 2.0f;
				bgMove3 -= 2.0f;
			}

			//else
			//{
			//	player.State = P_WALK;
			//	player.Right = true;
			//	bgMove -= 2.0f;
			//	bgMove3 -= 2.0f;
			//}
		}
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			player.State = P_STAND;
		}


		if (bgMove > 2100 && KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			bgMove = 2100;
			player.X -= 2;
		}

		if (bgMove3 > 1440 && KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			bgMove3 = 1440;
			player.X += 2;
		}


		if (bgMove < 200 && KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			bgMove = 200;
			player.X += 2;
		}

		if (bgMove3 < 720 && KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			bgMove3 = 720;
			player.X -= 2;
		}

	}


	//if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	//{
	//	if (villageMove)
	//	{
	//		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	//		{
	//			if (!playerCrash[0])
	//			{
	//				player.X -= 2.0f;
	//				bgMove3 += 2.0f;
	//				player.State = P_WALK;
	//				player.Right = false;
	//			}
	//			else if (playerCrash[0])
	//			{
	//				if (WINSIZE_X / 2 < player.X)
	//				{
	//					player.X += 2.0f;
	//					bgMove3 -= 2.0f;
	//				}
	//			}
	//		}
	//	}
	//}

	//if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	//{
	//	if (villageMove)
	//	{
	//		if (!playerCrash[2])
	//		{
	//			player.X += 2.0f;
	//			bgMove3 -= 2.0f;
	//		}
	//	}
	//}

	// 앉기 시
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		player.State = P_SITDOWN;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		player.State = P_STAND;
	}

	// 공격 시
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		player.State = P_ATTACK;
		SOUNDMANAGER->play("플레이어_타격", 100);
	}
	if (KEYMANAGER->isOnceKeyUp('X'))
	{
		player.State = P_STAND;
		player.AttackRc = RectMakeCenter(0, 0, 0, 0);
	}

	// 점프 시
	if (KEYMANAGER->isOnceKeyDown('Z') && !player.JumpCount)
	{
		player.Jump = true;
		player.JumpCount = true;
		player.Speed = -10.5f;
		player.Gravity = 0.8f;

		SOUNDMANAGER->play("플레이어_점프", 100);

	}

	if (worldTimeCount % 15 == 0) player.JumpFrameX++;
	if (player.FrameX > IMAGEMANAGER->findImage("플레이어_점프")->getMaxFrameX()) player.JumpFrameX = 1;

	if (player.Jump)
	{
		player.State = P_JUMP;
		player.Gravity += 0.3f;
		player.Y += player.Gravity + player.Speed;
	}

	if (player.Rc.top >= 520)
	{
		//if (player.DownRc.bottom && player.DownRc.top)
		//{
			player.Jump = false;
			player.JumpCount = false;
			player.Y = 570;
			player.State = P_STAND;
			player.JumpFrameX = 0;
		//}
		if (KEYMANAGER->isOnceKeyUp('Z'))
		{
			player.State = P_STAND;
		}
	}

	//if (player.Rc.bottom && player.Rc.top)
	//{			
		RECT temp;
		if (IntersectRect(&temp, &player.Rc, &Wall[2]))
		{
			//player.Y -= player.Speed - player.Gravity;
			player.Speed = -1.1f;
			player.Gravity = 0.0f;
			player.Jump = false;
		}

		// else player.Jump = true;


		if (IntersectRect(&temp, &player.Rc, &Wall[5]))
		{
			//player.Y -= player.Speed - player.Gravity;
			player.Speed = -1.1f;
			player.Gravity = 0.0f;
			player.Jump = false;
		}

		if (IntersectRect(&temp, &player.Rc, &Wall[9]))
		{
			//player.Y -= player.Speed - player.Gravity;
			player.Speed = -1.1f;
			player.Gravity = 0.0f;
			player.Jump = false;
		}

	//}


#pragma endregion

#pragma region 플레이어 이동 시 인덱스 업데이트

	// 인덱스 업데이트
	if (worldTimeCount % 15 == 0)
	{
		if (player.State == P_WALK)
		{
			player.FrameX++;
			if (player.FrameX > IMAGEMANAGER->findImage("플레이어_걷기")->getMaxFrameX()) player.FrameX = 0;
		}
		else if (player.State == P_ATTACK)
		{
			player.FrameX++;
			if (player.FrameX > IMAGEMANAGER->findImage("플레이어_공격")->getMaxFrameX()) player.FrameX = 0;
		}
		else if (player.State == P_JUMP)
		{
			player.FrameX++;
			if (player.FrameX > IMAGEMANAGER->findImage("플레이어_점프")->getMaxFrameX()) player.FrameX = 0;
		}
		else if (player.State == P_SITDOWN)
		{
			player.FrameX++;
			if (player.FrameX > IMAGEMANAGER->findImage("플레이어_앉기")->getMaxFrameX()) player.FrameX = 0;
		}
		else
		{
			player.FrameX = 0;
		}
	}

	//if (!playerMomemt.P_Die)
	//{
	//	// 왼쪽 
	//	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	//	{
	//		playerState = P_WALK;
	//		playerFrameY = 0;
	//		// 배경제한
	//		/*if (playerX < WINSIZE_X / 2)
	//		{
	//			if (enemyMoment.E_Die && enemyMoment.BV_Die && bgMove1 != 890.0f)
	//			{
	//				zombieRC.left += 2;
	//				zombieRC.right += 2;
	//				vomitBossRC.left += 2;
	//				vomitBossRC.right += 2;
	//			}
	//			bgMove1 += 2.0f;
	//		}
	//		else
	//		{
	//			playerX -= 2;
	//			playerAttackX -= 2;
	//		}
	//		if (bgMove1 > 890) bgMove1 = 890.0f;
	//		if (bgMove1 == 890.0f)
	//		{
	//			playerX -= 2;
	//			playerAttackX -= 2;
	//		}*/
	//		
	//		if (worldTimeCount % 15 == 0) playerFrameX++;
	//		if (playerFrameX > IMAGEMANAGER->findImage("플레이어_걷기")->getMaxFrameX()) playerFrameX = 0;
	//	}
	//	// 오른쪽
	//	if (KEYMANAGER->isStayKeyDown('D') && !KEYMANAGER->isOnceKeyDown(VK_LEFT) && !playerRC.left >= 0)
	//	{
	//		playerState = P_WALK;
	//		playerFrameY = 1;
	//		if (playerX > WINSIZE_X / 2)
	//		{
	//			if (enemyMoment.E_Die && enemyMoment.BV_Die && bgMove1 != 890.0f)
	//			{
	//				zombieRC.left -= 2;
	//				zombieRC.right -= 2;
	//				vomitBossRC.left -= 2;
	//				vomitBossRC.right -= 2;
	//			}
	//			bgMove1 -= 2.0f;
	//		}
	//		else
	//		{
	//			playerX += 2;
	//			playerAttackX += 2;
	//		}
	//		if (bgMove1 < 0) bgMove1 = 0.0f;
	//		if (bgMove1 == 0.0f)
	//		{
	//			playerX += 2;
	//			playerAttackX += 2;
	//		}
	//		if (worldTimeCount % 15 == 0) playerFrameX++;
	//		if (playerFrameX > IMAGEMANAGER->findImage("플레이어_걷기")->getMaxFrameX()) playerFrameX = 0;
	//	}
	//	// 공격
	//	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	//	{
	//		playerState = P_ATTACK;
	//		playerAttackRC = RectMakeCenter(playerAttackX, playerAttackY, 171, 114);
	//	}
	//	if (worldTimeCount % 30 == 0) playerAttackFrameX++;
	//	if (playerAttackFrameX > IMAGEMANAGER->findImage("플레이어_공격")->getMaxFrameX()) playerAttackFrameX = 0;
	//	
	//	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	//	{
	//		playerState = P_STAND;
	//		playerAttackFrameX = 0;
	//		playerAttackRC = RectMakeCenter(0, 0, 0, 0);
	//	}
	//	// 점프
	//	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	//	{
	//		playerState = P_JUMP;
	//		playerMomemt.P_Jump = true;
	//		playerSpeed = 10.5f;
	//		playerGravity = 0.8f;
	//	}
	//	if (KEYMANAGER->isOnceKeyUp(VK_SPACE)) playerState = P_STAND;
	//	if (worldTimeCount % 15 == 0) playerJumpFrameX++;
	//	if (playerJumpFrameX > IMAGEMANAGER->findImage("플레이어_점프")->getMaxFrameX()) playerJumpFrameX = 1;
	//	
	//	if (playerMomemt.P_Jump)
	//	{
	//		playerState = P_JUMP;
	//		playerGravity -= 0.3f;
	//		playerY -= playerSpeed + playerGravity;
	//	}
	//	
	//	if (playerRC.top >= 522)
	//	{
	//		playerState = P_STAND;
	//		playerY = 570;
	//		playerMomemt.P_Jump = false;
	//		playerJumpFrameX = 0;
	//	}
	//	
	//	// 아래
	//	if (KEYMANAGER->isOnceKeyDown('S'))	playerState = P_SITDOWN;
	//	if (worldTimeCount % 15 == 0) playerStandFrameX++;
	//	if (playerStandFrameX > IMAGEMANAGER->findImage("플레이어_앉기")->getMaxFrameX()) playerStandFrameX = 0;
	//	if (KEYMANAGER->isOnceKeyUp('S')) playerState = P_STAND;
	//}
#pragma endregion

#pragma region 플레이어 인벤토리
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		player.Inventory = true;
	}

	if (player.Inventory == true)
	{
		if (KEYMANAGER->isOnceKeyDown('1'))
		{
			player.Inven = MAGIC;
			IMAGEMANAGER->findImage("마법")->getWidth();
		}

		if (KEYMANAGER->isOnceKeyDown('2'))
		{
			player.Inven = QUEST;
			IMAGEMANAGER->findImage("퀘스트")->getWidth();
		}

		if (KEYMANAGER->isOnceKeyDown('3'))
		{
			player.Inven = CHARECTER;
			IMAGEMANAGER->findImage("캐릭터")->getWidth();
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		player.Inventory = false;
	}
#pragma endregion

	// 플레이어 충돌용 업데이트
	playerRc[0] = RectMakeCenter(player.Rc.left, (player.Rc.bottom - player.Rc.top) / 2 + player.Rc.top, 5, 5);
	playerRc[1] = RectMakeCenter((player.Rc.right - player.Rc.left) / 2 + player.Rc.left, player.Rc.top, 5, 5);
	playerRc[2] = RectMakeCenter(player.Rc.right, (player.Rc.bottom - player.Rc.top) / 2 + player.Rc.top, 5, 5);
	playerRc[3] = RectMakeCenter((player.Rc.right - player.Rc.left) / 2 + player.Rc.left, player.Rc.bottom, 5, 5);

	for (int i = 0; i < _countof(Wall); i++)
	{
		RECT rc;
		// 땅의 벽 1
		if (IntersectRect(&rc, &playerRc[0], &Wall[2]))
		{
			playerCrash[0] = true;
		}
		if (IntersectRect(&rc, &playerRc[2], &Wall[2]))
		{
			playerCrash[0] = true;
		}
		if (IntersectRect(&rc, &playerRc[3], &Wall[2]))
		{
			playerCrash[0] = true;
		}

		if (!IntersectRect(&rc, &playerRc[1], &Wall[i]))
		{
			playerCrash[0] = false;
		}

		// 위로 올라가는 계단 2
		if (IntersectRect(&rc, &playerRc[1], &Wall[3]))
		{
			playerCrash[1] = true;
		}
		if (IntersectRect(&rc, &playerRc[1], &Wall[4]))
		{
			playerCrash[1] = true;
		}
		if (IntersectRect(&rc, &playerRc[1], &Wall[5]))
		{
			playerCrash[1] = true;
		}
		if (IntersectRect(&rc, &playerRc[1], &Wall[6]))
		{
			playerCrash[1] = true;
		}

		if (!IntersectRect(&rc, &playerRc[1], &Wall[i]))
		{
			playerCrash[1] = false;
		}


		// 위로 올라가는 계단 3
		if (IntersectRect(&rc, &playerRc[2], &Wall[7]))
		{
			playerCrash[2] = true;
		}
		if (IntersectRect(&rc, &playerRc[2], &Wall[8]))
		{
			playerCrash[2] = true;
		}
		if (IntersectRect(&rc, &playerRc[2], &Wall[9]))
		{
			playerCrash[2] = true;
		}
		if (IntersectRect(&rc, &playerRc[2], &Wall[10]))
		{
			playerCrash[2] = true;
		}

		if (!IntersectRect(&rc, &playerRc[2], &Wall[i]))
		{
			playerCrash[2] = false;
		}



		// 계단 벽 난간 4
		//if (IntersectRect(&rc, &playerRc[3], &Wall[11]))
		//{
		//	playerCrash[3] = true;
		//}
		//if (IntersectRect(&rc, &playerRc[3], &Wall[12]))
		//{
		//	playerCrash[3] = true;
		//}
		// 계단 벽 난간 5
		//if (IntersectRect(&rc, &playerRc[4], &Wall[13]))
		//{
		//	playerCrash[4] = true;
		//}
		//if (IntersectRect(&rc, &playerRc[4], &Wall[14]))
		//{
		//	playerCrash[4] = true;
		//}
	}
}

void Unit::playerRender(void)
{
	//DrawRectMake(getMemDC(), player.Rc);
	//DrawRectMake(getMemDC(), player.DownRc);

#pragma region 플레이어 랜더
	if (player.State == P_STAND)
	{
		// 서있기 우측/좌측
		if (player.Right) IMAGEMANAGER->frameRender("플레이어", getMemDC(),
			player.Rc.left, player.Rc.top + 2, player.FrameX, player.Right);
		else if (!player.Right) IMAGEMANAGER->frameRender("플레이어", getMemDC(),
			player.Rc.left - 5, player.Rc.top + 2, player.FrameX, player.Right);
	}
	else if (player.State == P_WALK)
	{
		// 걷기 우측/좌측
		if (player.Right) IMAGEMANAGER->frameRender("플레이어_걷기", getMemDC(),
			player.Rc.left, player.Rc.top, player.FrameX, player.Right);
		else if (!player.Right) IMAGEMANAGER->frameRender("플레이어_걷기", getMemDC(),
			player.Rc.left - 5, player.Rc.top, player.FrameX, player.Right);
	}
	else if (player.State == P_ATTACK)
	{
		// 공격 우측/좌측
		if (!player.Right)
		{
			if (player.AttackFrameX == 1)
			{
				player.AttackRc = RectMakeCenter(player.X, player.Y, 70, 114);
			}
			if (player.AttackFrameX == 0)
			{
				player.AttackRc = RectMakeCenter(player.X, player.Y, 140, 114);
			}
			IMAGEMANAGER->frameRender("플레이어_공격", getMemDC(),
				player.Rc.left - 88, player.Rc.top - 13, player.FrameX, player.Right);
		}
		else if (player.Right)
		{
			if (player.AttackFrameX == 1)
			{
				player.AttackRc = RectMakeCenter(player.X, player.Y, 70, 114);
			}
			if (player.AttackFrameX == 0)
			{
				player.AttackRc = RectMakeCenter(player.X, player.Y, 140, 114);
			}
			IMAGEMANAGER->frameRender("플레이어_공격", getMemDC(),
				player.Rc.left - 76, player.Rc.top - 13, player.FrameX, player.Right);
		}
	}
	else if (player.State == P_JUMP)
	{
		if (player.Right) IMAGEMANAGER->frameRender("플레이어_점프", getMemDC(),
			player.Rc.left - 5, player.Rc.top - 12, player.JumpFrameX, player.Right);
		else if (!player.Right) IMAGEMANAGER->frameRender("플레이어_점프", getMemDC(),
			player.Rc.left - 10, player.Rc.top - 12, player.JumpFrameX, player.Right);
	}

	else if (player.State == P_SITDOWN)
	{
		if (player.Right) IMAGEMANAGER->frameRender("플레이어_앉기", getMemDC(),
			player.Rc.left + 2, player.Rc.top + 35, player.FrameX, player.Right);
		else if (!player.Right) IMAGEMANAGER->frameRender("플레이어_앉기", getMemDC(),
			player.Rc.left - 4, player.Rc.top + 35, player.FrameX, player.Right);
	}

	//if (playerState == P_WALK)
	//{
	//	if (playerFrameY == 1) IMAGEMANAGER->frameRender("플레이어_걷기", getMemDC(), playerRC.left, playerRC.top, playerFrameX, playerFrameY);
	//	else if (playerFrameY == 0) IMAGEMANAGER->frameRender("플레이어_걷기", getMemDC(), playerRC.left - 5, playerRC.top, playerFrameX, playerFrameY);
	//}
	//if (playerState == P_STAND)
	//{
	//	if (playerFrameY == 1) IMAGEMANAGER->frameRender("플레이어", getMemDC(), playerRC.left, playerRC.top + 3, playerStandFrameX, playerFrameY);
	//	else if (playerFrameY == 0) IMAGEMANAGER->frameRender("플레이어", getMemDC(), playerRC.left - 7, playerRC.top + 3, playerStandFrameX, playerFrameY);
	//}
	//if (playerState == P_JUMP)
	//{
	//	if (playerFrameY == 1) IMAGEMANAGER->frameRender("플레이어_점프", getMemDC(), playerRC.left, playerRC.top, playerJumpFrameX, playerFrameY);
	//	else if (playerFrameY == 0) IMAGEMANAGER->frameRender("플레이어_점프", getMemDC(), playerRC.left, playerRC.top, playerJumpFrameX, playerFrameY);
	//}
	//if (playerState == P_ATTACK)
	//{
	//	// Y = 1 오른쪽
	//	if (playerFrameY == 1)
	//	{
	//		if (playerAttackFrameX == 1)
	//		{
	//			playerAttackX = player.X;
	//			playerAttackY = player.Y - 5;
	//			playerAttackRC = RectMakeCenter(playerAttackX, playerAttackY, 70, 114);
	//		}
	//		if (playerAttackFrameX == 0)
	//		{
	//			playerAttackX = player.X + 48;
	//			playerAttackY = player.Y - 5;
	//			playerAttackRC = RectMakeCenter(playerAttackX, playerAttackY, 140, 114);
	//			zombieFrameY = 2;
	//			if (!enemyMoment.E_Die) IMAGEMANAGER->findImage("좀비_걷기")->frameRender(getMemDC(), zombieRC.left, zombieRC.top - 8, zombieFrameX, zombieFrameY);
	//		}
	//		IMAGEMANAGER->frameRender("플레이어_공격", getMemDC(), player.Rc.left - 77, player.Rc.top - 12, playerAttackFrameX, playerFrameY);
	//	}
	//	// Y = 0 왼쪽
	//	if (playerFrameY == 0)
	//	{
	//		if (playerAttackFrameX == 1)
	//		{
	//			playerAttackX = player.X;
	//			playerAttackY = player.Y - 5;
	//			playerAttackRC = RectMakeCenter(playerAttackX, playerAttackY, 70, 114);
	//		}
	//		if (playerAttackFrameX == 0)
	//		{
	//			playerAttackX = player.X - 50;
	//			playerAttackY = player.Y - 5;
	//			playerAttackRC = RectMakeCenter(playerAttackX, playerAttackY, 140, 114);
	//			zombieFrameY = 3;
	//			if (!enemyMoment.E_Die) IMAGEMANAGER->findImage("좀비_걷기")->frameRender(getMemDC(), zombieRC.left, zombieRC.top - 8, zombieFrameX, zombieFrameY);
	//		}
	//		IMAGEMANAGER->frameRender("플레이어_공격", getMemDC(), player.Rc.left - 87, player.Rc.top - 12, playerAttackFrameX, playerFrameY);
	//	}
	//}	
	//if (playerState == P_SITDOWN)
	//{
	//	if (player.FrameY == 1) IMAGEMANAGER->frameRender("플레이어_앉기", getMemDC(), player.Rc.left + 1, player.Rc.top + 36, player.FrameX, player.FrameY);
	//	else if (player.FrameY == 0) IMAGEMANAGER->frameRender("플레이어_앉기", getMemDC(), player.Rc.left - 6, player.Rc.top + 35, player.FrameX, player.FrameY);
	//}
#pragma endregion

#pragma region 인벤토리 랜더

	if (player.Inventory)
	{
		if (player.Inven == MAGIC) IMAGEMANAGER->findImage("마법")->render(getMemDC(), 0, 0);
		if (player.Inven == QUEST) IMAGEMANAGER->findImage("퀘스트")->render(getMemDC(), 0, 0);
		if (player.Inven == CHARECTER) IMAGEMANAGER->findImage("캐릭터")->render(getMemDC(), 0, 0);
	}
#pragma endregion
	for (int i = 0; i < _countof(playerRc); i++)
		DrawRectMake(getMemDC(), playerRc[i]);
}