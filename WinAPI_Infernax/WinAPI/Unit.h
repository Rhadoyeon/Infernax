#pragma once
#include "GameNode.h"

enum PLAYER_STATE
{
	P_WALK,
	P_STAND,
	P_JUMP,
	P_ATTACK,
	P_DEAL,					// 적에게 공격받음
	P_SITDOWN,
	P_SITDOWNATTACK,		// 앉은 채로 공격
	P_SITDOWNDEAL,			// 적에게 앉은 채로 공격받음
	P_FRONT,				// 정면 응시
	P_DIE
};

enum ENEMY_STATE
{
	E_WALK,
	E_JUMP,
	E_ATTACK,
	E_DEAL,					// 플레이어에게 공격받음
	E_DIE
};

struct PlayerStruct
{
	float X, Y, Speed, Gravity;		// 위치/중력

	RECT Rc;				// 렉트
	RECT AttackRc;			// 공격렉트
	PLAYER_STATE State;		// enum
	int FrameX;				// 프레임
	int FrameY;				
	int JumpFrameX;			
	int AttackFrameX;
	int P_Hp;				// 체력
	int P_Mp;				// 마력
	int P_Life;				// 목숨
	float P_Exp;			// 경험치
	float P_Gold;			// 골드
	bool Right;				// 좌/우
	bool P_Jump;			// 점프
	bool P_Die;				// 죽음
	bool P_JumpCount;		// 점프확인
};

struct EnemyStruct
{
	ENEMY_STATE State;

	int E_Hp;
	bool E_Die;
	bool E_Right;

	int BV_Hp;
	bool BV_Die;
	bool BV_Right;
};

class Unit : public GameNode
{
private: // 플레이어

	PlayerStruct player;
	EnemyStruct enemy;

	// 화면 움직임
	float bgMove1;

	RECT playerAttackRC;

	// enum문
	int playerState;
	int EnemyState;

	// struct
	EnemyStruct enemyMoment;
	EnemyStruct bossMoment;

	int worldTimeCount;

private: // 배틀씬1 적

	RECT zombieRC;
	float bgMove2;
	float zombieX, zombieY;

	int zombieFrameX, zombieFrameY;
	int zombieDieFrameX;

private: // 첫번째 보스
	RECT vomitBossRC;
	RECT vomitBossTwoRC;

	float vomitBossX, vomitBossY;

	int vomitBossFrameX, vomitBossFrameY;
	int vomitBossAttackFrameX, vomitBossAttackFrameY;
	int vomitBossFireFrameX, vomitBossFireFrameY;

	int vomitBossDieFrameX1, vomitBossDieFrameX2;

	int vomitBossFireTime;
	int vomitBossFireStart;
	int vomitBossFireEndTime;
	bool vomitBossFireBoss;
	bool vomitBossFireEnd;

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