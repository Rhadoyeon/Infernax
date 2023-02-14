#pragma once
#include "GameNode.h"
#include "Unit.h"

class battleScene8 : public GameNode
{
private:
	int bgAlpha8;
	Unit* unit;
	float bgMove8;
	//bool change;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	battleScene8() {}
	~battleScene8() {}

};
