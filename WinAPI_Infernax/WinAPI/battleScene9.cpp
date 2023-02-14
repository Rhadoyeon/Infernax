#include "Stdafx.h"
#include "battleScene9.h"

HRESULT battleScene9::init(void)
{
	unit = new Unit;
	unit->init();

	bgAlpha9 = 0;

	unit->setPlayerX(100.0f);
	unit->setPlayerDirection(true);

	return S_OK;
}

void battleScene9::release(void)
{
	SAFE_DELETE(unit);
}

void battleScene9::update(void)
{
	//if (unit->getPlayerX() <= 30)
	//{
	//	bgAlpha9 += 2;
	//	if (bgAlpha9 > 255)
	//	{
	//		SCENEMANAGER->changeScene("배틀맵7");
	//	}
	//}

	unit->update();

}

void battleScene9::render(void)
{
	IMAGEMANAGER->findImage("고대웜배경1")->render(getMemDC(), 0, -250);
	IMAGEMANAGER->findImage("고대웜배경2")->render(getMemDC(), 0, 350);
	IMAGEMANAGER->findImage("고대웜전투지형")->render(getMemDC(), -405, -155);

	unit->AncientWormRender();
	unit->playerRender();

	IMAGEMANAGER->findImage("알파블랙")->alphaRender(getMemDC(), 0, 0, bgAlpha9);

}
