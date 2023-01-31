#pragma once
#include "GameNode.h"
class VillageScene : public GameNode
{
private:
	int bgMove3;


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	VillageScene() {}
	~VillageScene() {}
};

