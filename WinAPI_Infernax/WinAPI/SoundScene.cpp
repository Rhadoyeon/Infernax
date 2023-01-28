#include "Stdafx.h"
#include "SoundScene.h"

HRESULT SoundScene::init(void)
{

	IMAGEMANAGER->addImage("배경", "Resources/Images/Background/Tree.bmp", WINSIZE_X, WINSIZE_Y);
	SOUNDMANAGER->addSound("나무", "Resources/Sounds/ending.mp3", true, true);
	return S_OK;
}

void SoundScene::release(void)
{
}

void SoundScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		SOUNDMANAGER->play("나무", 1.0f);
	}



	if (KEYMANAGER->isOnceKeyDown(VK_MBUTTON))
	{
		SOUNDMANAGER->pause("나무");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		SOUNDMANAGER->resume("나무");
	}

	SOUNDMANAGER->update();
}

void SoundScene::render(void)
{
	IMAGEMANAGER->render("배경", getMemDC());
}