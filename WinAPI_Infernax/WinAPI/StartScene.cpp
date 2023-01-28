#include "Stdafx.h"
#include "StartScene.h"

HRESULT StartScene::init(void)
{
    IMAGEMANAGER->addFrameImage("시작", "Resources/Images/Background/StartScene.bmp", 0.0f, 0.0f, 5120, 800, 4, 1, true, RGB(255, 0, 255));
    
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
    if (startFrameX1 > IMAGEMANAGER->findImage("시작")->getMaxFrameX()) startFrameX1 = 0;

    if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
    {
        SCENEMANAGER->changeScene("배틀맵");
    }

}

void StartScene::render(void)
{
    IMAGEMANAGER->frameRender("시작", getMemDC(), 0, 0, startFrameX1, 0);

    //FONTMANAGER->drawText(getMemDC(),100,100,"돋움",70,30,"출력확인",strlen("출력확인"),RGB(255,255,0));
    //LPCWSTR str = L"이 문장을 출력해봅시다.\0"; //const wchar* 배열로 데이터를 저장
}
