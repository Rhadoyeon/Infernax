#pragma once
#include "GameNode.h"
#include "Unit.h"

class battleScene : public GameNode
{
private:
	int bgMove;
	Unit* unit;

	RECT crossRC;


	int crossX, crossY;
	int crowFrameX, crowFrameY;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	battleScene() {}
	~battleScene() {}

};

