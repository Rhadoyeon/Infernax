#include "Stdafx.h"
#include "MainGame.h"
#include "StartScene.h"
#include "MainMenu.h"
#include "battleScene.h"
#include "battleScene2.h"
#include "VillageScene.h"
#include "ShopScene.h"
#include "battleScene3.h"
#include "battleScene4.h"
//#include "battleScene5.h"
//#include "battleScene6.h"
//#include "battleScene7.h"

HRESULT MainGame::init(void)
{
	GameNode::init(TRUE);
	Images();

	SCENEMANAGER->addScene("½ÃÀÛ", new StartScene);
	SCENEMANAGER->addScene("¸ÞÀÎ¸Þ´º", new MainMenu);
	SCENEMANAGER->addScene("¹èÆ²¸Ê", new battleScene);
	SCENEMANAGER->addScene("¹èÆ²¸Ê2", new battleScene2);
	SCENEMANAGER->addScene("¸¶À»", new VillageScene);
	SCENEMANAGER->addScene("¹«±â»óÁ¡", new ShopScene);
	SCENEMANAGER->addScene("¹èÆ²¸Ê3", new battleScene3);
	SCENEMANAGER->addScene("¹èÆ²¸Ê4", new battleScene4);
	//SCENEMANAGER->addScene("¹èÆ²¸Ê5", new battleScene3);
	//SCENEMANAGER->addScene("¹èÆ²¸Ê6", new battleScene3);
	//SCENEMANAGER->addScene("¹èÆ²¸Ê7", new battleScene3);

	SCENEMANAGER->changeScene("¹èÆ²¸Ê4");

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