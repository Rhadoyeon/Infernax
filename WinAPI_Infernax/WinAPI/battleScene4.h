#pragma once
#include "GameNode.h"
#include "Unit.h"

class battleScene4 : public GameNode
{
private:
	int bgAlpha4;
	Unit* unit;

	float bgMove4;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	battleScene4() {}
	~battleScene4() {}

};
