#include "Stdafx.h"
#include "battleScene.h"

HRESULT battleScene::init(void)
{
	unit = new Unit;
	unit->init();

	bgMove = 0;
	crossX = 100;
	crossY = 350;
	crossRC = RectMakeCenter(crossX, crossY, 90, 114);

	crowFrameX = crowFrameY = 0;

	return S_OK;
}

void battleScene::release(void)
{
	SAFE_DELETE(unit);
}

void battleScene::update(void)
{
	unit->update();

	if (unit->getWorldTimeCount() % 15 == 0) crowFrameX++;
	if (crowFrameX > IMAGEMANAGER->findImage("까마귀")->getMaxFrameX()) crowFrameX = 0;

	if (unit->getBgMove() >= 600)
	{
		crossRC.top += 2;
		crossRC.right += 2;
	}

	crossRC = RectMakeCenter(crossX, crossY, 90, 114);

	//cout << unit->getBgMove() << endl;
}

void battleScene::render(void)
{
	// 배경 그리기
	IMAGEMANAGER->findImage("배경1")->render(getMemDC(), unit->getBgMove() - 1200, 0);
	IMAGEMANAGER->findImage("배경2")->render(getMemDC(), unit->getBgMove() - 1200, -200);
	IMAGEMANAGER->findImage("전투1")->render(getMemDC(), unit->getBgMove() - 1000, -200);
	
	IMAGEMANAGER->findImage("까마귀")->frameRender(getMemDC(), unit->getBgMove() - 530, 350, crowFrameX, 0);

	// 까마귀 그리기
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			IMAGEMANAGER->findImage("까마귀")->frameRender(getMemDC(), unit->getBgMove() - 530 + (2 + i * 2) * (2 + j * 2), 350 + (2 + i * 2) * (2 + j * 2), crowFrameX, 0);
		}
	}

	// 플레이어와 적 그리기
	unit->render();

	//IMAGEMANAGER->findImage("전투2")->render(getMemDC(), 0, 0, _player->getPlayerX() + 849, _player->getPlayerY(), 1280, 800);
	//IMAGEMANAGER->findImage("전투1")->render(getMemDC(), 0, 0, _player->getPlayerX(), _player->getPlayerY(), 1280, 800);
	// 1,2: 0,0 화면 시작
	// 3,4: 복사시작지점, 어디기준으로 player x,y 좌표,
	// 5,6: 복사영역(가로세로 크기)
}