#pragma once
#include "GameNode.h"
#include "Unit.h"

class battleScene9 : public GameNode
{
private:
	int bgAlpha9;
	Unit* unit;

	float bgMove9;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	battleScene9() {}
	~battleScene9() {}

};
