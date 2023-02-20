#include "Stdafx.h"
#include "SoundScene.h"

HRESULT SoundScene::init(void)
{

	IMAGEMANAGER->addImage("���", "Resources/Images/Background/Tree.bmp", WINSIZE_X, WINSIZE_Y);
	SOUNDMANAGER->addSound("�÷��̾�_Ÿ��", "Resources/Sounds/PlayerHit.wav", true, true);
	return S_OK;
}

void SoundScene::release(void)
{
}

void SoundScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		SOUNDMANAGER->play("�÷��̾�_Ÿ��", 1.0f);
	}



	if (KEYMANAGER->isOnceKeyDown(VK_MBUTTON))
	{
		SOUNDMANAGER->pause("�÷��̾�_Ÿ��");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		SOUNDMANAGER->resume("�÷��̾�_Ÿ��");
	}

	SOUNDMANAGER->update();
}

void SoundScene::render(void)
{
	IMAGEMANAGER->render("���", getMemDC());
}