#include "Stdafx.h"
#include "Unit.h"

HRESULT Unit::init(void)
{
	playerInit();
	enemyInit();
	bossVomitInit();
	BelphegorInit();
	CrocellInit();
	AncientWormInit();
	LeviathanInit();

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
	bossVomitUpdate();
	BelphegorUpdate();
	CrocellUpdate();
	AncientWormUpdate();
	LeviathanUpdate();

	worldTimeCount++;
}

void Unit::render(void)
{
	enemyRender();
	bossVomitRender();
	playerRender();
	BelphegorRender();
	CrocellRender();
	AncientWormRender();
	LeviathanRender();

}