#pragma once
#include "GameNode.h"

enum PLAYER_STATE
{
	P_WALK,
	P_STAND,
	P_JUMP,
	P_ATTACK,
	P_DEAL,					// ������ ���ݹ���
	P_SITDOWN,
	P_SITDOWNATTACK,		// ���� ä�� ����
	P_SITDOWNDEAL,			// ������ ���� ä�� ���ݹ���
	P_FRONT,				// ���� ����
	P_DIE
};

enum ENEMY_STATE
{
	E_WALK,
	E_JUMP,
	E_ATTACK,
	E_DEAL,					// �÷��̾�� ���ݹ���
	E_DIE
};

struct PlayerStruct
{
	float X, Y, Speed, Gravity;		// ��ġ/�߷�

	RECT Rc;				// ��Ʈ
	RECT AttackRc;			// ���ݷ�Ʈ
	PLAYER_STATE State;		// enum
	int FrameX;				// ������
	int FrameY;				
	int JumpFrameX;			
	int AttackFrameX;
	int P_Hp;				// ü��
	int P_Mp;				// ����
	int P_Life;				// ���
	float P_Exp;			// ����ġ
	float P_Gold;			// ���
	bool Right;				// ��/��
	bool P_Jump;			// ����
	bool P_Die;				// ����
	bool P_JumpCount;		// ����Ȯ��
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
private: // �÷��̾�

	PlayerStruct player;
	EnemyStruct enemy;

	// ȭ�� ������
	float bgMove1;

	RECT playerAttackRC;

	// enum��
	int playerState;
	int EnemyState;

	// struct
	EnemyStruct enemyMoment;
	EnemyStruct bossMoment;

	int worldTimeCount;

private: // ��Ʋ��1 ��

	RECT zombieRC;
	float bgMove2;
	float zombieX, zombieY;

	int zombieFrameX, zombieFrameY;
	int zombieDieFrameX;

private: // ù��° ����
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

	// ��� �̵� ��ǥ ������
	int getBgMove(void) { return bgMove1; }

	// WorldTimeCount ������
	int getWorldTimeCount(void) { return worldTimeCount; }

	// �÷��̾� X ��ǥ ������
	float getPlayerX(void) { return player.X; }

	Unit() {}
	~Unit() {}
};