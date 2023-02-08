#pragma once
#include "SingletonBase.h"

class SaveManager : public SingletonBase<SaveManager>
{
private:
	int _playerGold;
	int _playerExp;
	int _playerHp;
	int _playerMp;
	int _playerLife;

public:
	HRESULT init(void);
	void release(void);

	int getPlayerGold(void) { return _playerGold; }
	void setPlayerGold(int playerGold) { _playerGold = playerGold; }

	int getPlayerExp(void) { return _playerExp; }
	void setPlayerExp(int playerExp) { _playerExp = playerExp; }

	int getPlayerHp(void) { return _playerHp; }
	void setPlayerHp(int playerHp) { _playerHp = playerHp; }

	int getPlayerMp(void) { return _playerMp; }
	void setPlayerMp(int playerMp) { _playerMp = playerMp; }

	int getPlayerLife(void) { return _playerLife; }
	void setPlayerLife(int playerLife) { _playerLife = playerLife; }


	SaveManager() {}
	~SaveManager() {}
};