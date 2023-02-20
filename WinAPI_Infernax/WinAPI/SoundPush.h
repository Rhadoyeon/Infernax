#pragma once
#include "GameNode.h"

class SoundPush : public GameNode
{
private:
	int _index;

	float _volume;

	bool play;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	SoundPush() {}
	~SoundPush() {}
};

