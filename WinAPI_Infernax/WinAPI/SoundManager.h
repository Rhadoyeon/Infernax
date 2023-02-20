#pragma once
#include "SingletonBase.h"

#pragma region FMOD
/*
FMOD
- Sound Engine 라이브러리
- 언리얼과 유니티에는 라이센스 계약으로 기본 내장 되어있다.
ㄴ 이외의 대부분의 플랫폼에서는 사용하기 위한 선행 준비가 필요하다.
	ㄴ EX: CoCos2DX
- FMOD를 이용한 대표적인 게임
ㄴ 와우, 바이오 쇼크 등등


//여분의 채널 갯수(버퍼)
#define EXTRA_SOUND_CHANNEL 5
// 총 사운드 갯수
#define TOTAL_SOUND_CHANNEL SOUND_END + EXTRA_SOUND_CHANNEL
*/
#pragma endregion
/*
	▶ constexpr (Const Expression)
	- C++ 11에 추가된 키워드
	- 객체나 함수 앞에 붙일 수 있는 키워드로 해당 객체나 함수의 리턴 값을 "컴파일" 타임에 알 수 있다.
	(C++ 17 람다식에 적용 가능)
	- 컴파일 타임에 값이 결정되므로 함수 호출간에 템플릿 인자로 넘겨주기 아주 좋다.
	- const VS constexpr 차이점은 초기화 여부와 오류의 발견 시기
	- constexpr 변경 불가

	람다에 들어간다.

*/
constexpr auto soundBuffer = 100;
constexpr auto extraSoundChannel = 100;
constexpr auto totalSoundChannel = soundBuffer + extraSoundChannel;

using namespace FMOD;

class SoundManager : public SingletonBase <SoundManager>
{

private:
	// FMOD로 사운드를 관리해라.
	// 1. 서라운드 채널을 유지하기 위해
	// 2. 메모리 버퍼를 맞춰주기 위함
	// 기능화 되어있는 라이브러리가 들어와있다.
	// 시스템은 사운드를 켜주고 꺼주는 기능, 사운드는 기본적인 기능(재생, 반복, 일시정지) 뿐이다.
	// 소리를 관리하기 위해선 우리의 코드로 관리해줘야한다.
	// 사운드는 360도의 정방향으로 할 수있도록 하는데
	// 왼쪽에서 오른쪽으로 소리나게 하기위한 기능을 위해 channel이 들어왔다.
	// 코드적으로 제어하기 위해, 소리를 어디서 나게 하기 위해 Channel이 필요

	System* _system;
	Sound** _sound;
	Channel** _channel;
	// 더블포인터 쓰는 이유: 회사의 자산이 되는 부분인 cpp는 가려놨기 때문에 더블포인터를 사용하여 넘어가서 사용

	typedef map<string, Sound**> arrSounds;
	typedef map<string, Sound**>::iterator arrSoundIter;
	typedef map<string, Channel**> arrChannels;
	typedef map<string, Channel**>::iterator arrChannelIter;

	arrSounds _mTotalSounds;

public:
	HRESULT init(void);
	void release(void);
	void update(void);

	void addSound(string keyName, string soundName, bool backGround, bool loop);
	void play(string keyName, float volume);
	void stop(string keyName);
	void pause(string keyName);
	void resume(string keyName);

	bool isPlaySound(string keyName);
	bool isPauseSound(string keyName);

	SoundManager();
	~SoundManager() {}
};

