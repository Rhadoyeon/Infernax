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



	// 까마귀 초기화
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
			if (crows[i].index > IMAGEMANAGER->findImage("까마귀")->getMaxFrameX()) crows[i].index = 0;
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
			SCENEMANAGER->changeScene("배틀맵2");
		}
	}

	if (unit->getWorldTimeCount() % 15 == 0) crowFrameX++;
	if (crowFrameX > IMAGEMANAGER->findImage("까마귀")->getMaxFrameX()) crowFrameX = 0;

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
	// 배경 그리기
	/*IMAGEMANAGER->findImage("배경1")->render(getMemDC(), unit->getBgMove() - 1200, 0);
	IMAGEMANAGER->findImage("배경2")->render(getMemDC(), unit->getBgMove() - 1200, -200);
	IMAGEMANAGER->findImage("전투1")->render(getMemDC(), unit->getBgMove() - 1000, -200);*/

	IMAGEMANAGER->findImage("배경1")->render(getMemDC(), -200, 0);
	IMAGEMANAGER->findImage("배경2")->render(getMemDC(), -200, -200);
	IMAGEMANAGER->findImage("전투1")->render(getMemDC(), -200, -200);

	// 까마귀 그리기
	for (int i = 0; i < _countof(crows); i++)
	{
		if (crows[i].left)
			IMAGEMANAGER->findImage("까마귀")->frameRender(getMemDC(), crows[i].startX, crows[i].startY, crows[i].index, 0);
		else
			IMAGEMANAGER->findImage("까마귀")->frameRender(getMemDC(), crows[i].startX, crows[i].startY, crows[i].index, 1);
	}

	// 플레이어와 적 그리기
	//unit->render();
	unit->enemyRender();
	unit->playerRender();

	//IMAGEMANAGER->findImage("전투2")->render(getMemDC(), 0, 0, _player->getPlayerX() + 849, _player->getPlayerY(), 1280, 800);
	//IMAGEMANAGER->findImage("전투1")->render(getMemDC(), 0, 0, _player->getPlayerX(), _player->getPlayerY(), 1280, 800);
	// 1,2: 0,0 화면 시작
	// 3,4: 복사시작지점, 어디기준으로 player x,y 좌표,
	// 5,6: 복사영역(가로세로 크기)
}