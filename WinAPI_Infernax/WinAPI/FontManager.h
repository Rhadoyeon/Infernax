#pragma once
#include "SingletonBase.h"

class FontManager : public SingletonBase<FontManager>
{
public:
	void drawText(HDC hdc, int posX, int posY,
		int textSize, int r, int g, int b, char* txtStyle, bool txtBold, char* str);

	void drawInt(HDC hdc, int posX, int posY,
		int textSize, int r, int g, int b, char* txtStyle, bool txtBold, char* str);
	FontManager() {}
	~FontManager() {}
};

