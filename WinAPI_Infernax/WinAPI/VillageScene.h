#pragma once
#include "GameNode.h"
#include "Unit.h"

class VillageScene : public GameNode
{
private:
	float bgMove;
	int bgAlpha3;
	Unit* unit;


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	VillageScene() {}
	~VillageScene() {}
};

