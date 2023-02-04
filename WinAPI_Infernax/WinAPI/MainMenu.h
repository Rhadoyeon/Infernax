#pragma once
#include "GameNode.h"

enum MAINMENU
{
	CONTINUE,
	SETTING,
	SOUND
};

class MainMenu : public GameNode
{
private:
	RECT settingRc;
	MAINMENU menu;

	float mainX, mainY;
	int mainFrameX, mainFrameY;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	MainMenu() {}
	~MainMenu() {}

};

