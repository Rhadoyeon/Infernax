#include "Stdafx.h"
#include "VillageScene.h"

HRESULT VillageScene::init(void)
{
	unit = new Unit;
	unit->init();

	unit->setPlayerVillage(true);

	_battleScene2 = new battleScene2;
	_battleScene2->init();

	bgMove = 0;	


	return S_OK;
}

void VillageScene::release(void)
{
	SAFE_DELETE(unit);
}

void VillageScene::update(void)
{
	unit->update();


	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		SCENEMANAGER->changeScene("무기상점");
	}

	if (unit->getPlayerX() <= 40 )
	{
		bgAlpha3 += 2;
		if (bgAlpha3 > 255)
		{
			SCENEMANAGER->changeScene("배틀맵3");
		}
	}
}

void VillageScene::render(void)
{
	IMAGEMANAGER->findImage("배경1")->render(getMemDC(), unit->getBgMove() - 2200, 0);
	IMAGEMANAGER->findImage("배경2")->render(getMemDC(), unit->getBgMove() - 2200, -200);
	IMAGEMANAGER->findImage("마을_배경")->render(getMemDC(), unit->getBgMove() - 2300, 0);

	IMAGEMANAGER->findImage("알파블랙")->alphaRender(getMemDC(), 0, 0, bgAlpha3);

	unit->playerRender();
}
