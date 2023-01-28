#include "Stdafx.h"
#include "StartScene.h"

HRESULT StartScene::init(void)
{
    IMAGEMANAGER->addFrameImage("����", "Resources/Images/Background/StartScene.bmp", 0.0f, 0.0f, 5120, 800, 4, 1, true, RGB(255, 0, 255));
    
    worldTimeCount = startFrameX1 = startFrameY1 = 0;
    
    return S_OK;
}

void StartScene::release(void)
{
}

void StartScene::update(void)
{
    worldTimeCount++;

    if (worldTimeCount % 30 == 0) startFrameX1++;
    if (startFrameX1 > IMAGEMANAGER->findImage("����")->getMaxFrameX()) startFrameX1 = 0;

    if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
    {
        SCENEMANAGER->changeScene("��Ʋ��");
    }

}

void StartScene::render(void)
{
    IMAGEMANAGER->frameRender("����", getMemDC(), 0, 0, startFrameX1, 0);

    //FONTMANAGER->drawText(getMemDC(),100,100,"����",70,30,"���Ȯ��",strlen("���Ȯ��"),RGB(255,255,0));
    //LPCWSTR str = L"�� ������ ����غ��ô�.\0"; //const wchar* �迭�� �����͸� ����
}
