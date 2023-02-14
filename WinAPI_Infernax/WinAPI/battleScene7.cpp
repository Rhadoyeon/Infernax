#include "Stdafx.h"
#include "battleScene7.h"

HRESULT battleScene7::init(void)
{
	unit = new Unit;
	unit->init();

	bgAlpha7 = 0;

	unit->setPlayerX(690.0f);
	unit->setPlayerDirection(true);

	//unit->setPlayerX(100.0f);

    return S_OK;
}

void battleScene7::release(void)
{
	SAFE_DELETE(unit);
}

void battleScene7::update(void)
{
	if (unit->getPlayerX() <= 30)
	{
		bgAlpha7 += 2;
		if (bgAlpha7 > 255)
		{
			SCENEMANAGER->changeScene("배틀맵8");
		}
	}

	if (unit->getPlayerX() >= 1250)
	{
		bgAlpha7 += 2;
		if (bgAlpha7 > 255)
		{
			SCENEMANAGER->changeScene("배틀맵9");
		}
	}

	unit->update();
}

void battleScene7::render(void)
{
	IMAGEMANAGER->findImage("고대웜배경1")->render(getMemDC(), 0, -450);
	IMAGEMANAGER->findImage("고대웜배경2")->render(getMemDC(), -100, 300);
	IMAGEMANAGER->findImage("전투7")->render(getMemDC(), -820, -200);

	unit->playerRender();

	IMAGEMANAGER->findImage("알파블랙")->alphaRender(getMemDC(), 0, 0, bgAlpha7);
}
