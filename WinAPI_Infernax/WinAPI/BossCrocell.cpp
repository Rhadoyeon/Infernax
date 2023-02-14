#include "Stdafx.h"
#include "Unit.h"


// ������ ���� ��ȯ�Ѵ�.
// ��ȯ�ϴ� �������� ������.
// ���� ������ ���� ������! (�Ұ��� �༭ ���� �� Ʈ�簡 �Ǽ� ���� 2�� ������)
// ���� ���� 2�� ���� ������ ����� ���;��Ѵ�.
// �������� �ƴ� ������ ���� �� ������ ������ �ﰢ�Լ��� ����Ͽ� �� ȭ������ 3�� ���;��Ѵ�.
// ȭ������ �߻��ϴ� ���� �������� ���ư���.
// �������� �� ���ư� �� �ٽ� 1��������

void Unit::CrocellInit(void)
{
	Crocell.X = Crocell.Y = 0;
	Crocell.SkillFrameX1 /*= Crocell.SkillFrameY1*/ = Crocell.SkillFrameX2 = Crocell.DieFrameX = 0;

	Crocell.Hp = 0;
	/*Crocell.EnemyDiePatternChange =*/ Crocell.Die = false;
	currentTime = 5000;
	CrocellPattern = 0;

	CrocellSkeletonReset();
	//vBullet.X = vBullet.Y = 0;
	//vBullet.shot = false;
	//vBullet.degree = 0.0f;
}

void Unit::CrocellUpdate(void)
{
	//cout << CrocellPattern << endl;
	//cout << player.Y << endl;

	Crocell.Rc = RectMake(Crocell.X + 870, Crocell.Y + 220, 300, 400);
	Skeleton.Rc = RectMake(Skeleton.X + 980, Skeleton.Y + 510, 58, 109);

	if (!Crocell.Die)
	{

		if (CrocellPattern == 0)
		{
			Crocell.CrocellState = C_ATTACK1;
			if (worldTimeCount % 25 == 0) Crocell.SkillFrameX1++;
			if (Crocell.SkillFrameX1 > IMAGEMANAGER->findImage("ũ�μ�_�����ȯ")->getMaxFrameX()) Crocell.SkillFrameX1 = 4;

			if (Crocell.SkillFrameX1 == 4)
			{
				if (worldTimeCount % 25 == 0) Skeleton.WalKFrame++;
				if (Skeleton.WalKFrame > IMAGEMANAGER->findImage("�ذ�_�ȱ�")->getMaxFrameX()) Skeleton.WalKFrame = 0;
				Skeleton.X -= 1;
			}

			RECT Stemp;
			if (IntersectRect(&Stemp, &player.AttackRc, &Skeleton.Rc))
			{
				if (Skeleton.Hp < 30)
				{
					Skeleton.Hp++;
				}
			}

			if (Skeleton.Hp == 30)
			{
				Skeleton.Die = true;
			}

			if (Skeleton.Die && CrocellPattern == 0)
			{
				CrocellPattern = 1;
				Crocell.SkillFrameX1 = 0;
			}

			//cout << CrocellPattern << endl;
		}

		else if (CrocellPattern == 1)
		{
			Crocell.SkillFrameX2 = 0;
			if (Crocell.SkillFrameX2 == 0)
			{
				currentTime = TIMEMANAGER->getWorldTime();
				CrocellPattern = 2;
				vBullet.clear();
				for (int i = 0; i < 3; i++)
				{
					float BulletX = RND->getFromFloatTo(900.0f, 960.0f);
					float BulletY = RND->getFromFloatTo(350.0f, 400.0f);
					vBullet.push_back({ BulletX, BulletY, RectMakeCenter(BulletX, BulletY, 11, 12), getAngle(BulletX, BulletY, player.X, player.Y) + (float)(i - 0.5) * 2, false });
				}

				//BulletX += cosf(getAngle(0.0f, 0.0f, 69.0f, 198.0f));
				//BulletY -= sinf(getAngle(0.0f, 0.0f, 69.0f, 198.0f));
			}
		}

		else if (CrocellPattern == 2)
		{
			if (worldTimeCount % 17 == 0) Crocell.SkillFrameX2++;
			if (Crocell.SkillFrameX2 > IMAGEMANAGER->findImage("ũ�μ�_ȭ����")->getMaxFrameX()) Crocell.SkillFrameX2 = 3;
			for (int i = 0; i < 3; i++)
			{
				vBullet[i].X += cosf(vBullet[i].degree) * 5;
				vBullet[i].Y -= sinf(vBullet[i].degree) * 5;
				vBullet[i].BulletRc = RectMakeCenter(vBullet[i].X, vBullet[i].Y,11,12);
			}


			//Crocell.SkillFrameX2 = 2;
			if (TIMEMANAGER->getWorldTime() - currentTime > /*5*/1)
			{
				CrocellPattern = 0;
				//������ ������ ���̷��� �ʱⰪ���� �ٽ� ����ش�.
				CrocellSkeletonReset();
			}
			
		}

		RECT Ctemp;
		if (IntersectRect(&Ctemp, &player.AttackRc, &Crocell.Rc))
		{
			if (Crocell.Hp < 400) Crocell.Hp++;
		}
	}
	//cout << CrocellPattern << endl;

	if (Crocell.Hp == 400)
	{
		Crocell.Die = true;
		Crocell.CrocellState = C_DIE;
		if (worldTimeCount % 17 == 0) Crocell.DieFrameX++;
		if (Crocell.DieFrameX > IMAGEMANAGER->findImage("ũ�μ�_����")->getMaxFrameX()) Crocell.DieFrameX = 7;

	}
}

void Unit::CrocellRender(void)
{
	//DrawRectMake(getMemDC(), Skeleton.Rc);
	//DrawRectMake(getMemDC(), Crocell.Rc);

	if (!Crocell.Die)
	{
		if (CrocellPattern == 0)
		{
			if (Crocell.CrocellState == C_ATTACK1)
			{
				IMAGEMANAGER->findImage("�ذ�_�ȱ�")->frameRender(getMemDC(), Skeleton.Rc.left, Skeleton.Rc.top, Skeleton.WalKFrame, 0);
				IMAGEMANAGER->findImage("ũ�μ�_�����ȯ")->frameRender(getMemDC(), Crocell.Rc.left, Crocell.Rc.top - 54, Crocell.SkillFrameX1, 0);
			}
		}

		//if (Skeleton.Die)
		//{
		//	IMAGEMANAGER->findImage("�ذ�_����")->frameRender(getMemDC(), Skeleton.Rc.left, Skeleton.Rc.top, Crocell.DieFrameX, 0);
		//}

		else if (CrocellPattern == 1)
		{
			IMAGEMANAGER->findImage("ũ�μ�_ȭ����")->frameRender(getMemDC(), Crocell.Rc.left, Crocell.Rc.top - 54, Crocell.SkillFrameX2, 0);
		}

		else if (CrocellPattern == 2)
		{
			IMAGEMANAGER->findImage("ũ�μ�_ȭ����")->frameRender(getMemDC(), Crocell.Rc.left, Crocell.Rc.top - 54, Crocell.SkillFrameX2, 0);
			IMAGEMANAGER->findImage("ũ�μ�_�Ѿ�")->render(getMemDC(), vBullet[0].BulletRc.left, vBullet[0].BulletRc.top);
			IMAGEMANAGER->findImage("ũ�μ�_�Ѿ�")->render(getMemDC(), vBullet[1].BulletRc.left, vBullet[1].BulletRc.top);
			IMAGEMANAGER->findImage("ũ�μ�_�Ѿ�")->render(getMemDC(), vBullet[2].BulletRc.left, vBullet[2].BulletRc.top);
		}
	}

	if (Crocell.Die)
	{
		if (Crocell.CrocellState == C_DIE)
		{
			IMAGEMANAGER->findImage("ũ�μ�_����")->frameRender(getMemDC(), Crocell.Rc.left - 150, Crocell.Rc.top - 84, Crocell.DieFrameX, 0);
		}
	}
}

void Unit::CrocellSkeletonReset(void)
{
	Skeleton.WalKFrame = Skeleton.AttackFrame = 0;
	Skeleton.X = Skeleton.Y = 0;
	Skeleton.Hp = 0;
	Skeleton.Die = false;

	Skeleton.Rc = RectMake(Skeleton.X + 930, Skeleton.Y + 510, 58, 109);
}