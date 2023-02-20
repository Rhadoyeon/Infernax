#include "Stdafx.h"
#include "SoundScene.h"

HRESULT SoundScene::init(void)
{

	IMAGEMANAGER->addImage("배경", "Resources/Images/Background/Tree.bmp", WINSIZE_X, WINSIZE_Y);
	SOUNDMANAGER->addSound("플레이어_타격", "Resources/Sounds/PlayerHit.wav", true, true);
	return S_OK;
}

void SoundScene::release(void)
{
}

void SoundScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		SOUNDMANAGER->play("플레이어_타격", 1.0f);
	}



	if (KEYMANAGER->isOnceKeyDown(VK_MBUTTON))
	{
		SOUNDMANAGER->pause("플레이어_타격");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		SOUNDMANAGER->resume("플레이어_타격");
	}

	SOUNDMANAGER->update();
}

void SoundScene::render(void)
{
	IMAGEMANAGER->render("배경", getMemDC());
}