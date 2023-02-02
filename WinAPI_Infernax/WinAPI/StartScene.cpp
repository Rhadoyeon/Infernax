#include "Stdafx.h"
#include "StartScene.h"

HRESULT StartScene::init(void)
{    
    worldTimeCount = startFrameX1 = startFrameY1 = 0;
    loopBg1 = loopBg2 = 0;
    return S_OK;
}

void StartScene::release(void)
{
}

void StartScene::update(void)
{
    worldTimeCount++;

    if (worldTimeCount % 40 == 0) startFrameX1++;
    if (startFrameX1 > IMAGEMANAGER->findImage("시작")->getMaxFrameX()) startFrameX1 = 0;

    if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
    {
        SCENEMANAGER->changeScene("배틀맵");
    }
    loopBg1 += 0.1f;
    loopBg2 += 0.5f;
}

void StartScene::render(void)
{
    IMAGEMANAGER->findImage("시작")->frameRender(getMemDC(), 0, 0, startFrameX1, 0);
    IMAGEMANAGER->findImage("구름_위")->loopRender(getMemDC(), &RectMake(0, 0, 1287, 237), loopBg1, 0);
    IMAGEMANAGER->findImage("구름_아래")->loopRender(getMemDC(), &RectMake(0, 600, 1287, 237), loopBg2, 0);

}
