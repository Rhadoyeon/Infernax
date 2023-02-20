#pragma once
#include "GameNode.h"

class BossLycanthropeIntro : public GameNode
{
private:
	HWND video;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	BossLycanthropeIntro() {}
	~BossLycanthropeIntro() {}
};