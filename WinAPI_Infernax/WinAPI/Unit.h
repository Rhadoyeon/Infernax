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

enum PLAYER_INVEN
{
	MAGIC,
	QUEST,
	CHARECTER
};

struct PlayerStruct
{
	float X, Y, Speed, Gravity;		// ��ġ/�߷�

	RECT Rc;				// ��Ʈ
	RECT AttackRc;			// ���ݷ�Ʈ
	PLAYER_STATE State;		// enum
	PLAYER_INVEN Inven;
	int FrameX, FrameY;		// ������
	int JumpFrameX;			
	int AttackFrameX;
	int Hp;					// ü��
	int Mp;					// ����
	int Life;				// ���
	float Exp;				// ����ġ
	float Gold;				// ���
	bool Right;				// ��/��
	bool Jump;				// ����
	bool Die;				// ����
	bool JumpCount;			// ����Ȯ��
	bool Inventory;			// �κ��丮
	bool Move;				// �÷��̾� ������
};

struct EnemyStruct
{
	ENEMY_STATE State;

	// zombie
	RECT Rc;
	float X, Y;
	int FrameX, FrameY;
	int DieFrameX;

	int Hp;
	bool Die;
	bool Right;
};

struct BossStruct
{
	ENEMY_STATE State;

	RECT OneRc;
	RECT TwoRc;
	float X, Y;
	int FrameX, FrameY;
	int AttackFrameX;
	int FireFrameX;
	int DieFrameX1, DieFrameX2;

	int FireTime;
	int FireStart;
	int FireEndTime;
	bool FireBoss;
	bool FireEnd;
	bool DieChange;

	int Hp;
	bool Die;
	bool Right;
};

class Unit : public GameNode
{
private: // �÷��̾�

	PlayerStruct player;
	float bgMove;			// ȭ�� ������

	int worldTimeCount;

private: // ��Ʋ��1 ��
	EnemyStruct zombie;

private: // ù��° ����
	BossStruct vomitBoss;

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

	// �÷��̾� X ��ǥ ������
	float getPlayerX(void) { return player.X; }

	bool getPlayerMove(void) { return player.Move; }

	Unit() {}
	~Unit() {}
};