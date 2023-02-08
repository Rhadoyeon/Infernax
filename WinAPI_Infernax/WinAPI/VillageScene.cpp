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
		SCENEMANAGER->changeScene("�������");
	}

	if (unit->getPlayerX() <= 40 )
	{
		bgAlpha3 += 2;
		if (bgAlpha3 > 255)
		{
			SCENEMANAGER->changeScene("��Ʋ��3");
		}
	}
}

void VillageScene::render(void)
{
	IMAGEMANAGER->findImage("���1")->render(getMemDC(), unit->getBgMove() - 2200, 0);
	IMAGEMANAGER->findImage("���2")->render(getMemDC(), unit->getBgMove() - 2200, -200);
	IMAGEMANAGER->findImage("����_���")->render(getMemDC(), unit->getBgMove() - 2300, 0);

	IMAGEMANAGER->findImage("���ĺ�")->alphaRender(getMemDC(), 0, 0, bgAlpha3);

	unit->playerRender();
}
