#include "Stdafx.h"
#include "InvenScene.h"

HRESULT InvenScene::init(void)
{
	inven = false;
	return S_OK;
}

void InvenScene::release(void)
{

}

void InvenScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		inven = true;
	}
}

void InvenScene::render(void)
{
	if (inven)
	{
		IMAGEMANAGER->findImage("����")->render(getMemDC(), WINSIZE_X, WINSIZE_Y);
		if (KEYMANAGER->isToggleKey('2')) IMAGEMANAGER->findImage("����Ʈ")->render(getMemDC(), WINSIZE_X, WINSIZE_Y);
		if (KEYMANAGER->isToggleKey('3')) IMAGEMANAGER->findImage("ĳ����")->render(getMemDC(), WINSIZE_X, WINSIZE_Y);
	}
}
