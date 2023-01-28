#pragma once
#include "GameNode.h"

enum PLAYERSTATE
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

struct PlayerMoment
{
	int P_Hp;		// 체력
	int P_Mp;		// 마력
	int P_Life;		// 목숨
	float P_Exp;	// 경험치
	float P_Gold;	// 돈
	bool P_Jump;	// 점프
	bool P_Die;		// 죽음
};

struct EnemyMoment
{
	int E_Hp;
	bool E_Die;
};

class Unit : public GameNode
{
private: // 플레이어
	float bgMove;

	RECT playerRC;
	RECT playerAttackRC;
	RECT playerSitDownRC;
	RECT zombieRc;
	int playerState;

	PlayerMoment playerMomemt;
	EnemyMoment enemyMoment;

	int playerX, playerY;
	int playerAttackX, playerAttackY;
	int playerStandX, playerStandY;

	int playerFrameX, playerFrameY;
	int playerAttackFrameX;
	int	playerJumpFrameX;
	int playerSitDownFrameX;
	int playerStandFrameX;

	float playerSpeed, playerGravity;

	int alpha;

	int worldTimeCount;

private: // 적

	RECT enemyRC;
	int enemyX, enemyY;
	int enemyState;

	int enemyFrameX, enemyFrameY;

	int zombieX, zombieY;

	int zombieFrameX, zombieFrameY;

	//float enemySpeed;
	//bool enemyDie;

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

	// 배경 이동 좌표 접근자
	int getBgMove(void) { return bgMove; }

	// WorldTimeCount 접근자
	int getWorldTimeCount(void) { return worldTimeCount; }

	Unit() {}
	~Unit() {}
};