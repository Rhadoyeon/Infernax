#include "Stdafx.h"
#include "MainGame.h"
#include "StartScene.h"
#include "battleScene.h"
#include "battleScene2.h"
#include "VillageScene.h"

HRESULT MainGame::init(void)
{
	GameNode::init(TRUE);
	Images();

	SCENEMANAGER->addScene("시작", new StartScene);
	SCENEMANAGER->addScene("배틀맵", new battleScene);
	SCENEMANAGER->addScene("배틀맵2", new battleScene2);
	SCENEMANAGER->addScene("마을", new VillageScene);

	//SCENEMANAGER->addScene("방어구", new VillageScene);
	//SCENEMANAGER->addScene("스킬", new VillageScene);

	SCENEMANAGER->changeScene("마을");

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


