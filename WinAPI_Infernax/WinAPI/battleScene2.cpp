#include "Stdafx.h"
#include "battleScene2.h"

HRESULT battleScene2::init(void)
{
	unit = new Unit;
	unit->init();

	return S_OK;
}

void battleScene2::release(void)
{
	SAFE_DELETE(unit);
}

void battleScene2::update(void)
{
	unit->update();


	if (unit->getPlayerX() <= 30)
	{
		bgAlpha2 += 2;
		if (bgAlpha2 > 255)
		{
			SCENEMANAGER->changeScene("마을");
		}
	}
}

void battleScene2::render(void)
{
	// 배경 그리기
	IMAGEMANAGER->findImage("배경1")->render(getMemDC(), 0, 0);
	IMAGEMANAGER->findImage("배경2")->render(getMemDC(), 0, -200);
	IMAGEMANAGER->findImage("전투2")->render(getMemDC(), -100, 0);

	// 플레이어와 적 그리기
	//unit->render();
	unit->bossVomitRender();
	unit->playerRender();

	IMAGEMANAGER->findImage("알파블랙")->alphaRender(getMemDC(), 0, 0, bgAlpha2);

}