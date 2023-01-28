#include "Stdafx.h"
#include "SoundManager.h"

SoundManager::SoundManager() : _system(nullptr),
                               _channel(nullptr),
                               _sound(nullptr)
{
}

HRESULT SoundManager::init(void)
{
    // 사운드 시스템 생성
    System_Create(&_system);

    // 시스템 초기화
    _system->init(totalSoundChannel, FMOD_INIT_NORMAL, 0);


    // 채널 수 만큼 메모리 버퍼 및 사운드를 생성하겠다.
    // ㄴ 채널 수와 사운드 수는 맞춰 주는 것이 좋다.
    _sound = new Sound*[totalSoundChannel];
    _channel = new Channel * [totalSoundChannel];

    // 메모리 한번 밀자.
    // 크기가 매우 크기 때문에 한번 밀어줘서 최적화
    memset(_sound, 0, sizeof(Sound*) * (totalSoundChannel));
    memset(_channel, 0, sizeof(Channel*) * (totalSoundChannel));

    return S_OK;
}

void SoundManager::release(void)
{

    // 사운드 삭제
    if (_channel != nullptr || _sound != nullptr)
    {
        for (int i = 0; i < totalSoundChannel; i++)
        {
            if (_channel != nullptr)
            {
                if (_channel[i]) _channel[i]->stop();
            }

            if (_sound != nullptr)
            {
                // 재수없는 경우 방지
                // 동작하는 순간 혹시나 다른 사운드가 걸릴 수 있기 때문에 한번 더 물어본다.
                if (_sound != nullptr) _sound[i]->release();
            }
        }
    }

    SAFE_DELETE_ARRAY(_channel);
    SAFE_DELETE_ARRAY(_sound);

    // 시스템 해제
    if (_system != nullptr)
    {
        _system->release();
        _system->close();
    }

}

void SoundManager::update(void)
{
    //FMOD 시스템 갱신
    // ㄴ 사운드 시스템 업데이트
    // ㄴ 볼륨이 바뀌거나 재생이 끝난 사운드를 채널에서 빼는 등 다양한 작업을 자동으로 처리한다.
    _system->update();
}

void SoundManager::addSound(string keyName, string soundName, bool backGround, bool loop)
{
    if (loop)
    {
        if (backGround)
        {
            // stream 1대 1 매칭이 좋다.

            // fileName: 파일이름
            // FMOD_LOOP_NORMAL: 사운드를 열기위한 옵션(stream으로 들어왔기 때문)stream을 통해서 어떻게 들어오는지 알려주는 플래그
            // 0: stream을 받았을 때 성공했느냐 안했느냐(상관없기 때문에 배경음 0)
            _system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
        }
        // 효과음
        else
        {
            // sound로 가져오기 때문에 안정성은 떨어진다.
            // 동시다발적으로 사용하는 것에 좋다.
            // 동시에 여러개의 음원 재생 가능
            _system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
        }
    }

    else
    {
        _system->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSounds.size()]);
    }

    // 맵에 사운드를 키값과 하께 넣어준다.
    _mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));
}

// 프로그래스 바 + 사운드 + 이펙트 + 애니메이션 계열
// ㄴ 0.0 ~ 1.0
void SoundManager::play(string keyName, float volume)
{
    arrSoundIter iter = _mTotalSounds.begin();

    int count = 0;
    
    for (iter; iter != _mTotalSounds.end(); ++iter, count++)
    {
        if (keyName == iter->first)
        {
            //_system->playSound(FMOD_CHANNEL_FREE, _sound[count], false, &_channel[count]);

            _system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channel[count]);

            _channel[count]->setVolume(volume);

            break;
        }
    }
}

void SoundManager::stop(string keyName)
{
    arrSoundIter iter = _mTotalSounds.begin();

    int count = 0;

    for (iter; iter != _mTotalSounds.end(); ++iter, count++)
    {
        if (keyName == iter->first)
        {
            _channel[count]->stop();

            break;
        }
    }
}

void SoundManager::pause(string keyName)
{
    arrSoundIter iter = _mTotalSounds.begin();

    int count = 0;

    for (iter; iter != _mTotalSounds.end(); ++iter, count++)
    {
        if (keyName == iter->first)
        {
            _channel[count]->setPaused(true);

            break;
        }
    }

}

void SoundManager::resume(string keyName)
{
    arrSoundIter iter = _mTotalSounds.begin();

    int count = 0;

    for (iter; iter != _mTotalSounds.end(); ++iter, count++)
    {
        if (keyName == iter->first)
        {
            _channel[count]->setPaused(false);

            break;
        }
    }

}

bool SoundManager::isPlaySound(string keyName)
{
    bool isPlay;
    int count = 0;

    arrSoundIter iter = _mTotalSounds.begin();
    for (iter; iter != _mTotalSounds.end(); ++iter, count++)
    {
        if (keyName == iter->first)
        {
            _channel[count]->isPlaying(&isPlay);
            break;
        }
    }
    return isPlay;
}

bool SoundManager::isPauseSound(string keyName)
{
    bool isPause;
    int count = 0;

    arrSoundIter iter = _mTotalSounds.begin();
    for (iter; iter != _mTotalSounds.end(); ++iter, count++)
    {
        if (keyName == iter->first)
        {
            _channel[count]->isPlaying(&isPause);
            break;
        }
    }
    return isPause;
}