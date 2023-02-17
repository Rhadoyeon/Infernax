#include "Stdafx.h"
#include "battleScene8.h"

HRESULT battleScene8::init(void)
{
	unit = new Unit;
	unit->init();

	//change = false;

	unit->setPlayerX(800.0f);

	bgAlpha8 = 0;
	return S_OK;
}

void battleScene8::release(void)
{
	SAFE_DELETE(unit);
}

void battleScene8::update(void)
{
	unit->update();
	if (unit->getPlayerX() >= 1135)
	{
		bgAlpha8 += 2;
		if (bgAlpha8 > 255)
		{
			SCENEMANAGER->changeScene("��Ʋ��7");
			//change = true;
		}
	}

	//if (change)
	//{
	//	unit->setPlayerX(100.0f);
	//	unit->setPlayerDirection(true);
	//}
}

void battleScene8::render(void)
{
	IMAGEMANAGER->findImage("�����ź���1")->render(getMemDC(), -630, -335);
	IMAGEMANAGER->findImage("�����ź��������1")->render(getMemDC(), -1050, -317);

	unit->LeviathanRender();
	unit->playerRender();

	IMAGEMANAGER->findImage("���ĺ�")->alphaRender(getMemDC(), 0, 0, bgAlpha8);
}
