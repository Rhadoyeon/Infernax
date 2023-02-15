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
#include "battleScene5.h"
#include "battleScene6.h"
#include "battleScene7.h"
#include "battleScene8.h"
#include "battleScene9.h"

HRESULT MainGame::init(void)
{
	GameNode::init(TRUE);
	Images();

	SCENEMANAGER->addScene("시작", new StartScene);
	SCENEMANAGER->addScene("메인메뉴", new MainMenu);
	SCENEMANAGER->addScene("배틀맵", new battleScene);	 // 초반 좀비
	SCENEMANAGER->addScene("배틀맵2", new battleScene2);	 // 파이몬
	SCENEMANAGER->addScene("마을", new VillageScene);
	SCENEMANAGER->addScene("무기상점", new ShopScene);
	SCENEMANAGER->addScene("배틀맵3", new battleScene3);  // 통과지점
	SCENEMANAGER->addScene("배틀맵4", new battleScene4);	 // 벨페고르
	SCENEMANAGER->addScene("배틀맵5", new battleScene5);	 // 통과지점
	SCENEMANAGER->addScene("배틀맵6", new battleScene6);	 // 크로셀
	SCENEMANAGER->addScene("배틀맵7", new battleScene7); // 통과지점
	SCENEMANAGER->addScene("배틀맵8", new battleScene8); // 보스?
	SCENEMANAGER->addScene("배틀맵9", new battleScene9); // 고대웜

	SCENEMANAGER->changeScene("배틀맵9");

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