#pragma once
#include "GameNode.h"
class InvenScene : public GameNode
{
private:

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	InvenScene() {}
	~InvenScene() {}
};