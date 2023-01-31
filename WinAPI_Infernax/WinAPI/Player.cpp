#include "Stdafx.h"
#include "Unit.h"

void Unit::playerInit(void)
{
#pragma region 플레이어 변수 초기화
	player.X = 900;
	player.Y = 570;

	player.FrameX = player.FrameY = player.JumpFrameX = 0;

	player.State = P_STAND;

	player.P_Die = false;
	player.P_Jump = false;
	player.P_JumpCount = false;

	player.Speed = player.Gravity = 0.0f;
#pragma endregion

	// 장 변경 시 알파 값 초기화
	alpha = 0;
}

void Unit::playerUpdate(void)
{
#pragma region 키 입력 시 플레이어 이동
	// 왼쪽으로 걷기 시
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		player.X -= 2;
		player.State = P_WALK;
		player.Right = false;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		player.State = P_STAND;
	}

	// 오른쪽으로 걷기 시
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		player.X += 2;
		player.State = P_WALK;
		player.Right = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		player.State = P_STAND;
	}

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
	if (KEYMANAGER->isStayKeyDown('X'))
	{
		player.State = P_ATTACK;
	}
	if (KEYMANAGER->isOnceKeyUp('X'))
	{
		player.State = P_STAND;
	}

	// 점프 시
	if (KEYMANAGER->isOnceKeyDown('Z') && !player.P_JumpCount)
	{
		player.P_Jump = true;
		player.P_JumpCount = true;
		player.Speed = 10.5f;
		player.Gravity = 0.8f;
	}
	if (worldTimeCount % 15 == 0) player.JumpFrameX++;
	if (player.FrameX > IMAGEMANAGER->findImage("플레이어_점프")->getMaxFrameX()) player.JumpFrameX = 1;
	
	if (player.P_Jump)
	{
		player.State = P_JUMP;
		player.Gravity -= 0.3f;
		player.Y -= player.Speed + player.Gravity;
	}

	if (playerRC.top >= 522)
	{
		player.P_Jump = false;
		player.P_JumpCount = false;
		player.Y = 570;
		player.State = P_STAND;
		player.JumpFrameX = 0;

		if (KEYMANAGER->isOnceKeyUp('Z'))
		{
			player.State = P_STAND;
		}
	}


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
#pragma endregion

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


#pragma region 적과의 충돌
	//RECT temp;
	//if (playerFrameY == 0)
	//{
	//	if (IntersectRect(&temp, &playerAttackRC, &zombieRC))
	//	{
	//		if (temp.right - temp.left > 50)
	//		{
	//			zombieRC.left -= 100;
	//			zombieRC.right -= 100;

	//			if (enemyMoment.E_Hp < 3) enemyMoment.E_Hp++;
	//		}
	//	}
	//}
	//else if (playerFrameY == 1)
	//{
	//	if (IntersectRect(&temp, &playerAttackRC, &zombieRC))
	//	{
	//		if (temp.right - temp.left > 50)
	//		{
	//			zombieRC.left += 100;
	//			zombieRC.right += 100;
	//		}
	//	}
	//}
#pragma endregion

	playerRC = RectMakeCenter(player.X, player.Y, 69, 103);
}

void Unit::playerRender(void)
{
	//DrawRectMake(getMemDC(), playerRC);
	//DrawRectMake(getMemDC(), playerAttackRC);

#pragma region 플레이어 랜더
	if (player.State == P_STAND)
	{
		// 서있기 우측/좌측
		if (player.Right) IMAGEMANAGER->frameRender("플레이어", getMemDC(),
			playerRC.left, playerRC.top + 2, player.FrameX, player.Right);
		else if (!player.Right) IMAGEMANAGER->frameRender("플레이어", getMemDC(),
			playerRC.left - 5, playerRC.top + 2, player.FrameX, player.Right);
	}
	else if (player.State == P_WALK)
	{
		// 걷기 우측/좌측
		if (player.Right) IMAGEMANAGER->frameRender("플레이어_걷기", getMemDC(),
			playerRC.left, playerRC.top, player.FrameX, player.Right);
		else if (!player.Right) IMAGEMANAGER->frameRender("플레이어_걷기", getMemDC(),
			playerRC.left - 5, playerRC.top, player.FrameX, player.Right);
	}
	else if (player.State == P_ATTACK)
	{
		// 공격 우측/좌측
		if (player.Right) IMAGEMANAGER->frameRender("플레이어_공격", getMemDC(),
			playerRC.left - 80, playerRC.top - 12, player.FrameX, player.Right);
		else if (!player.Right) IMAGEMANAGER->frameRender("플레이어_공격", getMemDC(),
			playerRC.left - 89, playerRC.top - 12, player.FrameX, player.Right);
	}
	else if (player.State == P_JUMP)
	{
		if (player.Right) IMAGEMANAGER->frameRender("플레이어_점프", getMemDC(),
			playerRC.left - 5, playerRC.top - 12, player.JumpFrameX, player.Right);
		else if (!player.Right) IMAGEMANAGER->frameRender("플레이어_점프", getMemDC(),
			playerRC.left - 10, playerRC.top - 12, player.JumpFrameX, player.Right);
	}

	else if (player.State == P_SITDOWN)
	{
		if (player.Right) IMAGEMANAGER->frameRender("플레이어_앉기", getMemDC(),
			playerRC.left + 2, playerRC.top + 35, player.FrameX, player.Right);
		else if (!player.Right) IMAGEMANAGER->frameRender("플레이어_앉기", getMemDC(),
			playerRC.left - 4, playerRC.top + 35, player.FrameX, player.Right);
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
	//			playerAttackX = playerX;
	//			playerAttackY = playerY - 5;
	//			playerAttackRC = RectMakeCenter(playerAttackX, playerAttackY, 70, 114);
	//		}
	//		if (playerAttackFrameX == 0)
	//		{
	//			playerAttackX = playerX + 48;
	//			playerAttackY = playerY - 5;
	//			playerAttackRC = RectMakeCenter(playerAttackX, playerAttackY, 140, 114);
	//			zombieFrameY = 2;
	//			if (!enemyMoment.E_Die) IMAGEMANAGER->findImage("좀비_걷기")->frameRender(getMemDC(), zombieRC.left, zombieRC.top - 8, zombieFrameX, zombieFrameY);
	//		}
	//		IMAGEMANAGER->frameRender("플레이어_공격", getMemDC(), playerRC.left - 77, playerRC.top - 12, playerAttackFrameX, playerFrameY);
	//	}
		// Y = 0 왼쪽
		/*if (playerFrameY == 0)
		{
			if (playerAttackFrameX == 1)
			{
				playerAttackX = playerX;
				playerAttackY = playerY - 5;
				playerAttackRC = RectMakeCenter(playerAttackX, playerAttackY, 70, 114);
			}
			if (playerAttackFrameX == 0)
			{
				playerAttackX = playerX - 50;
				playerAttackY = playerY - 5;
				playerAttackRC = RectMakeCenter(playerAttackX, playerAttackY, 140, 114);
				zombieFrameY = 3;
				if (!enemyMoment.E_Die) IMAGEMANAGER->findImage("좀비_걷기")->frameRender(getMemDC(), zombieRC.left, zombieRC.top - 8, zombieFrameX, zombieFrameY);
			}
			IMAGEMANAGER->frameRender("플레이어_공격", getMemDC(), playerRC.left - 87, playerRC.top - 12, playerAttackFrameX, playerFrameY);
		}
	}
	if (playerState == P_SITDOWN)
	{
		if (playerFrameY == 1) IMAGEMANAGER->frameRender("플레이어_앉기", getMemDC(), playerRC.left + 1, playerRC.top + 36, playerFrameX, playerFrameY);
		else if (playerFrameY == 0) IMAGEMANAGER->frameRender("플레이어_앉기", getMemDC(), playerRC.left - 6, playerRC.top + 35, playerFrameX, playerFrameY);
	}*/
#pragma endregion
}