#pragma once
#include "GameNode.h"
#include "Unit.h"

class battleScene7 : public GameNode
{
private:
	int bgAlpha7;
	Unit* unit;

	float bgMove7;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	battleScene7() {}
	~battleScene7() {}

};
