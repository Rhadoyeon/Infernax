#include "Stdafx.h"
#include "battleScene3.h"
#include "Unit.h"

HRESULT battleScene3::init(void)
{
	gostFrameX = gostFrameY = 0;
	wallX = wallY = 0;

	bgMove3 = 0;
	
	unit = new Unit;
	unit->init();

	unit->setPlayerVillage(true);
	unit->setPlayerX(1200);
    
	return S_OK;
}

void battleScene3::release(void)
{
	SAFE_DELETE(unit);
}

void battleScene3::update(void)
{
	unit->update();

#pragma region ��Ʈ �浹

	// ���� �� 1
	Wall[0] = RectMakeCenter(unit->getBgMove3() + 237, wallY + 560, 10, 147);		// �ٷ� �տ� �� ������1
	Wall[1] = RectMakeCenter(unit->getBgMove3() - 117, wallY + 560, 10, 147);		// �ٷ� �տ� �� ����2
	Wall[2] = RectMakeCenter(unit->getBgMove3() + 60, wallY + 543, 364, 100);		// �ٷ� �տ� �� ��3

	// ���� �ö󰡴� ��� 2
	Wall[3] = RectMakeCenter(unit->getBgMove3() - 215, wallY + 370, 10, 46);		// ��� 1�� ������
	Wall[4] = RectMakeCenter(unit->getBgMove3() - 295, wallY + 370, 10, 46);		// ��� 1�� ����
	Wall[5] = RectMakeCenter(unit->getBgMove3() - 255, wallY + 390, 91, 10);		// ��� 1�� ��
	Wall[6] = RectMakeCenter(unit->getBgMove3() - 255, wallY + 350, 91, 10);		// ��� 1�� �Ʒ�

	// ���� �ö󰡴� ��� 3
	Wall[7] = RectMakeCenter(unit->getBgMove3() - 396, wallY + 330, 10, 46);		// ��� 2�� ������
	Wall[8] = RectMakeCenter(unit->getBgMove3() - 476, wallY + 330, 10, 46);		// ��� 2�� ����
	Wall[9] = RectMakeCenter(unit->getBgMove3() - 436, wallY + 350, 91, 10);		// ��� 2�� ��
	Wall[10] = RectMakeCenter(unit->getBgMove3() - 436, wallY + 310, 91, 10);		// ��� 2�� �Ʒ�
	
	// ��� �� ���� 4
	Wall[11] = RectMakeCenter(unit->getBgMove3() - 488, wallY + 224, 10, 107);		// ������
	Wall[12] = RectMakeCenter(unit->getBgMove3() - 528, wallY + 174, 91, 10);		// ��
	// ��� �� ���� 5
	Wall[13] = RectMakeCenter(unit->getBgMove3() - 580, wallY + 103, 10, 138);		// ������
	Wall[14] = RectMakeCenter(unit->getBgMove3() - 620, wallY + 33, 92, 10);		// ��


	for (int i = 0; i < _countof(Wall); i++)
	{
		unit->setWall(i, Wall[i]);
	}

#pragma endregion

	if (unit->getPlayerX() <= 100)
	{
		bgAlpha3 += 2;
		if (bgAlpha3 > 255)
		{
			SCENEMANAGER->changeScene("��Ʋ��4");
		}
	}

	//worldTimeCount++;
	//if (worldTimeCount % 10 == 0) gostFrameX++;
	//if (gostFrameX > IMAGEMANAGER->findImage("���������_��ų")->getMaxFrameX()) gostFrameX = 0;
}

void battleScene3::render(void)
{
	IMAGEMANAGER->findImage("���1")->render(getMemDC(), unit->getBgMove3() - 1438, -194);
	IMAGEMANAGER->findImage("���2")->render(getMemDC(), unit->getBgMove3() - 1438, -194);
	IMAGEMANAGER->findImage("����3")->render(getMemDC(), unit->getBgMove3() - 1438, -194);

	//DrawRectMake(getMemDC(), Wall[0]);
	//DrawRectMake(getMemDC(), Wall[1]);
	//DrawRectMake(getMemDC(), Wall[2]);
	//DrawRectMake(getMemDC(), Wall[3]);
	//DrawRectMake(getMemDC(), Wall[4]);
	//DrawRectMake(getMemDC(), Wall[5]);
	//DrawRectMake(getMemDC(), Wall[6]);
	//DrawRectMake(getMemDC(), Wall[7]);
	//DrawRectMake(getMemDC(), Wall[8]);
	//DrawRectMake(getMemDC(), Wall[9]);
	//DrawRectMake(getMemDC(), Wall[10]);
	//DrawRectMake(getMemDC(), Wall[11]);
	//DrawRectMake(getMemDC(), Wall[12]);
	//DrawRectMake(getMemDC(), Wall[13]);
	//DrawRectMake(getMemDC(), Wall[14]);
	//IMAGEMANAGER->findImage("�ͽ�")->frameRender(getMemDC(), 0, 0, gostFrameX, gostFrameY);

	unit->playerRender();

	IMAGEMANAGER->findImage("���ĺ�")->alphaRender(getMemDC(), 0, 0, bgAlpha3);
}
