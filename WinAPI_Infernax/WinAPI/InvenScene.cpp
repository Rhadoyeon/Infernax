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
		IMAGEMANAGER->findImage("마법")->render(getMemDC(), WINSIZE_X, WINSIZE_Y);
		if (KEYMANAGER->isToggleKey('2')) IMAGEMANAGER->findImage("퀘스트")->render(getMemDC(), WINSIZE_X, WINSIZE_Y);
		if (KEYMANAGER->isToggleKey('3')) IMAGEMANAGER->findImage("캐릭터")->render(getMemDC(), WINSIZE_X, WINSIZE_Y);
	}
}
