#include "Stdafx.h"
#include "Unit.h"

HRESULT Unit::init(void)
{
    playerInit();
    enemyInit();

    worldTimeCount = 0;

    return S_OK;
}

void Unit::release(void)
{
}

void Unit::update(void)
{
    playerUpdate();
    enemyUpdate();

    worldTimeCount++;
}

void Unit::render(void)
{
    enemyRender();
    playerRender();
}