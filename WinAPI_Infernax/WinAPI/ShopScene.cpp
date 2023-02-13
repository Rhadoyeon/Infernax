#include "Stdafx.h"
#include "ShopScene.h"

HRESULT ShopScene::init(void)
{
#pragma region �ʱ�ȭ
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

	// ��ų���� (ó�� npc / �� ���)
	DrawRectMake(getMemDC(), npcTemp[0] = RectMake(470, 500, 80, 120));
	// ����
	DrawRectMake(getMemDC(), npcTemp[1] = RectMake(690, 496, 90, 120));
	// ������
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
	//	�̹����Ŵ��� ui�̹�����~
	//	if (Ű�Ŵ��� �¹�ư)
	//	else if (Ű�Ŵ��� ���ư)
	//	else if (Ű�Ŵ��� x��ư) // ����
	//	else if (Ű�Ŵ��� z��ư)
	//		ui = false;
	//}
	//else
	//{
	//	unit->update();
	//	worldTimeCount++;
	//	if (worldTimeCount % 10 == 0) npcFrameX++;
	//	if (npcFrameX > IMAGEMANAGER->findImage("����")->getMaxFrameX()) npcFrameX = 0;
	//	shop.Rc = RectMakeCenter(shop.X, shop.Y, 100, 100);
	//}
	//if(Ű�Ŵ��� x������)
	//	 ui = Ʈ��
	item->update();
	worldTimeCount++;

#pragma region ���� & �÷��̾� �浹
	RECT temp;
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		// ��ų ����
		if (IntersectRect(&temp, &unit->getPlayerRc(), &npcTemp[0]))
		{
			if (uiOn[0]) uiOn[0] = false;
			else if (!uiOn[0]) uiOn[0] = true;
		}
		// ����
		if (IntersectRect(&temp, &unit->getPlayerRc(), &npcTemp[1]))
		{
			if (uiOn[1]) uiOn[1] = false;
			else if (!uiOn[1]) uiOn[1] = true;
		}
		// ������
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
	//	if (buyFrameX > IMAGEMANAGER->findImage("��������â")->getMaxFrameX()) buyFrameX = 1;
	//	//if (KEYMANAGER->isOnceKeyDown(VK_BACK)) uiOn = false;
	//}
	//if(KEYMANAGER->isOnceKeyDown(VK_BACK))
	//{
	//	uiOn = false;
	//	buyFrameX = 0;
	//}
#pragma region UI ������ ��/�� Ű �̵�
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

#pragma region ���� ������ ������
	if (worldTimeCount % 15 == 0) smithFrameX++;
	if (worldTimeCount % 200 == 0) magicianFrameX++;
	if (worldTimeCount % 35 == 0) skillFrameX++;
	if (smithFrameX > IMAGEMANAGER->findImage("����")->getMaxFrameX()) smithFrameX = 0;
	if (magicianFrameX > IMAGEMANAGER->findImage("������")->getMaxFrameX()) magicianFrameX = 0;
	if (skillFrameX > IMAGEMANAGER->findImage("��ų����")->getMaxFrameX()) skillFrameX = 0;
#pragma endregion

	if (unit->getPlayerX() <= 214)
	{
		bgAlpha += 7;
		if (bgAlpha > 255)
		{
			SCENEMANAGER->changeScene("����");
		}
	}

	shop.Rc = RectMakeCenter(shop.X, shop.Y, 120, 41);
}

void ShopScene::render(void)
{

#pragma region ���� �׸���
	IMAGEMANAGER->findImage("�������")->render(getMemDC(), shop.X - 30, shop.Y - 162);
	//DrawRectMake(getMemDC(), unit->getPlayerRc());
	DrawRectMake(getMemDC(), npcTemp[0]);
	DrawRectMake(getMemDC(), npcTemp[1]);
	DrawRectMake(getMemDC(), npcTemp[2]);

	if (uiOn[0])
	{
		IMAGEMANAGER->findImage("��ų����â")->render(getMemDC(), 0, 0);
		FONTMANAGER->drawInt(getMemDC(), 1150, 65, 36, 255, 255, 255, "Perfect DOS VGA 437", true, (char*)SAVEMANAGER->getPlayerGold());
	}
	if (uiOn[1])
	{
		IMAGEMANAGER->findImage("������â")->frameRender(getMemDC(), 0, 0, buyFrameX, 0);
		FONTMANAGER->drawInt(getMemDC(), 1150, 65, 36, 255, 255, 255, "Perfect DOS VGA 437", true, (char*)SAVEMANAGER->getPlayerGold());
	}
	if (uiOn[2])
	{
		IMAGEMANAGER->findImage("��������â")->frameRender(getMemDC(), 0, 0, buyFrameX, 0);
		FONTMANAGER->drawInt(getMemDC(), 1150, 65, 36, 255, 255, 255, "Perfect DOS VGA 437", true, (char*)SAVEMANAGER->getPlayerGold());
	}
	IMAGEMANAGER->findImage("����")->frameRender(getMemDC(), 680, 496, smithFrameX, 0);
	IMAGEMANAGER->findImage("������")->frameRender(getMemDC(), 925, 517, magicianFrameX, 0);
	IMAGEMANAGER->findImage("��ų����")->frameRender(getMemDC(), 480, 505, skillFrameX, 0);
#pragma endregion

	item->render();
	unit->playerRender();

	IMAGEMANAGER->findImage("���ĺ�")->alphaRender(getMemDC(), 0, 0, bgAlpha);

}

// �������� �ϳ��� �ϼ�..

// �ϼ�
// �������� ���� �ϳ�(���̾�α�)

// �̿ϼ�
// �ʹ� ���̾�α�, ���� Ÿ�� ���, �÷��̾� �� �浹, ���� �ö󰡴� ��, ����-> ������ �̵� ��
// ���� �ƾ�, ���� �Ѹ��� ��, ����, ����, ���θ޴� ����
