#pragma once
#include "GameNode.h"

class Opening : public GameNode
{
private:
	HWND video;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	Opening() {}
	~Opening() {}
};