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
		if (belphegor.FrameX == 12) ChangeBoss = 1;
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
		if (belphegor.ScreamFrameX > IMAGEMANAGER->findImage("�����_���")->getMaxFrameX()) belphegor.ScreamFrameX = 4;

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
	if (!belphegor.Die)
	{
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
					else if (player.Rc.left > belphegor.Rc.right)
					{
						belphegor.FrameY = 1;
						belphegor.X += 1;
					}
				}

				// �ɾ���� ���� �÷��̾ �浹�� ��Ʈ�� �ε����� â�� ����´�.
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

			// ������ true �϶� ���� 4��
			if (belphegor.Attack)
			{
				// â������
				if (belphegor.Count == 1)
				{
					belphegor.BelphegorState = B_ATTACK;
				}
				// �ȱ�
				else if (belphegor.Count == 2)
				{
					belphegor.BelphegorState = B_ATTACK2;
				}
				// ȭ���� ��ȯ
				else if (belphegor.Count == 3)
				{
					belphegor.BelphegorState = B_ATTACK3;
				}
				// ������
				else if (belphegor.Count == 4)
				{
					belphegor.BelphegorState = B_ATTACK4;
				}
			}

			// ����1 â������
			if (belphegor.BelphegorState == B_ATTACK)
			{
				if (worldTimeCount % 17 == 0) javelin.TrowFrameX++;
				if (javelin.TrowFrameX > IMAGEMANAGER->findImage("�����_â������")->getMaxFrameX()) javelin.TrowFrameX = 3;
				if (javelin.TrowFrameX == 3) belphegor.BelphegorState = B_WALK2;

				// ������ ����� max�϶� â ���� �ȴ� ����� ���´�.
				if (belphegor.BelphegorState == B_WALK2)
				{
					if (worldTimeCount % 25 == 0) belphegor.WalkFrameX++;
					if (belphegor.WalkFrameX > IMAGEMANAGER->findImage("�����_�ȱ�")->getMaxFrameX()) belphegor.WalkFrameX = 0;

					// â�� �ٴڿ� ���� �ڿ� ������ �÷��̾ ������ �ʰ� â�� ���� ����
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

				// â ��ó�� �ٴٸ��� ������ �ݴ� ����� ���ϰ� â�� �������� �Ѵ�.
				if (belphegor.BelphegorState == B_TAKE)
				{
					if (worldTimeCount % 17 == 0) javelin.TakeFrameX++;
					if (javelin.TakeFrameX > IMAGEMANAGER->findImage("�����_âȸ��")->getMaxFrameX()) javelin.TakeFrameX = 4;
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

			// ����2 �ȱ� �� �ٽ� ��Ʈ�� �浹�Ǹ� �ٸ� �������� �Ѿ��.
			else if (belphegor.BelphegorState == B_ATTACK2)
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

			// ����3 ȭ������ ������.
			else if (belphegor.BelphegorState == B_ATTACK3)
			{
				if (worldTimeCount % 17 == 0) belphegor.ScreamFrameX++;
				if (belphegor.ScreamFrameX > IMAGEMANAGER->findImage("�����_���_â")->getMaxFrameX()) belphegor.ScreamFrameX = 3;

				if (worldTimeCount % 10 == 0) potal.FrameX1++;
				if (potal.FrameX1 > IMAGEMANAGER->findImage("�����_��ȯ��Ż3")->getMaxFrameX()) potal.FrameX1 = 8;

				if (potal.FrameX1 >= 1)
				{
					if (worldTimeCount % 10 == 0) potal.FireBallFrameX++;
					if (potal.FireBallFrameX > IMAGEMANAGER->findImage("�����_ȭ����")->getMaxFrameX()) potal.FireBallFrameX = 0;
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

			// ����4 ������
			else if (belphegor.BelphegorState == B_ATTACK4)
			{
				if (worldTimeCount % 17 == 0) belphegor.KickFrameX++;
				if (belphegor.KickFrameX > IMAGEMANAGER->findImage("�����_������")->getMaxFrameX()) belphegor.KickFrameX = 3;

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
		if (belphegor.DieFrameX > IMAGEMANAGER->findImage("�����_����")->getMaxFrameX()) belphegor.DieFrameX = 16;
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


void Unit::BelphegorRender(void)
{

#pragma region ���� �ƾ� ����

	if (ChangeBoss == 0)
	{
		IMAGEMANAGER->findImage("�����_�ƾ�")->frameRender(getMemDC(), belphegor.X, belphegor.Y - 40, belphegor.FrameX, 0);
	}

	else if (ChangeBoss == 1)
	{
		IMAGEMANAGER->findImage("�����_â������")->frameRender(getMemDC(), belphegor.X, belphegor.Y, javelin.TrowFrameX, 0);
	}

	else if (ChangeBoss == 2)
	{
		IMAGEMANAGER->findImage("�����_���")->frameRender(getMemDC(), belphegor.X, belphegor.Y, belphegor.ScreamFrameX, 0);
	}

	else if (ChangeBoss == 3)
	{
		IMAGEMANAGER->findImage("�����_�ȱ�")->frameRender(getMemDC(), belphegor.X + 37, belphegor.Y, belphegor.WalkFrameX, 0);
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
		// ���� ���� ������ / â�� ��� �ȴ´�.
		if (!belphegor.Attack)
		{
			if (belphegor.BelphegorState == B_WALK)
			{
				if (belphegor.FrameY == 1)
					IMAGEMANAGER->findImage("�����_�ȱ�_â")->frameRender(getMemDC(), belphegor.Rc.left - 40, belphegor.Rc.top, belphegor.WalkFrameX, belphegor.FrameY);
				else if (belphegor.FrameY == 0)
					IMAGEMANAGER->findImage("�����_�ȱ�_â")->frameRender(getMemDC(), belphegor.Rc.left - 55, belphegor.Rc.top, belphegor.WalkFrameX, belphegor.FrameY);
			}
		}
		// ������ �����Ҷ� / ���� = â������, ȭ���� ��ȯ, ������
		else if (belphegor.Attack)
		{
			// ����1 â������
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

			//����2 �ȱ�
			else if (belphegor.Count == 2)
			{
				if (belphegor.BelphegorState == B_ATTACK2)
				{
					if (belphegor.FrameY == 1)
						IMAGEMANAGER->findImage("�����_�ȱ�_â")->frameRender(getMemDC(), belphegor.Rc.left - 55, belphegor.Rc.top, belphegor.WalkFrameX, belphegor.FrameY);
					else if (belphegor.FrameY == 0)
						IMAGEMANAGER->findImage("�����_�ȱ�_â")->frameRender(getMemDC(), belphegor.Rc.left - 55, belphegor.Rc.top, belphegor.WalkFrameX, belphegor.FrameY);
				}
			}

			//����3 ȭ���� ��ȯ�ϱ�
			else if (belphegor.Count == 3)
			{
				if (belphegor.BelphegorState == B_ATTACK3)
				{
					if (belphegor.FrameY == 1)
						IMAGEMANAGER->findImage("�����_���_â")->frameRender(getMemDC(), belphegor.Rc.left - 193, belphegor.Rc.top, belphegor.ScreamFrameX, belphegor.FrameY);
					else if (belphegor.FrameY == 0)
						IMAGEMANAGER->findImage("�����_���_â")->frameRender(getMemDC(), belphegor.Rc.left - 156, belphegor.Rc.top, belphegor.ScreamFrameX, belphegor.FrameY);

					if (belphegor.FrameY == 1)
						IMAGEMANAGER->findImage("�����_ȭ����")->frameRender(getMemDC(), potal.FireballRc.left, potal.FireballRc.top, potal.FireBallFrameX, belphegor.FrameY);
					else if (belphegor.FrameY == 0)
						IMAGEMANAGER->findImage("�����_ȭ����")->frameRender(getMemDC(), potal.FireballRc.left, potal.FireballRc.top + 70, potal.FireBallFrameX, belphegor.FrameY);

					if (belphegor.FrameY == 1)
						IMAGEMANAGER->findImage("�����_��ȯ��Ż3")->frameRender(getMemDC(), belphegor.Rc.left + 330, belphegor.Rc.top - 220, potal.FrameX1, belphegor.FrameY);
					else if (belphegor.FrameY == 0)
						IMAGEMANAGER->findImage("�����_��ȯ��Ż3")->frameRender(getMemDC(), belphegor.Rc.left - 250, belphegor.Rc.top - 220, potal.FrameX1, belphegor.FrameY);
					//if (belphegor.ChangePotal)
					//{
					//	if (belphegor.FrameY == 1)
					//		IMAGEMANAGER->findImage("�����_��ȯ��Ż1")->frameRender(getMemDC(), belphegor.Rc.left - 200, belphegor.Rc.top, potal.FrameX1, belphegor.FrameY);
					//	else if (belphegor.FrameY == 0)
					//		IMAGEMANAGER->findImage("�����_��ȯ��Ż1")->frameRender(getMemDC(), belphegor.Rc.left - 200, belphegor.Rc.top - 200, potal.FrameX1, belphegor.FrameY);
					//}
					//else
					//{
					//	if (belphegor.FrameY == 1)
					//		IMAGEMANAGER->findImage("�����_��ȯ��Ż2")->frameRender(getMemDC(), belphegor.Rc.left - 200, belphegor.Rc.top, potal.FrameX2, belphegor.FrameY);
					//	else if (belphegor.FrameY == 0)
					//		IMAGEMANAGER->findImage("�����_��ȯ��Ż2")->frameRender(getMemDC(), belphegor.Rc.left - 200, belphegor.Rc.top - 200, potal.FrameX2, belphegor.FrameY);
					//}
				}
			}

			// ����4 ������
			else if (belphegor.Count == 4)
			{
				if (belphegor.BelphegorState == B_ATTACK4)
				{
					if (belphegor.FrameY == 1)
						IMAGEMANAGER->findImage("�����_������")->frameRender(getMemDC(), belphegor.Rc.left - 230, belphegor.Rc.top - 15, belphegor.KickFrameX, belphegor.FrameY);
					else if (belphegor.FrameY == 0)
						IMAGEMANAGER->findImage("�����_������")->frameRender(getMemDC(), belphegor.Rc.left - 125, belphegor.Rc.top - 15, belphegor.KickFrameX, belphegor.FrameY);
				}
			}
		}

		// ������ â�� ������ �� â ����
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

		// ������� â�� �տ� �����־�� �ϹǷ� ���� ������ ���ش�.
		if (javelin.TrowFrameX >= 2 && javelin.TakeFrameX <= 1)
		{
			if (belphegor.FrameY == 1)
				IMAGEMANAGER->findImage("�����_â")->frameRender(getMemDC(), javelin.Rc.left + 500, javelin.Rc.top - 255, javelin.FrameX, belphegor.FrameY);
			if (belphegor.FrameY == 0)
				IMAGEMANAGER->findImage("�����_â")->frameRender(getMemDC(), javelin.Rc.left - 50, javelin.Rc.top - 255, javelin.FrameX, belphegor.FrameY);
		}
	}

	if (belphegor.Die)
	{
		if (belphegor.BelphegorState == B_DIE)
		{
			if (belphegor.FrameY == 1)
				IMAGEMANAGER->findImage("�����_����")->frameRender(getMemDC(), belphegor.Rc.left - 320, belphegor.Rc.top - 60, belphegor.DieFrameX, belphegor.FrameY);
			if (belphegor.FrameY == 0)
				IMAGEMANAGER->findImage("�����_����")->frameRender(getMemDC(), belphegor.Rc.left - 270, belphegor.Rc.top - 60, belphegor.DieFrameX, belphegor.FrameY);
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
