#include "Stdafx.h"
#include "Unit.h"


// 보스가 적을 소환한다.
// 소환하는 프레임을 돌린다.
// 좀비가 나오고 좀비가 죽으면! (불값을 줘서 죽은 후 트루가 되서 패턴 2가 나오게)
// 다음 패턴 2는 입을 벌리는 모션이 나와야한다.
// 프레임이 아닌 랜더가 놔서 그 랜더가 나오면 삼각함수를 사용하여 적 화염구가 3개 나와야한다.
// 화염구를 발사하는 동안 프레임이 돌아간다.
// 프레임이 다 돌아간 후 다시 1패턴으로

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
			if (Crocell.SkillFrameX1 > IMAGEMANAGER->findImage("크로셀_좀비소환")->getMaxFrameX()) Crocell.SkillFrameX1 = 4;

			if (Crocell.SkillFrameX1 == 4)
			{
				if (worldTimeCount % 25 == 0) Skeleton.WalKFrame++;
				if (Skeleton.WalKFrame > IMAGEMANAGER->findImage("해골_걷기")->getMaxFrameX()) Skeleton.WalKFrame = 0;
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
			if (Crocell.SkillFrameX2 > IMAGEMANAGER->findImage("크로셀_화염구")->getMaxFrameX()) Crocell.SkillFrameX2 = 3;
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
				//패턴이 끝나면 스켈레톤 초기값으로 다시 잡아준다.
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
		if (Crocell.DieFrameX > IMAGEMANAGER->findImage("크로셀_죽음")->getMaxFrameX()) Crocell.DieFrameX = 7;

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
				IMAGEMANAGER->findImage("해골_걷기")->frameRender(getMemDC(), Skeleton.Rc.left, Skeleton.Rc.top, Skeleton.WalKFrame, 0);
				IMAGEMANAGER->findImage("크로셀_좀비소환")->frameRender(getMemDC(), Crocell.Rc.left, Crocell.Rc.top - 54, Crocell.SkillFrameX1, 0);
			}
		}

		//if (Skeleton.Die)
		//{
		//	IMAGEMANAGER->findImage("해골_죽음")->frameRender(getMemDC(), Skeleton.Rc.left, Skeleton.Rc.top, Crocell.DieFrameX, 0);
		//}

		else if (CrocellPattern == 1)
		{
			IMAGEMANAGER->findImage("크로셀_화염구")->frameRender(getMemDC(), Crocell.Rc.left, Crocell.Rc.top - 54, Crocell.SkillFrameX2, 0);
		}

		else if (CrocellPattern == 2)
		{
			IMAGEMANAGER->findImage("크로셀_화염구")->frameRender(getMemDC(), Crocell.Rc.left, Crocell.Rc.top - 54, Crocell.SkillFrameX2, 0);
			IMAGEMANAGER->findImage("크로셀_총알")->render(getMemDC(), vBullet[0].BulletRc.left, vBullet[0].BulletRc.top);
			IMAGEMANAGER->findImage("크로셀_총알")->render(getMemDC(), vBullet[1].BulletRc.left, vBullet[1].BulletRc.top);
			IMAGEMANAGER->findImage("크로셀_총알")->render(getMemDC(), vBullet[2].BulletRc.left, vBullet[2].BulletRc.top);
		}
	}

	if (Crocell.Die)
	{
		if (Crocell.CrocellState == C_DIE)
		{
			IMAGEMANAGER->findImage("크로셀_죽음")->frameRender(getMemDC(), Crocell.Rc.left - 150, Crocell.Rc.top - 84, Crocell.DieFrameX, 0);
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