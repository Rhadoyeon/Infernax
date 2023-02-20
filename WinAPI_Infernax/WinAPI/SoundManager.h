#pragma once
#include "SingletonBase.h"

#pragma region FMOD
/*
FMOD
- Sound Engine ���̺귯��
- �𸮾�� ����Ƽ���� ���̼��� ������� �⺻ ���� �Ǿ��ִ�.
�� �̿��� ��κ��� �÷��������� ����ϱ� ���� ���� �غ� �ʿ��ϴ�.
	�� EX: CoCos2DX
- FMOD�� �̿��� ��ǥ���� ����
�� �Ϳ�, ���̿� ��ũ ���


//������ ä�� ����(����)
#define EXTRA_SOUND_CHANNEL 5
// �� ���� ����
#define TOTAL_SOUND_CHANNEL SOUND_END + EXTRA_SOUND_CHANNEL
*/
#pragma endregion
/*
	�� constexpr (Const Expression)
	- C++ 11�� �߰��� Ű����
	- ��ü�� �Լ� �տ� ���� �� �ִ� Ű����� �ش� ��ü�� �Լ��� ���� ���� "������" Ÿ�ӿ� �� �� �ִ�.
	(C++ 17 ���ٽĿ� ���� ����)
	- ������ Ÿ�ӿ� ���� �����ǹǷ� �Լ� ȣ�Ⱓ�� ���ø� ���ڷ� �Ѱ��ֱ� ���� ����.
	- const VS constexpr �������� �ʱ�ȭ ���ο� ������ �߰� �ñ�
	- constexpr ���� �Ұ�

	���ٿ� ����.

*/
constexpr auto soundBuffer = 100;
constexpr auto extraSoundChannel = 100;
constexpr auto totalSoundChannel = soundBuffer + extraSoundChannel;

using namespace FMOD;

class SoundManager : public SingletonBase <SoundManager>
{

private:
	// FMOD�� ���带 �����ض�.
	// 1. ������ ä���� �����ϱ� ����
	// 2. �޸� ���۸� �����ֱ� ����
	// ���ȭ �Ǿ��ִ� ���̺귯���� �����ִ�.
	// �ý����� ���带 ���ְ� ���ִ� ���, ����� �⺻���� ���(���, �ݺ�, �Ͻ�����) ���̴�.
	// �Ҹ��� �����ϱ� ���ؼ� �츮�� �ڵ�� ����������Ѵ�.
	// ����� 360���� ���������� �� ���ֵ��� �ϴµ�
	// ���ʿ��� ���������� �Ҹ����� �ϱ����� ����� ���� channel�� ���Դ�.
	// �ڵ������� �����ϱ� ����, �Ҹ��� ��� ���� �ϱ� ���� Channel�� �ʿ�

	System* _system;
	Sound** _sound;
	Channel** _channel;
	// ���������� ���� ����: ȸ���� �ڻ��� �Ǵ� �κ��� cpp�� �������� ������ ���������͸� ����Ͽ� �Ѿ�� ���

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

