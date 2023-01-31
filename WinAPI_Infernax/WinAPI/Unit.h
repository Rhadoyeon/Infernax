#pragma once
#include "GameNode.h"

enum PLAYER_STATE
{
	P_WALK,
	P_STAND,
	P_JUMP,
	P_ATTACK,
	P_DEAL,				// 상처받음 힝힝
	P_SITDOWN,
	P_SITDOWNATTACK,	// 앉은 채로 공격
	P_SITDOWNDEAL,		// 앉은 채로 상처받음 힝힝
	P_FRONT,			// I SEE YOU 너가 보여 '__' / 정면보기
	P_DIE
};

enum ENEMYSTATE
{
	E_WALK,
	E_JUMP,
	E_ATTACK,
	E_DEAL,				// 상처받음 힝힝
	E_DIE
};

struct PlayerStruct
{
	float X, Y, Speed, Gravity;
	RECT Rc;			// 렉트
	RECT AttackRc;		// 공격렉트
	PLAYER_STATE State;	// enum
	int FrameX;			// 프레임
	int FrameY;			// 프레임
	int JumpFrameX;		// 프레임
	int P_Hp;			// 체력
	int P_Mp;			// 마력
	int P_Life;			// 목숨
	float P_Exp;		// 경험치
	float P_Gold;		// 골드
	bool Right;			// 좌/우
	bool P_Jump;		// 점프
	bool P_Die;			// 죽음
	bool P_JumpCount;	// 점프확인
};

struct EnemyMoment
{
	int E_Hp;
	bool E_Die;
	int BV_Hp;
	bool BV_Die;

};

class Unit : public GameNode
{
private: // 플레이어

	PlayerStruct player;

	// 화면 움직임
	float bgMove1;

	RECT playerRC;
	RECT playerAttackRC;

	// enum문
	int playerState;
	int EnemyState;

	// struct
	//PlayerMoment playerMomemt;
	EnemyMoment enemyMoment;
	EnemyMoment bossMoment;

	//float playerX, playerY;
	float playerAttackX, playerAttackY;
	float playerStandX, playerStandY;

	// 프레임
	int playerFrameX, playerFrameY;
	int playerAttackFrameX;
	int	playerJumpFrameX;
	int playerSitDownFrameX;
	int playerStandFrameX;

	// 플레이어 점프
	float playerSpeed, playerGravity;

	// 화면 알파
	int alpha;

	int worldTimeCount;

private: // 배틀씬1 적

	RECT zombieRC;
	float bgMove2;
	float zombieX, zombieY;

	int zombieFrameX, zombieFrameY;
	int zombieDieFrameX;

	//float enemySpeed;
	//bool enemyDie;

private: // 첫번째 보스
	RECT vomitBossRC;
	RECT vomitBossTwoRC;

	float vomitBossX, vomitBossY;

	int vomitBossFrameX, vomitBossFrameY;
	int vomitBossAttackFrameX, vomitBossAttackFrameY;
	int vomitBossFireFrameX, vomitBossFireFrameY;

	int vomitBossDieFrameX, vomitBossDieFrameY;

	bool _fireBoss;
	int _fireTime;
	int _fireStart;
	int _fireEndTime;
	bool _fireEnd;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void playerInit(void);
	void playerUpdate(void);
	void playerRender(void);

	void enemyInit(void);
	void enemyUpdate(void);
	void enemyRender(void);

	void bossVomitInit(void);
	void bossVomitUpdate(void);
	void bossVomitRender(void);

	// 배경 이동 좌표 접근자
	int getBgMove(void) { return bgMove1; }

	// WorldTimeCount 접근자
	int getWorldTimeCount(void) { return worldTimeCount; }

	// 플레이어 X 좌표 접근자
	float getPlayerX(void) { return player.X; }

	Unit() {}
	~Unit() {}
};