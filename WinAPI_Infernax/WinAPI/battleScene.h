#pragma once
#include "GameNode.h"
#include "Unit.h"

struct StructCrow
{
	float startX, startY, endX, endY, radian;
	int index;
	bool left;
};

class battleScene : public GameNode
{
private:
	int bgMove1;
	int bgAlpha1;
	Unit* unit;

	RECT crossRC;

	StructCrow crows[10];
	int crossX[10], crossY[10];
	int crowFrameX, crowFrameY;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	battleScene() {}
	~battleScene() {}

};

