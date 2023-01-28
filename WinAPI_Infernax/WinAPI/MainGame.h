#pragma once
#include "GameNode.h"

class MainGame : public GameNode
{
	//사운드 이펙트와 같은거는 들어갈 수 있음
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	virtual void Images(void);

	MainGame() {}
	~MainGame() {}
};
