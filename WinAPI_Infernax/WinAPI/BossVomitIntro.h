#pragma once
#include "GameNode.h"

class BossVomitIntro : public GameNode
{
private:
	HWND video;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	BossVomitIntro() {}
	~BossVomitIntro() {}
};