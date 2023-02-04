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
	unit->update();
	worldTimeCount++;
	if (worldTimeCount % 15 == 0) smithFrameX++;
	if (worldTimeCount % 200 == 0) magicianFrameX++;
	if (worldTimeCount % 35 == 0) skillFrameX++;
	if (smithFrameX > IMAGEMANAGER->findImage("����")->getMaxFrameX()) smithFrameX = 0;
	if (magicianFrameX > IMAGEMANAGER->findImage("������")->getMaxFrameX()) magicianFrameX = 0;
	if (skillFrameX > IMAGEMANAGER->findImage("��ų����")->getMaxFrameX()) skillFrameX = 0;

	shop.Rc = RectMakeCenter(685, 146, 960, 150);
}

void ShopScene::render(void)
{
	IMAGEMANAGER->findImage("�������")->render(getMemDC(), 0, -162);
	IMAGEMANAGER->findImage("����")->frameRender(getMemDC(), 700, 496, smithFrameX, 0);
	IMAGEMANAGER->findImage("������")->frameRender(getMemDC(), 930, 517, magicianFrameX, 0);
	IMAGEMANAGER->findImage("��ų����")->frameRender(getMemDC(), 500, 505, skillFrameX, 0);
	//DrawRectMake(getMemDC(), shop.Rc);
	//IMAGEMANAGER->findImage("���ĺ�")->render(getMemDC(), shop.Rc.left, shop.Rc.top);
	unit->playerRender();
}

// �������� �ϳ��� �ϼ�..
// �ʹ� ���̾�α�, ���� Ÿ�� ���, �÷��̾� �� �浹, �������� ���� �ϳ�(���̾�α�), �� �̵� �÷��̾� �߽����� �̵�, ���� �ö󰡴� ��, ����-> ������ �̵� ��
// ���� �ƾ�, ���� �Ѹ��� ��, ����, ����, ���θ޴� ����
