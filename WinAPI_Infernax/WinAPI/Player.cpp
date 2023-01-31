#include "Stdafx.h"
#include "Unit.h"

void Unit::playerInit(void)
{
#pragma region 변수 초기화
	playerX = 900;
	playerY = 570;

	playerAttackX = 951;
	playerAttackY = 578;

	playerRC = RectMakeCenter(playerX, playerY, 69, 103);
	playerAttackRC = RectMakeCenter(0, 0, 0, 0);

	playerFrameX = playerFrameY = playerAttackFrameX = playerJumpFrameX = playerSitDownFrameX = playerStandFrameX = 0;

	// 플레이어 움직임
	playerState = P_WALK;

	playerMomemt.P_Die = false;
	playerMomemt.P_Jump = false;

	alpha = 0;

	playerSpeed = playerGravity = 0.0f;
#pragma endregion
}

void Unit::playerUpdate(void)
{
#pragma region 플레이어 이동 & 프레임

	if (!playerMomemt.P_Die)
	{
		// 왼쪽 
		if (KEYMANAGER->isStayKeyDown('A') && !KEYMANAGER->isOnceKeyDown(VK_LEFT) && !playerRC.left <= 0)
		{
			playerState = P_WALK;
			playerFrameY = 0;

			// 배경제한
			if (playerX < WINSIZE_X / 2)
			{
				if (enemyMoment.E_Die && enemyMoment.BV_Die && bgMove != 890.0f)
				{
					zombieRC.left += 2;
					zombieRC.right += 2;

					vomitBossRC.left += 2;
					vomitBossRC.right += 2;
				}
				bgMove += 2.0f;
			}
			else
			{
				playerX -= 2;
				playerAttackX -= 2;
			}
			if (bgMove > 890) bgMove = 890.0f;
			if (bgMove == 890.0f)
			{
				playerX -= 2;
				playerAttackX -= 2;
			}
			
			if (worldTimeCount % 15 == 0) playerFrameX++;
			if (playerFrameX > IMAGEMANAGER->findImage("플레이어_걷기")->getMaxFrameX()) playerFrameX = 0;
		}

		// 오른쪽
		if (KEYMANAGER->isStayKeyDown('D') && !KEYMANAGER->isOnceKeyDown(VK_LEFT) && !playerRC.left >= 0)
		{
			playerState = P_WALK;
			playerFrameY = 1;

			if (playerX > WINSIZE_X / 2)
			{
				if (enemyMoment.E_Die && enemyMoment.BV_Die && bgMove != 890.0f)
				{
					zombieRC.left -= 2;
					zombieRC.right -= 2;

					vomitBossRC.left -= 2;
					vomitBossRC.right -= 2;
				}
				bgMove -= 2.0f;
			}
			else
			{
				playerX += 2;
				playerAttackX += 2;
			}

			if (bgMove < 0) bgMove = 0.0f;
			if (bgMove == 0.0f)
			{
				playerX += 2;
				playerAttackX += 2;
			}

			if (worldTimeCount % 15 == 0) playerFrameX++;
			if (playerFrameX > IMAGEMANAGER->findImage("플레이어_걷기")->getMaxFrameX()) playerFrameX = 0;
		}

		// 공격
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			playerState = P_ATTACK;
			playerAttackRC = RectMakeCenter(playerAttackX, playerAttackY, 171, 114);
		}
		if (worldTimeCount % 30 == 0) playerAttackFrameX++;
		if (playerAttackFrameX > IMAGEMANAGER->findImage("플레이어_공격")->getMaxFrameX()) playerAttackFrameX = 0;
		
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			playerState = P_STAND;
			playerAttackFrameX = 0;
			playerAttackRC = RectMakeCenter(0, 0, 0, 0);
		}

		// 점프
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			playerState = P_JUMP;
			playerMomemt.P_Jump = true;
			playerSpeed = 10.5f;
			playerGravity = 0.8f;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_SPACE)) playerState = P_STAND;
		if (worldTimeCount % 15 == 0) playerJumpFrameX++;
		if (playerJumpFrameX > IMAGEMANAGER->findImage("플레이어_점프")->getMaxFrameX()) playerJumpFrameX = 1;
		
		if (playerMomemt.P_Jump)
		{
			playerState = P_JUMP;
			playerGravity -= 0.3f;
			playerY -= playerSpeed + playerGravity;
		}
		
		if (playerRC.top >= 522)
		{
			playerState = P_STAND;
			playerY = 570;
			playerMomemt.P_Jump = false;
			playerJumpFrameX = 0;
		}
		
		// 아래
		if (KEYMANAGER->isOnceKeyDown('S'))	playerState = P_SITDOWN;

		if (worldTimeCount % 15 == 0) playerStandFrameX++;
		if (playerStandFrameX > IMAGEMANAGER->findImage("플레이어_앉기")->getMaxFrameX()) playerStandFrameX = 0;

		if (KEYMANAGER->isOnceKeyUp('S')) playerState = P_STAND;
	}

	if (playerRC.left <= 0)
	{
		alpha++;
		if (alpha > 255)
		{
			SCENEMANAGER->changeScene("배틀맵2");
		}
	}

#pragma endregion

#pragma region 적과의 충돌
	RECT temp;
	if (playerFrameY == 0)
	{
		if (IntersectRect(&temp, &playerAttackRC, &zombieRC))
		{
			if (temp.right - temp.left > 50)
			{
				zombieRC.left -= 100;
				zombieRC.right -= 100;

				if (enemyMoment.E_Hp < 3) enemyMoment.E_Hp++;
			}
		}
	}
	else if (playerFrameY == 1)
	{
		if (IntersectRect(&temp, &playerAttackRC, &zombieRC))
		{
			if (temp.right - temp.left > 50)
			{
				zombieRC.left += 100;
				zombieRC.right += 100;
			}
		}
	}
#pragma endregion

	playerRC = RectMakeCenter(playerX, playerY, 69, 103);
}

void Unit::playerRender(void)
{
	DrawRectMake(getMemDC(), playerRC);
	DrawRectMake(getMemDC(), playerAttackRC);

#pragma region 플레이어 랜더
	if (playerState == P_WALK)
	{
		if (playerFrameY == 1) IMAGEMANAGER->frameRender("플레이어_걷기", getMemDC(), playerRC.left, playerRC.top, playerFrameX, playerFrameY);
		else if (playerFrameY == 0) IMAGEMANAGER->frameRender("플레이어_걷기", getMemDC(), playerRC.left - 5, playerRC.top, playerFrameX, playerFrameY);

	}
	if (playerState == P_STAND)
	{
		if (playerFrameY == 1) IMAGEMANAGER->frameRender("플레이어", getMemDC(), playerRC.left, playerRC.top + 3, playerStandFrameX, playerFrameY);
		else if (playerFrameY == 0) IMAGEMANAGER->frameRender("플레이어", getMemDC(), playerRC.left - 7, playerRC.top + 3, playerStandFrameX, playerFrameY);
	}

	if (playerState == P_JUMP)
	{
		if (playerFrameY == 1) IMAGEMANAGER->frameRender("플레이어_점프", getMemDC(), playerRC.left, playerRC.top, playerJumpFrameX, playerFrameY);
		else if (playerFrameY == 0) IMAGEMANAGER->frameRender("플레이어_점프", getMemDC(), playerRC.left, playerRC.top, playerJumpFrameX, playerFrameY);
	}

	if (playerState == P_ATTACK)
	{
		// Y = 1 오른쪽
		if (playerFrameY == 1)
		{
			if (playerAttackFrameX == 1)
			{
				playerAttackX = playerX;
				playerAttackY = playerY - 5;
				playerAttackRC = RectMakeCenter(playerAttackX, playerAttackY, 70, 114);
			}
			if (playerAttackFrameX == 0)
			{
				playerAttackX = playerX + 48;
				playerAttackY = playerY - 5;
				playerAttackRC = RectMakeCenter(playerAttackX, playerAttackY, 140, 114);

				zombieFrameY = 2;
				if (!enemyMoment.E_Die) IMAGEMANAGER->findImage("좀비_걷기")->frameRender(getMemDC(), zombieRC.left, zombieRC.top - 8, zombieFrameX, zombieFrameY);

			}

			IMAGEMANAGER->frameRender("플레이어_공격", getMemDC(), playerRC.left - 77, playerRC.top - 12, playerAttackFrameX, playerFrameY);
		}

		// Y = 0 왼쪽
		if (playerFrameY == 0)
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
	}
#pragma endregion

	IMAGEMANAGER->findImage("알파블랙")->alphaRender(getMemDC(), 0, 0, alpha);
}