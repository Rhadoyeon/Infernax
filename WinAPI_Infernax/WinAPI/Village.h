#pragma once
#include "GameNode.h"
class Village : public GameNode
{
private:

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	Village() {}
	~Village() {}
};

