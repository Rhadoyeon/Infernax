#pragma once
#include "GameNode.h"
#include "Unit.h"

class battleScene5 : public GameNode
{
private:
	int bgAlpha5;
	int alpha;
	Unit* unit;

	float bgMove5;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	battleScene5() {}
	~battleScene5() {}

};
