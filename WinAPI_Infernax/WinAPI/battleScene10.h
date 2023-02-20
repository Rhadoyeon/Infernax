#pragma once
#include "GameNode.h"
#include "Unit.h"

class battleScene10 : public GameNode
{
private:
	int bgAlpha10;
	Unit* unit;

	float bgMove10;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	battleScene10() {}
	~battleScene10() {}

};
