#pragma once
#include "GameNode.h"

class MainGame : public GameNode
{
	//���� ����Ʈ�� �����Ŵ� �� �� ����
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	virtual void Images(void);

	MainGame() {}
	~MainGame() {}
};
