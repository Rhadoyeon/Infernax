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
#include "battleScene10.h"
//#include "battleScene11.h"
//#include "battleScene12.h"
//#include "battleScene13.h"

//??????
#include "Opening.h"
#include "BossVomitIntro.h"
//#include "BossBelphegorIntro.h"
#include "BossCrocellIntro.h"
#include "BossLeviathanIntro.h"
#include "BossLycanthropeIntro.h"


HRESULT MainGame::init(void)
{
	GameNode::init(TRUE);
	Images();

	SCENEMANAGER->addScene("????", new StartScene);
	SCENEMANAGER->addScene("???θ޴?", new MainMenu);
	SCENEMANAGER->addScene("??Ʋ??", new battleScene);		// ????
	SCENEMANAGER->addScene("??Ʋ??2", new battleScene2);		// ???̸?
	SCENEMANAGER->addScene("????", new VillageScene);
	SCENEMANAGER->addScene("????????", new ShopScene);
	SCENEMANAGER->addScene("??Ʋ??3", new battleScene3);		// ????????
	SCENEMANAGER->addScene("??Ʋ??4", new battleScene4);		// ????????
	SCENEMANAGER->addScene("??Ʋ??5", new battleScene5);		// ????????
	SCENEMANAGER->addScene("??Ʋ??6", new battleScene6);		// ũ?μ?
	SCENEMANAGER->addScene("??Ʋ??7", new battleScene7);		// ????????
	SCENEMANAGER->addScene("??Ʋ??8", new battleScene8);		// ??????ź
	SCENEMANAGER->addScene("??Ʋ??9", new battleScene9);		// ??????
	SCENEMANAGER->addScene("??Ʋ??10", new battleScene10);	// ?????ΰ?
	//SCENEMANAGER->addScene("??Ʋ??11", new battleScene11);
	//SCENEMANAGER->addScene("??Ʋ??12", new battleScene12);
	//SCENEMANAGER->addScene("??Ʋ??13", new battleScene13);

	// ??????
	SCENEMANAGER->addScene("??????", new Opening);		// ???? ???? ?????? ??????
	SCENEMANAGER->addScene("???̸?_??Ʈ??", new BossVomitIntro);
	//SCENEMANAGER->addScene("????????_??Ʈ??", new BossBelphegorIntro);
	SCENEMANAGER->addScene("ũ?μ?_??Ʈ??", new BossCrocellIntro);
	SCENEMANAGER->addScene("??????ź_??Ʈ??", new BossLeviathanIntro);
	SCENEMANAGER->addScene("?????ΰ?_??Ʈ??", new BossLycanthropeIntro);

	//????	

	// ???? ??
	SCENEMANAGER->changeScene("??Ʋ??8");

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

	if (!SCENEMANAGER->isPlayScene("??????") &&
		!SCENEMANAGER->isPlayScene("???̸?_??Ʈ??") &&
		!SCENEMANAGER->isPlayScene("ũ?μ?_??Ʈ??") &&
		!SCENEMANAGER->isPlayScene("??????ź_??Ʈ??") &&
		!SCENEMANAGER->isPlayScene("?????ΰ?_??Ʈ??"))
	this->getBackBuffer()->render(getHDC());
}