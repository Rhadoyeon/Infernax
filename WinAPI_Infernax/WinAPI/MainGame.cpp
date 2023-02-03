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

	SCENEMANAGER->addScene("����", new StartScene);
	SCENEMANAGER->addScene("��Ʋ��", new battleScene);
	SCENEMANAGER->addScene("��Ʋ��2", new battleScene2);
	SCENEMANAGER->addScene("����", new VillageScene);

	//SCENEMANAGER->addScene("��", new VillageScene);
	//SCENEMANAGER->addScene("��ų", new VillageScene);

	SCENEMANAGER->changeScene("����");

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


