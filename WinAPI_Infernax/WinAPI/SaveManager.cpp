#include "Stdafx.h"
#include "SaveManager.h"

HRESULT SaveManager::init(void)
{
	_playerGold = 450;
	_playerExp = 0;
	_playerHp = 10;
	_playerMp = 10;
	_playerLife = 3;

	return S_OK;
}

void SaveManager::release(void)
{
}