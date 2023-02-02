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
    if (startFrameX1 > IMAGEMANAGER->findImage("����")->getMaxFrameX()) startFrameX1 = 0;

    if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
    {
        SCENEMANAGER->changeScene("��Ʋ��");
    }
    loopBg1 += 0.1f;
    loopBg2 += 0.5f;
}

void StartScene::render(void)
{
    IMAGEMANAGER->findImage("����")->frameRender(getMemDC(), 0, 0, startFrameX1, 0);
    IMAGEMANAGER->findImage("����_��")->loopRender(getMemDC(), &RectMake(0, 0, 1287, 237), loopBg1, 0);
    IMAGEMANAGER->findImage("����_�Ʒ�")->loopRender(getMemDC(), &RectMake(0, 600, 1287, 237), loopBg2, 0);

}
