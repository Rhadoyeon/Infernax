#include "Stdafx.h"
#include "battleScene4.h"

HRESULT battleScene4::init(void)
{
	unit = new Unit;
	unit->init();

	bgAlpha4 = 0;

	unit->setPlayerVillage(true);
	unit->setPlayerX(100.0f);
	unit->setPlayerDirection(true);

	return S_OK;
}

void battleScene4::release(void)
{
	SAFE_DELETE(unit);
}

void battleScene4::update(void)
{
	unit->update();

	if (unit->getPlayerX() <= 30)
	{
		bgAlpha4 += 2;
		if (bgAlpha4 > 255)
		{
			SCENEMANAGER->changeScene("배틀맵5");
		}
	}
}

void battleScene4::render(void)
{
	IMAGEMANAGER->findImage("벨페고르배경")->render(getMemDC(), -890, -20);
	//IMAGEMANAGER->findImage("배경3")->render(getMemDC(), unit->getBgMove() - 200, 0);
	//IMAGEMANAGER->findImage("배경4")->render(getMemDC(), unit->getBgMove() - 200, -200);
	//IMAGEMANAGER->findImage("전투4")->render(getMemDC(), unit->getBgMove() - 1000, -200);

	unit->BelphegorRender();
	unit->playerRender();

	IMAGEMANAGER->findImage("알파블랙")->alphaRender(getMemDC(), 0, 0, bgAlpha4);
}
