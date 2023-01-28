#include "Stdafx.h"
#include "MainGame.h"
#include "StartScene.h"
#include "battleScene.h"
#include "battleScene2.h"

HRESULT MainGame::init(void)
{
	GameNode::init(TRUE);
	Images();

	SCENEMANAGER->addScene("½ÃÀÛ", new StartScene);
	SCENEMANAGER->addScene("¹èÆ²¸Ê", new battleScene);
	SCENEMANAGER->addScene("¹èÆ²¸Ê2", new battleScene2);

	SCENEMANAGER->changeScene("½ÃÀÛ");

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
}

void MainGame::update(void)
{
	GameNode::update();

	SCENEMANAGER->update();
}

void MainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	
	SCENEMANAGER->render();

	TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC());
}


