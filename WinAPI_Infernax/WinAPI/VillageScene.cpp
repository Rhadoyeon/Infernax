#include "Stdafx.h"
#include "VillageScene.h"

HRESULT VillageScene::init(void)
{
	unit = new Unit;
	unit->init();

	return S_OK;
}

void VillageScene::release(void)
{
	SAFE_DELETE(unit);
}

void VillageScene::update(void)
{
	unit->update();
}

void VillageScene::render(void)
{
	IMAGEMANAGER->findImage("배경1")->render(getMemDC(), 0, 0);
	IMAGEMANAGER->findImage("배경2")->render(getMemDC(), 0, -200);
	IMAGEMANAGER->findImage("마을_배경")->render(getMemDC(), 0, 0);

	unit->playerRender();

}
