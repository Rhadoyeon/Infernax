#include "Stdafx.h"
#include "battleScene5.h"

HRESULT battleScene5::init(void)
{
	unit = new Unit;
	unit->init();

	bgAlpha5 = alpha = 0;

	unit->setPlayerX(100.0f);
	unit->setPlayerDirection(true);


	return S_OK;
}

void battleScene5::release(void)
{
	SAFE_DELETE(unit);
}

void battleScene5::update(void)
{
	if (unit->getPlayerX() <= 30)
	{
		bgAlpha5 += 2;
		if (bgAlpha5 > 255)
		{
			SCENEMANAGER->changeScene("��Ʋ��6");
		}
	}

	if (unit->getPlayerX() >= 1135)
	{
		bgAlpha5 += 2;
		if (bgAlpha5 > 255)
		{
			SCENEMANAGER->changeScene("��Ʋ��7");
		}
	}
	// cout << unit->getPlayerX() << endl;
	unit->update();

}

void battleScene5::render(void)
{
	IMAGEMANAGER->findImage("���3")->render(getMemDC(), -100, -250);
	IMAGEMANAGER->findImage("���4")->alphaRender(getMemDC(), 0, 150 , 35);
	IMAGEMANAGER->findImage("����5")->render(getMemDC(), - 1200, -280);

	unit->playerRender();

	IMAGEMANAGER->findImage("���ĺ�")->alphaRender(getMemDC(), 0, 0, bgAlpha5);
}
