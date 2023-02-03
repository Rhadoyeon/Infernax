#pragma once
#include "GameNode.h"

class StartScene : public GameNode
{
private:
	int startFrameX, startThunderFrameX;
	float loopBg1, loopBg2;
	int worldTimeCount;
	int startTime, PressAnyKey;

	bool thunder;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	StartScene() {}
	~StartScene() {}
};

