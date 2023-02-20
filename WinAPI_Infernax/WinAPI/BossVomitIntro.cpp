#include "Stdafx.h"
#include "BossVomitIntro.h"

HRESULT BossVomitIntro::init(void)
{
    video = MCIWndCreate(_hWnd, NULL, MCIWNDF_NOPLAYBAR | WS_VISIBLE | WS_CHILD, "Resources/Video/BossVomit.wmv");
    MoveWindow(video, 0, 0, WINSIZE_X, WINSIZE_Y, NULL);

    MCIWndPlay(video);

    return S_OK;
}

void BossVomitIntro::release(void)
{
}

void BossVomitIntro::update(void)
{
    if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
    {
        MCIWndPlay(video);
    }

    if (MCIWndGetLength(video) <= MCIWndGetPosition(video))
    {
        MCIWndClose(video);
        MCIWndDestroy(video);
        SCENEMANAGER->changeScene("��Ʋ��2");
    }

    if (KEYMANAGER->isOnceKeyDown(VK_RETURN) || KEYMANAGER->isOnceKeyDown(VK_SPACE))
    {
        MCIWndStop(video);
        MCIWndClose(video);
        MCIWndDestroy(video);
        SCENEMANAGER->changeScene("��Ʋ��2");
    }
}

void BossVomitIntro::render(void)
{
}