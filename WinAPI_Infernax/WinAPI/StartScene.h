#pragma once
#include "GameNode.h"

class StartScene : public GameNode
{
private:
	int startFrameX1, startFrameY1;
	float loopBg1, loopBg2;
	int worldTimeCount;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	StartScene() {}
	~StartScene() {}
};

