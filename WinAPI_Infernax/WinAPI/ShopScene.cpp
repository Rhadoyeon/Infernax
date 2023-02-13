#include "Stdafx.h"
#include "ShopScene.h"

HRESULT ShopScene::init(void)
{
#pragma region 초기화
	unit = new Unit;
	unit->init();

	item = new ItemSkill;
	item->init();

	shop.X, shop.Y = 0;
	shop.npcRc = RectMakeCenter(shop.X, shop.Y, 120, 41);
	worldTimeCount = 0;

	smithFrameX = magicianFrameX = skillFrameX = buyFrameX = 0;

	for (int i = 0; i < _countof(uiOn); i++) uiOn[i] = false;

	sellNum = 0;
	isSell = false;

	unit->setPlayerX(300.0f);
	unit->setPlayerDirection(true);

	// 스킬상인 (처음 npc / 손 비빔)
	DrawRectMake(getMemDC(), npcTemp[0] = RectMake(470, 500, 80, 120));
	// 장인
	DrawRectMake(getMemDC(), npcTemp[1] = RectMake(690, 496, 90, 120));
	// 마법사
	DrawRectMake(getMemDC(), npcTemp[2] = RectMake(915, 500, 80, 120));
#pragma endregion
	return S_OK;
}

void ShopScene::release(void)
{
	unit->release();
	SAFE_DELETE(unit);

	item->release();
	SAFE_DELETE(item);
}

void ShopScene::update(void)
{
	isSell = false;

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
	item->update();
	worldTimeCount++;

#pragma region 상인 & 플레이어 충돌
	RECT temp;
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		// 스킬 상인
		if (IntersectRect(&temp, &unit->getPlayerRc(), &npcTemp[0]))
		{
			if (uiOn[0]) uiOn[0] = false;
			else if (!uiOn[0]) uiOn[0] = true;
		}
		// 장인
		if (IntersectRect(&temp, &unit->getPlayerRc(), &npcTemp[1]))
		{
			if (uiOn[1]) uiOn[1] = false;
			else if (!uiOn[1]) uiOn[1] = true;
		}
		// 마법사
		if (IntersectRect(&temp, &unit->getPlayerRc(), &npcTemp[2]))
		{
			if (uiOn[2]) uiOn[2] = false;
			else if (!uiOn[2]) uiOn[2] = true;
		}
	}
#pragma endregion

	// ==============================================================================================================
	//if (uiOn)
	//{
	//	buyFrameX++;
	//	if (buyFrameX > IMAGEMANAGER->findImage("마법구매창")->getMaxFrameX()) buyFrameX = 1;
	//	//if (KEYMANAGER->isOnceKeyDown(VK_BACK)) uiOn = false;
	//}
	//if(KEYMANAGER->isOnceKeyDown(VK_BACK))
	//{
	//	uiOn = false;
	//	buyFrameX = 0;
	//}
#pragma region UI 선택후 좌/우 키 이동
	if (!uiOn[0] && !uiOn[1] && !uiOn[2])
	{
		unit->update();
		buyFrameX = 0;
	}

	if (uiOn[0] || uiOn[1] || uiOn[2])
	{
		if (uiOn[1] || uiOn[2])
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
			{
				buyFrameX--;
				buyFrameX != 2;
			}

			if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
			{
				buyFrameX++;
				buyFrameX != -1;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			isSell = true;
		}

		if (isSell)
		{
			if (uiOn[0])
			{
				if (item->getItemSkill()[0].price < SAVEMANAGER->getPlayerGold()) SAVEMANAGER->setPlayerGold(SAVEMANAGER->getPlayerGold() - item->getItemSkill()[0].price);
			}
			if (uiOn[1])
			{
				if (item->getItemSkill()[1].price < SAVEMANAGER->getPlayerGold())
					SAVEMANAGER->setPlayerGold(SAVEMANAGER->getPlayerGold() - item->getItemSkill()[buyFrameX + 1].price);
			}
			if (uiOn[2])
			{
				if (item->getItemSkill()[1].price <= SAVEMANAGER->getPlayerGold())
				{
					if (buyFrameX == 0)	SAVEMANAGER->setPlayerGold(SAVEMANAGER->getPlayerGold() - item->getItemSkill()[3].price);
					if (buyFrameX == 1) SAVEMANAGER->setPlayerGold(SAVEMANAGER->getPlayerGold() - item->getItemSkill()[4].price);
				}
			}
		}
	}
#pragma endregion

#pragma region 상인 프레임 움직임
	if (worldTimeCount % 15 == 0) smithFrameX++;
	if (worldTimeCount % 200 == 0) magicianFrameX++;
	if (worldTimeCount % 35 == 0) skillFrameX++;
	if (smithFrameX > IMAGEMANAGER->findImage("장인")->getMaxFrameX()) smithFrameX = 0;
	if (magicianFrameX > IMAGEMANAGER->findImage("마법사")->getMaxFrameX()) magicianFrameX = 0;
	if (skillFrameX > IMAGEMANAGER->findImage("스킬상인")->getMaxFrameX()) skillFrameX = 0;
#pragma endregion

	if (unit->getPlayerX() <= 214)
	{
		bgAlpha += 7;
		if (bgAlpha > 255)
		{
			SCENEMANAGER->changeScene("마을");
		}
	}

	shop.Rc = RectMakeCenter(shop.X, shop.Y, 120, 41);
}

void ShopScene::render(void)
{

#pragma region 상점 그리기
	IMAGEMANAGER->findImage("무기상점")->render(getMemDC(), shop.X - 30, shop.Y - 162);
	//DrawRectMake(getMemDC(), unit->getPlayerRc());
	DrawRectMake(getMemDC(), npcTemp[0]);
	DrawRectMake(getMemDC(), npcTemp[1]);
	DrawRectMake(getMemDC(), npcTemp[2]);

	if (uiOn[0])
	{
		IMAGEMANAGER->findImage("스킬구매창")->render(getMemDC(), 0, 0);
		FONTMANAGER->drawInt(getMemDC(), 1150, 65, 36, 255, 255, 255, "Perfect DOS VGA 437", true, (char*)SAVEMANAGER->getPlayerGold());
	}
	if (uiOn[1])
	{
		IMAGEMANAGER->findImage("방어구구매창")->frameRender(getMemDC(), 0, 0, buyFrameX, 0);
		FONTMANAGER->drawInt(getMemDC(), 1150, 65, 36, 255, 255, 255, "Perfect DOS VGA 437", true, (char*)SAVEMANAGER->getPlayerGold());
	}
	if (uiOn[2])
	{
		IMAGEMANAGER->findImage("마법구매창")->frameRender(getMemDC(), 0, 0, buyFrameX, 0);
		FONTMANAGER->drawInt(getMemDC(), 1150, 65, 36, 255, 255, 255, "Perfect DOS VGA 437", true, (char*)SAVEMANAGER->getPlayerGold());
	}
	IMAGEMANAGER->findImage("장인")->frameRender(getMemDC(), 680, 496, smithFrameX, 0);
	IMAGEMANAGER->findImage("마법사")->frameRender(getMemDC(), 925, 517, magicianFrameX, 0);
	IMAGEMANAGER->findImage("스킬상인")->frameRender(getMemDC(), 480, 505, skillFrameX, 0);
#pragma endregion

	item->render();
	unit->playerRender();

	IMAGEMANAGER->findImage("알파블랙")->alphaRender(getMemDC(), 0, 0, bgAlpha);

}

// 스테이지 하나를 완성..

// 완성
// 마을에서 상점 하나(다이얼로그)

// 미완성
// 초반 다이얼로그, 보스 타격 모션, 플레이어 적 충돌, 위로 올라가는 맵, 왼쪽-> 오른쪽 이동 맵
// 보스 컷씬, 보스 한마리 더, 엔딩, 사운드, 메인메뉴 수정
