#include "Stdafx.h"
#include "MainMenu.h"

HRESULT MainMenu::init(void)
{
    mainX, mainY = 0;

    settingRc = RectMakeCenter(mainX, mainY, 100, 100);

    menu = CONTINUE;

    mainFrameX = mainFrameY = 0;

    return S_OK;
}

void MainMenu::release(void)
{

}

void MainMenu::update(void)
{
    if (KEYMANAGER->isOnceKeyDown(VK_UP))
    {
        mainFrameX++;
        if (mainFrameX > IMAGEMANAGER->findImage("계속하기")->getMaxFrameX()) mainFrameX = 1;

    }

    if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
    {
        mainFrameX = 0;
        //if (mainFrameX > IMAGEMANAGER->findImage("계속하기")->getMaxFrameX()) mainFrameX = 1;
    }

    if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
    {
        menu = SETTING;
        IMAGEMANAGER->findImage("게임설정");
    }

    if (KEYMANAGER->isOnceKeyDown(VK_BACK))
    {
        menu = CONTINUE;
        IMAGEMANAGER->findImage("게임선택");
    }


    if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
    {
        SCENEMANAGER->changeScene("배틀맵");
    }

    settingRc = RectMakeCenter(mainX, mainY, 100, 100);

}

void MainMenu::render(void)
{
    if (menu == CONTINUE)
    {
        IMAGEMANAGER->findImage("게임선택")->render(getMemDC(), 0, 0);
        IMAGEMANAGER->findImage("계속하기")->frameRender(getMemDC(), settingRc.left + 130, settingRc.top + 220, mainFrameX, mainFrameY);
        IMAGEMANAGER->findImage("설정")->frameRender(getMemDC(), settingRc.left + 130, settingRc.top + 280, mainFrameX, mainFrameY);
    }
    if (menu == SETTING)
    {
        IMAGEMANAGER->findImage("게임설정")->render(getMemDC(), 230, 100);
        IMAGEMANAGER->findImage("오디오")->frameRender(getMemDC(), settingRc.left + 340, settingRc.top + 260, mainFrameX, mainFrameY);
    }
    //IMAGEMANAGER->findImage("선택오브젝트")->render(getMemDC(), settingRc.left + 100, settingRc.top + 225);


}
