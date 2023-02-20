#include "Stdafx.h"
#include "Opening.h"

HRESULT Opening::init(void)
{
    video = MCIWndCreate(_hWnd, NULL, MCIWNDF_NOPLAYBAR | WS_VISIBLE | WS_CHILD, "Resources/Video/Opening.wmv");
    MoveWindow(video, 0, 0, WINSIZE_X, WINSIZE_Y, NULL);

    MCIWndPlay(video);

    return S_OK;
}

void Opening::release(void)
{
}

void Opening::update(void)
{
    if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
    {
        MCIWndPlay(video);
    }

    if (MCIWndGetLength(video) <= MCIWndGetPosition(video))
    {
        MCIWndClose(video);
        MCIWndDestroy(video);
        SCENEMANAGER->changeScene("πË∆≤∏ ");
    }

    if (KEYMANAGER->isOnceKeyDown(VK_RETURN) || KEYMANAGER->isOnceKeyDown(VK_SPACE))
    {
        MCIWndStop(video);
        MCIWndClose(video);
        MCIWndDestroy(video);
        SCENEMANAGER->changeScene("πË∆≤∏ ");
    }
}

void Opening::render(void)
{
}