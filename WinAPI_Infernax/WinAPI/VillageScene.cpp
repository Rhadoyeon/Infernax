#include "Stdafx.h"
#include "VillageScene.h"

HRESULT VillageScene::init(void)
{
	unit = new Unit;
	unit->init();

	bgMove = 0;

	return S_OK;
}

void VillageScene::release(void)
{
	SAFE_DELETE(unit);
}

void VillageScene::update(void)
{
	if (!unit->getPlayerMove() && KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		bgMove += 2.0f;
	}

	if (unit->getPlayerMove() && KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		bgMove -= 2.0f;
	}

	if (bgMove > 1434)
	{
		bgMove = 1434;
	}
	if (bgMove < -500)
	{
		bgMove = -500;
	}
	unit->update();
}

void VillageScene::render(void)
{
	IMAGEMANAGER->findImage("배경1")->render(getMemDC(), bgMove - 1700, 0);
	IMAGEMANAGER->findImage("배경2")->render(getMemDC(), bgMove - 1800, -200);
	IMAGEMANAGER->findImage("마을_배경")->render(getMemDC(), bgMove - 1433, 0);

	unit->playerRender();
}
