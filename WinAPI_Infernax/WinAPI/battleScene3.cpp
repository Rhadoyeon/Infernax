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

#pragma region 렉트 충돌

	// 땅의 벽 1
	Wall[0] = RectMakeCenter(unit->getBgMove3() + 237, wallY + 560, 10, 147);		// 바로 앞에 벽 오른쪽1
	Wall[1] = RectMakeCenter(unit->getBgMove3() - 117, wallY + 560, 10, 147);		// 바로 앞에 벽 왼쪽2
	Wall[2] = RectMakeCenter(unit->getBgMove3() + 60, wallY + 543, 364, 100);		// 바로 앞에 벽 위3

	// 위로 올라가는 계단 2
	Wall[3] = RectMakeCenter(unit->getBgMove3() - 215, wallY + 370, 10, 46);		// 계단 1층 오른쪽
	Wall[4] = RectMakeCenter(unit->getBgMove3() - 295, wallY + 370, 10, 46);		// 계단 1층 왼쪽
	Wall[5] = RectMakeCenter(unit->getBgMove3() - 255, wallY + 390, 91, 10);		// 계단 1층 위
	Wall[6] = RectMakeCenter(unit->getBgMove3() - 255, wallY + 350, 91, 10);		// 계단 1층 아래

	// 위로 올라가는 계단 3
	Wall[7] = RectMakeCenter(unit->getBgMove3() - 396, wallY + 330, 10, 46);		// 계단 2층 오른쪽
	Wall[8] = RectMakeCenter(unit->getBgMove3() - 476, wallY + 330, 10, 46);		// 계단 2층 왼쪽
	Wall[9] = RectMakeCenter(unit->getBgMove3() - 436, wallY + 350, 91, 10);		// 계단 2층 위
	Wall[10] = RectMakeCenter(unit->getBgMove3() - 436, wallY + 310, 91, 10);		// 계단 2층 아래
	
	// 계단 벽 난간 4
	Wall[11] = RectMakeCenter(unit->getBgMove3() - 488, wallY + 224, 10, 107);		// 오른쪽
	Wall[12] = RectMakeCenter(unit->getBgMove3() - 528, wallY + 174, 91, 10);		// 위
	// 계단 벽 난간 5
	Wall[13] = RectMakeCenter(unit->getBgMove3() - 580, wallY + 103, 10, 138);		// 오른쪽
	Wall[14] = RectMakeCenter(unit->getBgMove3() - 620, wallY + 33, 92, 10);		// 위


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
			SCENEMANAGER->changeScene("배틀맵4");
		}
	}

	//worldTimeCount++;
	//if (worldTimeCount % 10 == 0) gostFrameX++;
	//if (gostFrameX > IMAGEMANAGER->findImage("벨페고르보스_스킬")->getMaxFrameX()) gostFrameX = 0;
}

void battleScene3::render(void)
{
	IMAGEMANAGER->findImage("배경1")->render(getMemDC(), unit->getBgMove3() - 1438, -194);
	IMAGEMANAGER->findImage("배경2")->render(getMemDC(), unit->getBgMove3() - 1438, -194);
	IMAGEMANAGER->findImage("전투3")->render(getMemDC(), unit->getBgMove3() - 1438, -194);

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
	//IMAGEMANAGER->findImage("귀신")->frameRender(getMemDC(), 0, 0, gostFrameX, gostFrameY);

	unit->playerRender();

	IMAGEMANAGER->findImage("알파블랙")->alphaRender(getMemDC(), 0, 0, bgAlpha3);
}
