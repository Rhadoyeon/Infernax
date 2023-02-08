#pragma once
#include "GameNode.h"
#include "Unit.h"

class battleScene3 : public GameNode
{
private:
	int bgAlpha3;
	Unit* unit;

	int wallX, wallY;
	RECT Wall[15];

	float bgMove3;

	int gostFrameX, gostFrameY;

	int worldTimeCount;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	battleScene3() {}
	~battleScene3() {}

};
