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
        if (mainFrameX > IMAGEMANAGER->findImage("����ϱ�")->getMaxFrameX()) mainFrameX = 1;

    }

    if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
    {
        mainFrameX = 0;
        //if (mainFrameX > IMAGEMANAGER->findImage("����ϱ�")->getMaxFrameX()) mainFrameX = 1;
    }

    if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
    {
        menu = SETTING;
        IMAGEMANAGER->findImage("���Ӽ���");
    }

    if (KEYMANAGER->isOnceKeyDown(VK_BACK))
    {
        menu = CONTINUE;
        IMAGEMANAGER->findImage("���Ӽ���");
    }


    if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
    {
        SCENEMANAGER->changeScene("��Ʋ��");
    }

    settingRc = RectMakeCenter(mainX, mainY, 100, 100);

}

void MainMenu::render(void)
{
    if (menu == CONTINUE)
    {
        IMAGEMANAGER->findImage("���Ӽ���")->render(getMemDC(), 0, 0);
        IMAGEMANAGER->findImage("����ϱ�")->frameRender(getMemDC(), settingRc.left + 130, settingRc.top + 220, mainFrameX, mainFrameY);
        IMAGEMANAGER->findImage("����")->frameRender(getMemDC(), settingRc.left + 130, settingRc.top + 280, mainFrameX, mainFrameY);
    }
    if (menu == SETTING)
    {
        IMAGEMANAGER->findImage("���Ӽ���")->render(getMemDC(), 230, 100);
        IMAGEMANAGER->findImage("�����")->frameRender(getMemDC(), settingRc.left + 340, settingRc.top + 260, mainFrameX, mainFrameY);
    }
    //IMAGEMANAGER->findImage("���ÿ�����Ʈ")->render(getMemDC(), settingRc.left + 100, settingRc.top + 225);


}
