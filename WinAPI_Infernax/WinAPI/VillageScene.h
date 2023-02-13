#pragma once
#include "GameNode.h"
#include "Unit.h"
#include "battleScene2.h"

class VillageScene : public GameNode
{
private:

	float bgMove;
	int bgAlpha3;
	Unit* unit;
	battleScene2* _battleScene2;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//float getBgMove(void) { return bgMove; }

	VillageScene() {}
	~VillageScene() {}
};

