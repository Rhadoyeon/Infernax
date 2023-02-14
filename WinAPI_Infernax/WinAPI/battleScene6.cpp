#include "Stdafx.h"
#include "battleScene6.h"

HRESULT battleScene6::init(void)
{
	unit = new Unit;
	unit->init();

	bgAlpha6 = 0;

	unit->setPlayerX(100.0f);
	unit->setPlayerDirection(true);


	return S_OK;
}

void battleScene6::release(void)
{
	SAFE_DELETE(unit);
}

void battleScene6::update(void)
{
	if (unit->getPlayerX() <= 30)
	{
		bgAlpha6 += 2;
		if (bgAlpha6 > 255)
		{
			SCENEMANAGER->changeScene("배틀맵5");
		}
	}

	unit->update();
}

void battleScene6::render(void)
{
	IMAGEMANAGER->findImage("크로셀배경")->render(getMemDC(), 0, -160);
	IMAGEMANAGER->findImage("크로셀전투지형")->render(getMemDC(), -915, -643);

	unit->CrocellRender();
	unit->playerRender();

	IMAGEMANAGER->findImage("알파블랙")->alphaRender(getMemDC(), 0, 0, bgAlpha6);
}
