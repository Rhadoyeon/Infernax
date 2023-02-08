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

	// ������
	ItemSkill* item;

	int worldTimeCount;
	int smithFrameX;
	int magicianFrameX;
	int skillFrameX;
	int buyFrameX;

	int bgAlpha;
	
	int sellNum; // ���� ������ ��ȣ
	bool uiOn[3]; // �� ui ������?
	bool isSell;  // true ����, false ���� x

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	ShopScene() {}
	~ShopScene() {}

};

