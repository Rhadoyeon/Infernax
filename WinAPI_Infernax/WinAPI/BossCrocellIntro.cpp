#include "Stdafx.h"
#include "BossCrocellIntro.h"

HRESULT BossCrocellIntro::init(void)
{
    video = MCIWndCreate(_hWnd, NULL, MCIWNDF_NOPLAYBAR | WS_VISIBLE | WS_CHILD, "Resources/Video/BossCrocell.wmv");
    MoveWindow(video, 0, 0, WINSIZE_X, WINSIZE_Y, NULL);

    MCIWndPlay(video);

    return S_OK;
}

void BossCrocellIntro::release(void)
{
}

void BossCrocellIntro::update(void)
{
    if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
    {
        MCIWndPlay(video);
    }

    if (MCIWndGetLength(video) <= MCIWndGetPosition(video))
    {
        MCIWndClose(video);
        MCIWndDestroy(video);
        SCENEMANAGER->changeScene("πË∆≤∏ 6");
    }

    if (KEYMANAGER->isOnceKeyDown(VK_RETURN) || KEYMANAGER->isOnceKeyDown(VK_SPACE))
    {
        MCIWndStop(video);
        MCIWndClose(video);
        MCIWndDestroy(video);
        SCENEMANAGER->changeScene("πË∆≤∏ 6");
    }
}

void BossCrocellIntro::render(void)
{
}