#pragma once
#include "GameNode.h"

enum PLAYERSTATE
{
	P_WALK,
	P_STAND,
	P_JUMP,
	P_ATTACK,
	P_DEAL,				// ��ó���� ����
	P_SITDOWN,
	P_SITDOWNATTACK,	// ���� ä�� ����
	P_SITDOWNDEAL,		// ���� ä�� ��ó���� ����
	P_FRONT,			// I SEE YOU �ʰ� ���� '__' / ���麸��
	P_DIE
};

enum ENEMYSTATE
{
	E_WALK,
	E_JUMP,
	E_ATTACK,
	E_DEAL,				// ��ó���� ����
	E_DIE
};

struct PlayerMoment
{
	int P_Hp;		// ü��
	int P_Mp;		// ����
	int P_Life;		// ���
	float P_Exp;	// ����ġ
	float P_Gold;	// ��
	bool P_Jump;	// ����
	bool P_Die;		// ����
};

struct EnemyMoment
{
	int E_Hp;
	bool E_Die;
};

class Unit : public GameNode
{
private: // �÷��̾�
	float bgMove;

	RECT playerRC;
	RECT playerAttackRC;
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

private: // ��Ʋ��1 ��

	RECT zombieRC;

	int zombieX, zombieY;

	int zombieFrameX, zombieFrameY;
	int zombieDieFrameX;

	//float enemySpeed;
	//bool enemyDie;

private: // ù��° ����
	RECT vomitBossRC;

	int vomitBossX, vomitBossY;

	int vomitBossFrameX, vomitBossFrameY;
	int vomitBossAttackFrameX, vomitBossAttackFrameY;

	int vomitBossDieFrameX, vomitBossDieFrameY;

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

	// ��� �̵� ��ǥ ������
	int getBgMove(void) { return bgMove; }

	// WorldTimeCount ������
	int getWorldTimeCount(void) { return worldTimeCount; }

	Unit() {}
	~Unit() {}
};