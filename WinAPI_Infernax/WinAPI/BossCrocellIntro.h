#pragma once
#include "GameNode.h"

class BossCrocellIntro : public GameNode
{
private:
	HWND video;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	BossCrocellIntro() {}
	~BossCrocellIntro() {}
};