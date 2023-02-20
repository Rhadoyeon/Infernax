#include "Stdafx.h"
#include "battleScene10.h"

HRESULT battleScene10::init(void)
{
    unit = new Unit;
    unit->init();

    unit->setPlayerX(100.0f);
    unit->setPlayerDirection(true);

    return S_OK;
}

void battleScene10::release(void)
{
    SAFE_DELETE(unit);
}

void battleScene10::update(void)
{
    //if (unit->getPlayerX() <= 30)
    //{
    //    bgAlpha10 += 2;
    //    if (bgAlpha10 > 255)
    //    {
    //        SCENEMANAGER->changeScene("배틀맵11");
    //    }
    //}

    unit->update();
}

void battleScene10::render(void)
{
    IMAGEMANAGER->findImage("늑대인간배경")->render(getMemDC(), 0, 0);
    IMAGEMANAGER->findImage("배경2")->render(getMemDC(), 0, -200);
    IMAGEMANAGER->findImage("전투5")->render(getMemDC(), 0, -280);

    unit->LycanthropeRender();
    unit->playerRender();

    IMAGEMANAGER->findImage("알파블랙")->alphaRender(getMemDC(), 0, 0, bgAlpha10);

}
