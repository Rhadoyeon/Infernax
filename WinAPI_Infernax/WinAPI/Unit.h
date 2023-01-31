#pragma once
#include "GameNode.h"

enum PLAYER_STATE
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

struct PlayerStruct
{
	float X, Y, Speed, Gravity;
	RECT Rc;			// ��Ʈ
	RECT AttackRc;		// ���ݷ�Ʈ
	PLAYER_STATE State;	// enum
	int FrameX;			// ������
	int FrameY;			// ������
	int JumpFrameX;		// ������
	int P_Hp;			// ü��
	int P_Mp;			// ����
	int P_Life;			// ���
	float P_Exp;		// ����ġ
	float P_Gold;		// ���
	bool Right;			// ��/��
	bool P_Jump;		// ����
	bool P_Die;			// ����
	bool P_JumpCount;	// ����Ȯ��
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
private: // �÷��̾�

	PlayerStruct player;

	// ȭ�� ������
	float bgMove1;

	RECT playerRC;
	RECT playerAttackRC;

	// enum��
	int playerState;
	int EnemyState;

	// struct
	//PlayerMoment playerMomemt;
	EnemyMoment enemyMoment;
	EnemyMoment bossMoment;

	//float playerX, playerY;
	float playerAttackX, playerAttackY;
	float playerStandX, playerStandY;

	// ������
	int playerFrameX, playerFrameY;
	int playerAttackFrameX;
	int	playerJumpFrameX;
	int playerSitDownFrameX;
	int playerStandFrameX;

	// �÷��̾� ����
	float playerSpeed, playerGravity;

	// ȭ�� ����
	int alpha;

	int worldTimeCount;

private: // ��Ʋ��1 ��

	RECT zombieRC;
	float bgMove2;
	float zombieX, zombieY;

	int zombieFrameX, zombieFrameY;
	int zombieDieFrameX;

	//float enemySpeed;
	//bool enemyDie;

private: // ù��° ����
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

	// ��� �̵� ��ǥ ������
	int getBgMove(void) { return bgMove1; }

	// WorldTimeCount ������
	int getWorldTimeCount(void) { return worldTimeCount; }

	// �÷��̾� X ��ǥ ������
	float getPlayerX(void) { return player.X; }

	Unit() {}
	~Unit() {}
};