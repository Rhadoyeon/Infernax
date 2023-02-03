#pragma once
#include "GameNode.h"
#include "Unit.h"

class battleScene3 : public GameNode
{
private:
	int bgAlpha3;
	Unit* unit;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	battleScene3() {}
	~battleScene3() {}

};
