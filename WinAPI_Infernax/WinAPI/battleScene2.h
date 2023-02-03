#pragma once
#include "GameNode.h"
#include "Unit.h"

class battleScene2 : public GameNode
{
private:
	int bgAlpha2;
	Unit* unit;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	battleScene2() {}
	~battleScene2() {}

};

