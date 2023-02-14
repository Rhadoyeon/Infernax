#pragma once
#include "GameNode.h"
#include "Unit.h"

class battleScene6 : public GameNode
{
private:
	int bgAlpha6;
	Unit* unit;

	float bgMove6;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	battleScene6() {}
	~battleScene6() {}

};
