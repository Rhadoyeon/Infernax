#include "Stdafx.h"
#include "battleScene.h"

HRESULT battleScene::init(void)
{
	unit = new Unit;
	unit->init();

	bgMove1 = 0;
	//crossX = 100;
	//crossY = 350;
	//crossRC = RectMakeCenter(crossX, crossY, 90, 114);

	//crowFrameX = crowFrameY = 0;



	// ��� �ʱ�ȭ
	for (int i = 0; i < _countof(crows); i++)
	{
		crows[i].startX = RND->getFromFloatTo(100.0f, 400.0f);
		crows[i].startY = RND->getFromFloatTo(250.0f, 450.0f);
		crows[i].endX = RND->getFromFloatTo(-400.0f, -100.0f);
		crows[i].endY = RND->getFromFloatTo(-100.0f, -200.0f);
		crows[i].index = 0;
		crows[i].left = false;
	}

	return S_OK;
}

void battleScene::release(void)
{
	SAFE_DELETE(unit);
}

void battleScene::update(void)
{
	unit->update();

	for (int i = 0; i < _countof(crows); i++)
	{
		if (unit->getWorldTimeCount() % 15 == 0)
		{
			crows[i].index++;
			if (crows[i].index > IMAGEMANAGER->findImage("���")->getMaxFrameX()) crows[i].index = 0;
		}

		if (unit->getPlayerX() < 500)
		{
			crows[i].left = true;
			crows[i].radian = getAngle(crows[i].startX, crows[i].startY, crows[i].endX, crows[i].endY);
			crows[i].startX += cosf(crows[i].radian) * 5;
			crows[i].startY -= sinf(crows[i].radian) * 5;
		}
	}

	if (unit->getPlayerX() <= 30)
	{
		bgAlpha1 += 50;
		if (bgAlpha1 > 255)
		{
			SCENEMANAGER->changeScene("��Ʋ��2");
		}
	}

	if (unit->getWorldTimeCount() % 15 == 0) crowFrameX++;
	if (crowFrameX > IMAGEMANAGER->findImage("���")->getMaxFrameX()) crowFrameX = 0;

	/*if (unit->getBgMove() >= 600)
	{
		crossRC.top += 2;
		crossRC.right += 2;
	}*/

	//crossRC = RectMakeCenter(crossX, crossY, 90, 114);

	//cout << unit->getBgMove() << endl;
}

void battleScene::render(void)
{
	// ��� �׸���
	/*IMAGEMANAGER->findImage("���1")->render(getMemDC(), unit->getBgMove() - 1200, 0);
	IMAGEMANAGER->findImage("���2")->render(getMemDC(), unit->getBgMove() - 1200, -200);
	IMAGEMANAGER->findImage("����1")->render(getMemDC(), unit->getBgMove() - 1000, -200);*/

	IMAGEMANAGER->findImage("���1")->render(getMemDC(), -200, 0);
	IMAGEMANAGER->findImage("���2")->render(getMemDC(), -200, -200);
	IMAGEMANAGER->findImage("����1")->render(getMemDC(), -200, -200);

	// ��� �׸���
	for (int i = 0; i < _countof(crows); i++)
	{
		if (crows[i].left)
			IMAGEMANAGER->findImage("���")->frameRender(getMemDC(), crows[i].startX, crows[i].startY, crows[i].index, 0);
		else
			IMAGEMANAGER->findImage("���")->frameRender(getMemDC(), crows[i].startX, crows[i].startY, crows[i].index, 1);
	}

	// �÷��̾�� �� �׸���
	//unit->render();
	unit->enemyRender();
	unit->playerRender();

	//IMAGEMANAGER->findImage("����2")->render(getMemDC(), 0, 0, _player->getPlayerX() + 849, _player->getPlayerY(), 1280, 800);
	//IMAGEMANAGER->findImage("����1")->render(getMemDC(), 0, 0, _player->getPlayerX(), _player->getPlayerY(), 1280, 800);
	// 1,2: 0,0 ȭ�� ����
	// 3,4: �����������, ���������� player x,y ��ǥ,
	// 5,6: ���翵��(���μ��� ũ��)
}