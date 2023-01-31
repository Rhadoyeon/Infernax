#include "Stdafx.h"
#include "battleScene2.h"

HRESULT battleScene2::init(void)
{
	unit = new Unit;
	unit->init();

	bgMove2 = 0;

	return S_OK;
}

void battleScene2::release(void)
{
	SAFE_DELETE(unit);
}

void battleScene2::update(void)
{
	unit->update();


	/*if (playerX <= 0)
	{
		bgAlpha2++;
		if (bgAlpha2 > 255)
		{
			SCENEMANAGER->changeScene("����");
		}
	}*/

}

void battleScene2::render(void)
{
	// ��� �׸���
	IMAGEMANAGER->findImage("���1")->render(getMemDC(), /*unit->getBgMove() - */1200, 0);
	IMAGEMANAGER->findImage("���2")->render(getMemDC(),/* unit->getBgMove() -*/ 1200, -200);
	IMAGEMANAGER->findImage("����2")->render(getMemDC(), /*unit->getBgMove() -*/ 1432, 0);

	// �÷��̾�� �� �׸���
	//unit->render();
	unit->bossVomitRender();
	unit->playerRender();
}