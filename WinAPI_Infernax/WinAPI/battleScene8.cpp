#include "Stdafx.h"
#include "battleScene8.h"

HRESULT battleScene8::init(void)
{
	unit = new Unit;
	unit->init();

	//change = false;
	bgAlpha8 = 0;
	return S_OK;
}

void battleScene8::release(void)
{
	SAFE_DELETE(unit);
}

void battleScene8::update(void)
{
	unit->update();
	if (unit->getPlayerX() >= 1135)
	{
		bgAlpha8 += 2;
		if (bgAlpha8 > 255)
		{
			SCENEMANAGER->changeScene("배틀맵7");
			//change = true;
		}
	}

	//if (change)
	//{
	//	unit->setPlayerX(100.0f);
	//	unit->setPlayerDirection(true);
	//}
}

void battleScene8::render(void)
{
	unit->playerRender();

	IMAGEMANAGER->findImage("알파블랙")->alphaRender(getMemDC(), 0, 0, bgAlpha8);
}
