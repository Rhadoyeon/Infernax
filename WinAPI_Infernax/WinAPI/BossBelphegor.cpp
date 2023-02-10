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

#pragma region ���� �ƾ� ������Ʈ

	//if (player.X < 150)
	//{
	//	player.State = P_WALK;
	//	player.X += 2;
	//	if (player.X == 150)
	//	{
	//		player.State = P_STAND;
	//	}
	//}

	// ���� �Ͼ��
	if (ChangeBoss == 0)
	{
		if (player.X >= 150)
		{
			if (worldTimeCount % 17 == 0) belphegor.FrameX++;
			if (belphegor.FrameX > IMAGEMANAGER->findImage("�����_�ƾ�")->getMaxFrameX()) belphegor.FrameX = 12;
		}
		if(belphegor.FrameX == 12) ChangeBoss = 1;
	}

	// ���� â������
	if (ChangeBoss == 1)
	{
		if (worldTimeCount % 17 == 0) javelin.TrowFrameX++;
		if (javelin.TrowFrameX > IMAGEMANAGER->findImage("�����_â������")->getMaxFrameX()) javelin.TrowFrameX = 3;
		if (javelin.TrowFrameX == 3) ChangeBoss = 2;
	}

	// â���󰡴� ������
	if (javelin.TrowFrameX >= 2)
	{
		if (worldTimeCount % 5 == 0) javelin.FrameX++;
		if (javelin.FrameX > IMAGEMANAGER->findImage("�����_â")->getMaxFrameX()) javelin.FrameX = 3;
	}

	// ���� �Ҹ�ġ��
	if (ChangeBoss == 2)
	{
		if (worldTimeCount % 17 == 0) belphegor.ScreamFrameX++;
		if (belphegor.ScreamFrameX > IMAGEMANAGER->findImage("�����_��ħ")->getMaxFrameX()) belphegor.ScreamFrameX = 4;
		
		belphegor.BossTimeCount++;
		if (belphegor.BossTimeCount < 100)
		{
			if (belphegor.ScreamFrameX == 4) ChangeBoss = 3;
		}
	}

	// ���� �ȱ�
	if (ChangeBoss == 3)
	{
		belphegor.X -= 0.8f;
		if (worldTimeCount % 25 == 0) belphegor.WalkFrameX++;
		if (belphegor.WalkFrameX > IMAGEMANAGER->findImage("�����_�ȱ�")->getMaxFrameX()) belphegor.WalkFrameX = 4;

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

	// ���� âȸ��
	if (ChangeBoss == 4)
	{
		belphegor.BelphegorState = B_TAKE;
		if (worldTimeCount % 17 == 0) javelin.TakeFrameX++;
		if (javelin.TakeFrameX > IMAGEMANAGER->findImage("�����_âȸ��")->getMaxFrameX())
		{
			belphegor.SkillFrameX = javelin.FrameX = javelin.TrowFrameX = 0;
			belphegor.ScreamFrameX = belphegor.WalkFrameX = belphegor.StandFrameX = javelin.TakeFrameX = javelin.StayFrameX = 0;
			ChangeBoss++;
			belphegor.BelphegorState = B_WALK;
		}
	}
#pragma endregion

#pragma region ���� ���� ������Ʈ

	// ���� ���� ����
	if (ChangeBoss == 5)
	{
		// �����̴� <-> �ƴϴ� �Ұ�
		if (!belphegor.Attack)
		{
			// ������ ���� �ϸ� ������ �÷��̾�� �ɾ�´�.
			if (belphegor.BelphegorState == B_WALK)
			{
				if (worldTimeCount % 25 == 0) belphegor.WalkFrameX++;
				if (belphegor.WalkFrameX > IMAGEMANAGER->findImage("�����_�ȱ�_â")->getMaxFrameX()) belphegor.WalkFrameX = 0;

				// ����
				if (player.Rc.right < belphegor.Rc.left)
				{
					belphegor.FrameY = 0;
					belphegor.X -= 1;
				}

				// ������
				if (player.Rc.left > belphegor.Rc.right)
				{
					belphegor.FrameY = 1;
					belphegor.X += 1;
				}
			}

			// �ɾ���� ���� �÷��̾ �浹�� ��Ʈ�� �ε����� â�� ����´�.
			RECT temp;
			if (IntersectRect(&temp, &player.Rc, &belphegor.AttackRc)/*&& !&belphegor.Rc*/)
			{
				belphegor.Attack = true;
				belphegor.Count = 1;
				belphegor.BelphegorState = B_ATTACK;
			}
		}

		// �Ұ��� ���� ī��Ʈ, ���� ī��Ʈ
		// ���� ���� ����
		// â������
		// �ι�° �浹 �ٸ� ���� ��ȯ�ϴ� �Ұ�, ����° �浹 ������....
		// ī��Ʈ�� ���� �ö� �� ����° ī��Ʈ�϶� �ٽ� 0�� ����.
		// �÷��̾ ����
		// ���� ī��Ʈ �ö󰡰� �� �� ���� �̻� �� ��� ����.

		else if (belphegor.Attack)
		{
			if (belphegor.Count == 1)
			{
				if (belphegor.BelphegorState == B_ATTACK)
				{
					if (worldTimeCount % 17 == 0) javelin.TrowFrameX++;
					if (javelin.TrowFrameX > IMAGEMANAGER->findImage("�����_â������")->getMaxFrameX()) javelin.TrowFrameX = 3;
					if (javelin.TrowFrameX == 3) belphegor.BelphegorState = B_WALK2;
				}

				// ������ ����� max�϶� â ���� �ȴ� ����� ���´�.
				if (belphegor.BelphegorState == B_WALK2)
				{
					if (worldTimeCount % 25 == 0) belphegor.WalkFrameX++;
					if (belphegor.WalkFrameX > IMAGEMANAGER->findImage("�����_�ȱ�")->getMaxFrameX()) belphegor.WalkFrameX = 0;

					// â�� �ٴڿ� ���� �ڿ� ������ �÷��̾ ������ �ʰ� â�� ���� ����
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

				// â ��ó�� �ٴٸ��� ������ �ݴ� ����� ���ϰ� â�� �������� �Ѵ�.
				if (belphegor.BelphegorState == B_TAKE)
				{
					if (worldTimeCount % 17 == 0) javelin.TakeFrameX++;
					if (javelin.TakeFrameX > IMAGEMANAGER->findImage("�����_âȸ��")->getMaxFrameX()) javelin.TakeFrameX = 4;
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
					if (javelin.TakeFrameX > IMAGEMANAGER->findImage("�����_��ȯ��Ż")->getMaxFrameX()) javelin.TakeFrameX = 3;
					if (javelin.TakeFrameX == 3)
					{
						if (worldTimeCount % 17 == 0) javelin.TakeFrameX++;
						if (javelin.TakeFrameX > IMAGEMANAGER->findImage("�����_��ȯ��Ż2")->getMaxFrameX()) javelin.TakeFrameX = 0;
					}
				}
			}
			// â�� �ֿ� �� �ٽ� �÷��̾ ���󰡾��ϸ� �÷��̾ �浹�� ��Ʈ�� �ε����� â�� ������ ������ ���;��Ѵ�
			//if()
			// �����̴�
			// â�� ������
			// â�� ���� �ȴ´�.
			// â�� ������ ����
			// â�� ȸ���ϸ�
			// ���� ���µ� Ǯ���� ���µ� walk�� �ٲٰ� �÷��̾ �ٶ󺻴�.
		}
	}

	//if (ChangeBoss == 5)
	//{	
	//	// ���� �� �Ҷ��� ���� �ȱ�
	//	if (!belphegor.Attack)
	//	{
	//		if (belphegor.BelphegorState != E_WALK2)
	//		{
	//			belphegor.BelphegorState = E_WALK;
	//			if (worldTimeCount % 25 == 0) belphegor.WalkFrameX++;
	//			if (belphegor.WalkFrameX > IMAGEMANAGER->findImage("�����_�ȱ�_â")->getMaxFrameX()) belphegor.WalkFrameX = 0;
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
	//		// 	if (belphegor.WalkFrameX > IMAGEMANAGER->findImage("�����_�ȱ�_â")->getMaxFrameX()) belphegor.WalkFrameX = 0;
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
	//		// �ں��� ȸ���Ϸ� ����
	//		//else
	//		//{
	//		//	if (belphegor.JavelinX < belphegor.Rc.left)
	//		//	{
	//		//		belphegor.X -= 1;
	//		//		//cout << "�ں��� ��" << endl;
	//		//	}
	//		//	if (belphegor.JavelinX > belphegor.Rc.right)
	//		//	{
	//		//		belphegor.X += 1;
	//		//		//cout << "�ں��� ��" << endl;
	//		//	}
	//		//	//cout << "������" << belphegor.JavelinX << endl;
	//		//	//cout << "����" << belphegor.Rc.left << endl;
	//		//}
	//	}
	//	// ������ true�� �Ǹ� ���ø�� �� â ������ ������
	//	else if (belphegor.Attack)
	//	{
	//		belphegor.BelphegorState = E_ATTACK;
	//		if (worldTimeCount % 17 == 0) belphegor.JavelinTrowFrameX++;
	//		if (belphegor.JavelinTrowFrameX > IMAGEMANAGER->findImage("�����_â������")->getMaxFrameX())
	//		{
	//			belphegor.BelphegorState = E_WALK2;
	//		}
	//	}
	//	// �浹 ��Ʈ(�÷��̾�� �浹�� ���� ��Ʈ) �浹�ϸ� ������ â�� ������ ���
	//	RECT Belphe;
	//	if (IntersectRect(&Belphe, &player.Rc, &belphegor.AttackRc))
	//	{
	//		belphegor.Attack = true;
	//	}
	//	// ������ ����� �ƽ� �������϶� ���� false, â ���� ���� �ȱ� ���
	//	if (belphegor.BelphegorState == E_WALK2)
	//	{
	//		belphegor.Attack = false;
	//		if (worldTimeCount % 25 == 0) belphegor.WalkFrameX++;
	//		if (belphegor.WalkFrameX > IMAGEMANAGER->findImage("�����_�ȱ�")->getMaxFrameX()) belphegor.WalkFrameX = 0;
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

#pragma region ���� �ƾ� ����

	if (ChangeBoss == 0)
	{
		IMAGEMANAGER->findImage("�����_�ƾ�")->frameRender(getMemDC(), belphegor.X, belphegor.Y - 40, belphegor.FrameX, 0);
	}

	if (ChangeBoss == 1)
	{
		IMAGEMANAGER->findImage("�����_â������")->frameRender(getMemDC(), belphegor.X, belphegor.Y, javelin.TrowFrameX, 0);
	}

	else if (ChangeBoss == 2)
	{
		IMAGEMANAGER->findImage("�����_��ħ")->frameRender(getMemDC(), belphegor.X, belphegor.Y, belphegor.ScreamFrameX, 0);
	}

	else if (ChangeBoss == 3)
	{
		IMAGEMANAGER->findImage("�����_�ȱ�")->frameRender(getMemDC(), belphegor.X, belphegor.Y, belphegor.WalkFrameX, 0);
	}

	else if (ChangeBoss == 4)
	{
		IMAGEMANAGER->findImage("�����_âȸ��")->frameRender(getMemDC(), belphegor.X, belphegor.Y, javelin.TakeFrameX, 0);
	}

	if (javelin.TrowFrameX >= 2 && javelin.TakeFrameX <= 1 && ChangeBoss < 5)
	{
		IMAGEMANAGER->findImage("�����_â")->frameRender(getMemDC(), javelin.X + 400, belphegor.Y, javelin.FrameX, 0);
	}


#pragma endregion

#pragma region ���� ���� ����
	// 0 �϶� ������ -> ����
	// 1 �϶� ���� -> ������
	if (ChangeBoss == 5)
	{
		if (!belphegor.Attack)
		{
			if (belphegor.BelphegorState == B_WALK)
			{
				if (belphegor.FrameY == 1)
					IMAGEMANAGER->findImage("�����_�ȱ�_â")->frameRender(getMemDC(), belphegor.Rc.left - 55, belphegor.Rc.top, belphegor.WalkFrameX, belphegor.FrameY);
				else if (belphegor.FrameY == 0)
					IMAGEMANAGER->findImage("�����_�ȱ�_â")->frameRender(getMemDC(), belphegor.Rc.left - 55, belphegor.Rc.top, belphegor.WalkFrameX, belphegor.FrameY);
			}
		}
		else if (belphegor.Attack)
		{
			if (belphegor.Count == 1)
			{
				if (belphegor.BelphegorState == B_ATTACK)
				{
					if (belphegor.FrameY == 1)
						IMAGEMANAGER->findImage("�����_â������")->frameRender(getMemDC(), belphegor.Rc.left - 155, belphegor.Rc.top, javelin.TrowFrameX, belphegor.FrameY);
					else if (belphegor.FrameY == 0)
						IMAGEMANAGER->findImage("�����_â������")->frameRender(getMemDC(), belphegor.Rc.left - 105, belphegor.Rc.top, javelin.TrowFrameX, belphegor.FrameY);
				}

				if (belphegor.BelphegorState == B_WALK2)
				{
					if (belphegor.FrameY == 1)
						IMAGEMANAGER->findImage("�����_�ȱ�")->frameRender(getMemDC(), belphegor.Rc.left - 65, belphegor.Rc.top, belphegor.WalkFrameX, belphegor.FrameY);
					else if (belphegor.FrameY == 0)
						IMAGEMANAGER->findImage("�����_�ȱ�")->frameRender(getMemDC(), belphegor.Rc.left - 105, belphegor.Rc.top, belphegor.WalkFrameX, belphegor.FrameY);
				}

				if (belphegor.BelphegorState == B_TAKE)
				{
					if (belphegor.FrameY == 1)
						IMAGEMANAGER->findImage("�����_âȸ��")->frameRender(getMemDC(), belphegor.Rc.left - 195, belphegor.Rc.top, javelin.TakeFrameX, belphegor.FrameY);
					else if (belphegor.FrameY == 0)
						IMAGEMANAGER->findImage("�����_âȸ��")->frameRender(getMemDC(), belphegor.Rc.left - 155, belphegor.Rc.top, javelin.TakeFrameX, belphegor.FrameY);
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
			IMAGEMANAGER->findImage("�����_â")->frameRender(getMemDC(), javelin.X, javelin.Y, javelin.FrameX, belphegor.FrameY);
	}
#pragma endregion
	//DrawRectMake(getMemDC(), RectMake(belphegor.JavelinX, belphegor.JavelinY, 10, 10));
}
