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
			SCENEMANAGER->changeScene("��Ʋ��5");
		}
	}

	unit->update();
}

void battleScene6::render(void)
{
	IMAGEMANAGER->findImage("ũ�μ����")->render(getMemDC(), 0, -160);
	IMAGEMANAGER->findImage("ũ�μ���������")->render(getMemDC(), -915, -643);

	unit->CrocellRender();
	unit->playerRender();

	IMAGEMANAGER->findImage("���ĺ�")->alphaRender(getMemDC(), 0, 0, bgAlpha6);
}
