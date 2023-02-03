#include "Stdafx.h"
#include "StartScene.h"

HRESULT StartScene::init(void)
{    
    worldTimeCount = startFrameX = startThunderFrameX = 0;
    loopBg1 = loopBg2 = 0;

    startTime = PressAnyKey = 0;
    thunder = false;
    return S_OK;
}

void StartScene::release(void)
{
}

void StartScene::update(void)
{
    worldTimeCount++;
    if (worldTimeCount % 40 == 0) startFrameX++;
    if (startFrameX > IMAGEMANAGER->findImage("����")->getMaxFrameX()) startFrameX = 0;

    if (worldTimeCount % 17 == 0) PressAnyKey++;
    if (PressAnyKey > IMAGEMANAGER->findImage("�ѱ����")->getMaxFrameX()) PressAnyKey = 0;

    startTime++;
    if (startTime >= 580 && !thunder)
    {
        thunder = true;
    }

    if (thunder)
    {
        if (worldTimeCount % 7 == 0) startThunderFrameX++;
        if (startThunderFrameX >= IMAGEMANAGER->findImage("����_����")->getMaxFrameX()) startThunderFrameX = 4;
        if (startThunderFrameX >= IMAGEMANAGER->findImage("����_������")->getMaxFrameX()) startThunderFrameX = 4;

        if (startThunderFrameX == 4)
        {
            if (startTime > 611)
            {
                startTime = 0;
                startThunderFrameX = 0;
            }
            thunder = false;
        }
    }

    if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
    {
        SCENEMANAGER->changeScene("��Ʋ��");
    }

    loopBg1 += 0.5f;
    loopBg2 += 1.0f;
}

void StartScene::render(void)
{
    IMAGEMANAGER->findImage("����")->frameRender(getMemDC(), 0, 0, startFrameX, 0);

    if (thunder)
    {
        IMAGEMANAGER->findImage("����_����")->frameRender(getMemDC(), 100, 50, startThunderFrameX, 0);
        IMAGEMANAGER->findImage("����_������")->frameRender(getMemDC(), 1050, 50, startThunderFrameX, 0);
    }
    if (startTime == 600) IMAGEMANAGER->findImage("ȭ��Ʈ")->render(getMemDC(), 0, 0);
    if (startTime == 610) IMAGEMANAGER->findImage("ȭ��Ʈ")->render(getMemDC(), 0, 0);

    IMAGEMANAGER->findImage("����_��")->loopRender(getMemDC(), &RectMake(0, 0, 1287, 237), loopBg1, 0);
    IMAGEMANAGER->findImage("����_�Ʒ�")->loopRender(getMemDC(), &RectMake(0, 563, 1287, 237), loopBg2, 0);
    IMAGEMANAGER->findImage("����")->render(getMemDC(), 165, 85);
    IMAGEMANAGER->findImage("�ѱ����")->frameRender(getMemDC(), 430, 610, PressAnyKey, 0);


}
