#pragma once
#include "GameNode.h"
#include "Unit.h"
#include "VillageScene.h"
#include "ItemSkill.h"

enum VILLAGE_SHOP
{
	SKILL,
	SMITH,
	SHELTER
};
struct VillageShop
{
	RECT npcRc;
	RECT Rc;
	float X, Y;
};

class ShopScene : public GameNode
{
private:
	RECT npcTemp[3];

	VillageShop shop;
	Unit* unit;
	VillageScene* village;

	// 아이템
	ItemSkill* item;

	int worldTimeCount;
	int smithFrameX;
	int magicianFrameX;
	int skillFrameX;
	int buyFrameX;

	int bgAlpha;
	
	int sellNum; // 상점 아이템 번호
	bool uiOn[3]; // 샵 ui 열었니?
	bool isSell;  // true 구매, false 구매 x

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	ShopScene() {}
	~ShopScene() {}

};

