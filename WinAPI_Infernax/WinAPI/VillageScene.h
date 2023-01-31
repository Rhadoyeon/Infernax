#pragma once
#include "GameNode.h"
#include "Unit.h"

class VillageScene : public GameNode
{
private:
	int bgMove3;
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

