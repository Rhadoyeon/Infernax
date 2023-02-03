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
			SCENEMANAGER->changeScene("����");
		}
	}
}

void battleScene2::render(void)
{
	// ��� �׸���
	IMAGEMANAGER->findImage("���1")->render(getMemDC(), 0, 0);
	IMAGEMANAGER->findImage("���2")->render(getMemDC(), 0, -200);
	IMAGEMANAGER->findImage("����2")->render(getMemDC(), -100, 0);

	// �÷��̾�� �� �׸���
	//unit->render();
	unit->bossVomitRender();
	unit->playerRender();

	IMAGEMANAGER->findImage("���ĺ�")->alphaRender(getMemDC(), 0, 0, bgAlpha2);

}