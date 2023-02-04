#include "Stdafx.h"
#include "ShopScene.h"

HRESULT ShopScene::init(void)
{
	unit = new Unit;
	unit->init();


	shop.X, shop.Y = 0;
	shop.npcRc = RectMakeCenter(shop.X, shop.Y, 120, 41);
	worldTimeCount = 0;

	smithFrameX = magicianFrameX = skillFrameX = 0;

	unit->setPlayerX(300.0f);
	unit->setPlayerDirection(true);

	return S_OK;
}

void ShopScene::release(void)
{
	SAFE_DELETE(unit);
}

void ShopScene::update(void)
{
	//if (ui)
	//{
	//	이미지매니저 ui이미지들~



	//	if (키매니저 좌버튼)
	//	else if (키매니저 우버튼)
	//	else if (키매니저 x버튼) // 구매
	//	else if (키매니저 z버튼)
	//		ui = false;

	//}
	//else
	//{
	//	unit->update();
	//	worldTimeCount++;
	//	if (worldTimeCount % 10 == 0) npcFrameX++;
	//	if (npcFrameX > IMAGEMANAGER->findImage("장인")->getMaxFrameX()) npcFrameX = 0;

	//	shop.Rc = RectMakeCenter(shop.X, shop.Y, 100, 100);

	//}

	//if(키매니저 x누른다)
	//	 ui = 트루
	unit->update();
	worldTimeCount++;
	if (worldTimeCount % 15 == 0) smithFrameX++;
	if (worldTimeCount % 200 == 0) magicianFrameX++;
	if (worldTimeCount % 35 == 0) skillFrameX++;
	if (smithFrameX > IMAGEMANAGER->findImage("장인")->getMaxFrameX()) smithFrameX = 0;
	if (magicianFrameX > IMAGEMANAGER->findImage("마법사")->getMaxFrameX()) magicianFrameX = 0;
	if (skillFrameX > IMAGEMANAGER->findImage("스킬상인")->getMaxFrameX()) skillFrameX = 0;

	shop.Rc = RectMakeCenter(685, 146, 960, 150);
}

void ShopScene::render(void)
{
	IMAGEMANAGER->findImage("무기상점")->render(getMemDC(), 0, -162);
	IMAGEMANAGER->findImage("장인")->frameRender(getMemDC(), 700, 496, smithFrameX, 0);
	IMAGEMANAGER->findImage("마법사")->frameRender(getMemDC(), 930, 517, magicianFrameX, 0);
	IMAGEMANAGER->findImage("스킬상인")->frameRender(getMemDC(), 500, 505, skillFrameX, 0);
	//DrawRectMake(getMemDC(), shop.Rc);
	//IMAGEMANAGER->findImage("알파블랙")->render(getMemDC(), shop.Rc.left, shop.Rc.top);
	unit->playerRender();
}

// 스테이지 하나를 완성..
// 초반 다이얼로그, 보스 타격 모션, 플레이어 적 충돌, 마을에서 상점 하나(다이얼로그), 맵 이동 플레이어 중심으로 이동, 위로 올라가는 맵, 왼쪽-> 오른쪽 이동 맵
// 보스 컷씬, 보스 한마리 더, 엔딩, 사운드, 메인메뉴 수정
