#include "Stdafx.h"
#include "BossLeviathanIntro.h"

HRESULT BossLeviathanIntro::init(void)
{
    video = MCIWndCreate(_hWnd, NULL, MCIWNDF_NOPLAYBAR | WS_VISIBLE | WS_CHILD, "Resources/Video/BossLeviathan.wmv");
    MoveWindow(video, 0, 0, WINSIZE_X, WINSIZE_Y, NULL);

    MCIWndPlay(video);

    return S_OK;
}

void BossLeviathanIntro::release(void)
{
}

void BossLeviathanIntro::update(void)
{
    if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
    {
        MCIWndPlay(video);
    }

    if (MCIWndGetLength(video) <= MCIWndGetPosition(video))
    {
        MCIWndClose(video);
        MCIWndDestroy(video);
        SCENEMANAGER->changeScene("??Ʋ??8");
    }

    if (KEYMANAGER->isOnceKeyDown(VK_RETURN) || KEYMANAGER->isOnceKeyDown(VK_SPACE))
    {
        MCIWndStop(video);
        MCIWndClose(video);
        MCIWndDestroy(video);
        SCENEMANAGER->changeScene("??Ʋ??8");
    }
}

void BossLeviathanIntro::render(void)
{
}