#include "Stdafx.h"
#include "Unit.h"

void Unit::playerInit(void)
{
#pragma region �÷��̾� ���� �ʱ�ȭ
	player.X = 900;
	player.Y = 570;

	player.FrameX = player.FrameY = player.JumpFrameX = 0;
	villageMove = false;

	player.State = P_STAND;
	player.Inven = MAGIC;

	player.Die = player.Jump = player.JumpCount = player.Inventory = player.Move =  false;

	player.Speed = player.Gravity = 0.0f;
#pragma endregion
}

void Unit::playerUpdate(void)
{
#pragma region Ű �Է� �� �÷��̾� �̵�

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
		// �������� �ȱ� ��
		//if (player.Move)
		//{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			player.X -= 2;
			player.State = P_WALK;
			player.Right = false;
		}
		//}

		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			player.State = P_STAND;
		}

		//if (!player.Move)
		//{
		// ���������� �ȱ� ��
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			player.X += 2;
			player.State = P_WALK;
			player.Right = true;
		}
		//}

		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			player.State = P_STAND;
		}
	}

	if (villageMove)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			if (WINSIZE_X / 2 < player.X)
			{
				player.X -= 2;
				player.State = P_WALK;
				player.Right = false;
				bgMove += 2.0f;
			}
			else
			{
				player.State = P_WALK;
				player.Right = false;
				bgMove += 2.0f;
			}
		}

		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			player.State = P_STAND;
		}


		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			if (WINSIZE_X / 2 > player.X)
			{
				player.X += 2;
				player.State = P_WALK;
				player.Right = true;
				bgMove -= 2.0f;
			}

			else
			{
				player.State = P_WALK;
				player.Right = true;
				bgMove -= 2.0f;
			}
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

		if (bgMove < 200 && KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			bgMove = 200;
			player.X += 2;
		}
	}

	cout << villageMove << endl;
	// �ɱ� ��
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		player.State = P_SITDOWN;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		player.State = P_STAND;
	}

	// ���� ��
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		player.State = P_ATTACK;
	}
	if (KEYMANAGER->isOnceKeyUp('X'))
	{
		player.State = P_STAND;
		player.AttackRc = RectMakeCenter(0, 0, 0, 0);
	}

	// ���� ��
	if (KEYMANAGER->isOnceKeyDown('Z') && !player.JumpCount)
	{
		player.Jump = true;
		player.JumpCount = true;
		player.Speed = 10.5f;
		player.Gravity = 0.8f;
	}

	if (worldTimeCount % 15 == 0) player.JumpFrameX++;
	if (player.FrameX > IMAGEMANAGER->findImage("�÷��̾�_����")->getMaxFrameX()) player.JumpFrameX = 1;
	
	if (player.Jump)
	{
		player.State = P_JUMP;
		player.Gravity -= 0.3f;
		player.Y -= player.Speed + player.Gravity;
	}

	if (player.Rc.top >= 522)
	{
		player.Jump = false;
		player.JumpCount = false;
		player.Y = 570;
		player.State = P_STAND;
		player.JumpFrameX = 0;

		if (KEYMANAGER->isOnceKeyUp('Z'))
		{
			player.State = P_STAND;
		}
	}
#pragma endregion

#pragma region �÷��̾� �̵� �� �ε��� ������Ʈ

	// �ε��� ������Ʈ
	if (worldTimeCount % 15 == 0)
	{
		if (player.State == P_WALK)
		{
			player.FrameX++;
			if (player.FrameX > IMAGEMANAGER->findImage("�÷��̾�_�ȱ�")->getMaxFrameX()) player.FrameX = 0;
		}
		else if (player.State == P_ATTACK)
		{
			player.FrameX++;
			if (player.FrameX > IMAGEMANAGER->findImage("�÷��̾�_����")->getMaxFrameX()) player.FrameX = 0;
		}
		else if (player.State == P_JUMP)
		{
			player.FrameX++;
			if (player.FrameX > IMAGEMANAGER->findImage("�÷��̾�_����")->getMaxFrameX()) player.FrameX = 0;
		}
		else if (player.State == P_SITDOWN)
		{
			player.FrameX++;
			if (player.FrameX > IMAGEMANAGER->findImage("�÷��̾�_�ɱ�")->getMaxFrameX()) player.FrameX = 0;
		}
		else
		{
			player.FrameX = 0;
		}
	}

	//if (!playerMomemt.P_Die)
	//{
	//	// ���� 
	//	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	//	{
	//		playerState = P_WALK;
	//		playerFrameY = 0;
	//		// �������
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
	//		if (playerFrameX > IMAGEMANAGER->findImage("�÷��̾�_�ȱ�")->getMaxFrameX()) playerFrameX = 0;
	//	}
	//	// ������
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
	//		if (playerFrameX > IMAGEMANAGER->findImage("�÷��̾�_�ȱ�")->getMaxFrameX()) playerFrameX = 0;
	//	}
	//	// ����
	//	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	//	{
	//		playerState = P_ATTACK;
	//		playerAttackRC = RectMakeCenter(playerAttackX, playerAttackY, 171, 114);
	//	}
	//	if (worldTimeCount % 30 == 0) playerAttackFrameX++;
	//	if (playerAttackFrameX > IMAGEMANAGER->findImage("�÷��̾�_����")->getMaxFrameX()) playerAttackFrameX = 0;
	//	
	//	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	//	{
	//		playerState = P_STAND;
	//		playerAttackFrameX = 0;
	//		playerAttackRC = RectMakeCenter(0, 0, 0, 0);
	//	}
	//	// ����
	//	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	//	{
	//		playerState = P_JUMP;
	//		playerMomemt.P_Jump = true;
	//		playerSpeed = 10.5f;
	//		playerGravity = 0.8f;
	//	}
	//	if (KEYMANAGER->isOnceKeyUp(VK_SPACE)) playerState = P_STAND;
	//	if (worldTimeCount % 15 == 0) playerJumpFrameX++;
	//	if (playerJumpFrameX > IMAGEMANAGER->findImage("�÷��̾�_����")->getMaxFrameX()) playerJumpFrameX = 1;
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
	//	// �Ʒ�
	//	if (KEYMANAGER->isOnceKeyDown('S'))	playerState = P_SITDOWN;
	//	if (worldTimeCount % 15 == 0) playerStandFrameX++;
	//	if (playerStandFrameX > IMAGEMANAGER->findImage("�÷��̾�_�ɱ�")->getMaxFrameX()) playerStandFrameX = 0;
	//	if (KEYMANAGER->isOnceKeyUp('S')) playerState = P_STAND;
	//}
#pragma endregion

#pragma region �÷��̾� �κ��丮
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		player.Inventory = true;
	}

	if (player.Inventory == true)
	{
		if (KEYMANAGER->isOnceKeyDown('1'))
		{
			player.Inven = MAGIC;
			IMAGEMANAGER->findImage("����")->getWidth();
		}

		if (KEYMANAGER->isOnceKeyDown('2'))
		{
			player.Inven = QUEST;
			IMAGEMANAGER->findImage("����Ʈ")->getWidth();
		}

		if (KEYMANAGER->isOnceKeyDown('3'))
		{
			player.Inven = CHARECTER;
			IMAGEMANAGER->findImage("ĳ����")->getWidth();
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		player.Inventory = false;
	}
#pragma endregion

	player.Rc = RectMakeCenter(player.X, player.Y, 69, 103);
}

void Unit::playerRender(void)
{
	//DrawRectMake(getMemDC(), player.AttackRc);
	//DrawRectMake(getMemDC(), player.Rc);

#pragma region �÷��̾� ����
	if (player.State == P_STAND)
	{
		// ���ֱ� ����/����
		if (player.Right) IMAGEMANAGER->frameRender("�÷��̾�", getMemDC(),
			player.Rc.left, player.Rc.top + 2, player.FrameX, player.Right);
		else if (!player.Right) IMAGEMANAGER->frameRender("�÷��̾�", getMemDC(),
			player.Rc.left - 5, player.Rc.top + 2, player.FrameX, player.Right);
	}
	else if (player.State == P_WALK)
	{
		// �ȱ� ����/����
		if (player.Right) IMAGEMANAGER->frameRender("�÷��̾�_�ȱ�", getMemDC(),
			player.Rc.left, player.Rc.top, player.FrameX, player.Right);
		else if (!player.Right) IMAGEMANAGER->frameRender("�÷��̾�_�ȱ�", getMemDC(),
			player.Rc.left - 5, player.Rc.top, player.FrameX, player.Right);
	}
	else if (player.State == P_ATTACK)
	{
		// ���� ����/����
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
			IMAGEMANAGER->frameRender("�÷��̾�_����", getMemDC(),
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
			IMAGEMANAGER->frameRender("�÷��̾�_����", getMemDC(),
				player.Rc.left - 76, player.Rc.top - 13, player.FrameX, player.Right);
		}
	}
	else if (player.State == P_JUMP)
	{
		if (player.Right) IMAGEMANAGER->frameRender("�÷��̾�_����", getMemDC(),
			player.Rc.left - 5, player.Rc.top - 12, player.JumpFrameX, player.Right);
		else if (!player.Right) IMAGEMANAGER->frameRender("�÷��̾�_����", getMemDC(),
			player.Rc.left - 10, player.Rc.top - 12, player.JumpFrameX, player.Right);
	}

	else if (player.State == P_SITDOWN)
	{
		if (player.Right) IMAGEMANAGER->frameRender("�÷��̾�_�ɱ�", getMemDC(),
			player.Rc.left + 2, player.Rc.top + 35, player.FrameX, player.Right);
		else if (!player.Right) IMAGEMANAGER->frameRender("�÷��̾�_�ɱ�", getMemDC(),
			player.Rc.left - 4, player.Rc.top + 35, player.FrameX, player.Right);
	}

	//if (playerState == P_WALK)
	//{
	//	if (playerFrameY == 1) IMAGEMANAGER->frameRender("�÷��̾�_�ȱ�", getMemDC(), playerRC.left, playerRC.top, playerFrameX, playerFrameY);
	//	else if (playerFrameY == 0) IMAGEMANAGER->frameRender("�÷��̾�_�ȱ�", getMemDC(), playerRC.left - 5, playerRC.top, playerFrameX, playerFrameY);
	//}
	//if (playerState == P_STAND)
	//{
	//	if (playerFrameY == 1) IMAGEMANAGER->frameRender("�÷��̾�", getMemDC(), playerRC.left, playerRC.top + 3, playerStandFrameX, playerFrameY);
	//	else if (playerFrameY == 0) IMAGEMANAGER->frameRender("�÷��̾�", getMemDC(), playerRC.left - 7, playerRC.top + 3, playerStandFrameX, playerFrameY);
	//}
	//if (playerState == P_JUMP)
	//{
	//	if (playerFrameY == 1) IMAGEMANAGER->frameRender("�÷��̾�_����", getMemDC(), playerRC.left, playerRC.top, playerJumpFrameX, playerFrameY);
	//	else if (playerFrameY == 0) IMAGEMANAGER->frameRender("�÷��̾�_����", getMemDC(), playerRC.left, playerRC.top, playerJumpFrameX, playerFrameY);
	//}
	//if (playerState == P_ATTACK)
	//{
	//	// Y = 1 ������
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
	//			if (!enemyMoment.E_Die) IMAGEMANAGER->findImage("����_�ȱ�")->frameRender(getMemDC(), zombieRC.left, zombieRC.top - 8, zombieFrameX, zombieFrameY);
	//		}
	//		IMAGEMANAGER->frameRender("�÷��̾�_����", getMemDC(), player.Rc.left - 77, player.Rc.top - 12, playerAttackFrameX, playerFrameY);
	//	}
	//	// Y = 0 ����
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
	//			if (!enemyMoment.E_Die) IMAGEMANAGER->findImage("����_�ȱ�")->frameRender(getMemDC(), zombieRC.left, zombieRC.top - 8, zombieFrameX, zombieFrameY);
	//		}
	//		IMAGEMANAGER->frameRender("�÷��̾�_����", getMemDC(), player.Rc.left - 87, player.Rc.top - 12, playerAttackFrameX, playerFrameY);
	//	}
	//}	
	//if (playerState == P_SITDOWN)
	//{
	//	if (player.FrameY == 1) IMAGEMANAGER->frameRender("�÷��̾�_�ɱ�", getMemDC(), player.Rc.left + 1, player.Rc.top + 36, player.FrameX, player.FrameY);
	//	else if (player.FrameY == 0) IMAGEMANAGER->frameRender("�÷��̾�_�ɱ�", getMemDC(), player.Rc.left - 6, player.Rc.top + 35, player.FrameX, player.FrameY);
	//}
#pragma endregion

#pragma region �κ��丮 ����

	if (player.Inventory)
	{
		if (player.Inven == MAGIC) IMAGEMANAGER->findImage("����")->render(getMemDC(), 0, 0);
		if (player.Inven == QUEST) IMAGEMANAGER->findImage("����Ʈ")->render(getMemDC(), 0, 0);
		if (player.Inven == CHARECTER) IMAGEMANAGER->findImage("ĳ����")->render(getMemDC(), 0, 0);
	}
#pragma endregion
}