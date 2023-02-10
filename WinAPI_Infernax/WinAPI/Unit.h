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
	E_STAND,
	E_WALK,
	E_JUMP,
	E_ATTACK,
	E_DEAL,					// �÷��̾�� ���ݹ���
	E_DIE,
	E_WEAPON,
};

enum BOSS_BELPHEGOR
{
	B_STAND,
	B_WALK,
	B_WALK2,
	B_TAKE,
	B_ATTACK,				// â ����
	B_ATTACK2,				// �ҵ��� ����
	B_DEAL,					// �÷��̾�� ���ݹ���
	B_DIE,
	B_WEAPON,
	B_SCREAM
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
	RECT UpRc;
	RECT DownRc;
	RECT LeftRc;
	RECT RightRc;
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
	float moveControl;		// ������
	bool Right;				// ��/��
	bool Jump;				// ����
	bool Die;				// ����
	bool JumpCount;			// ����Ȯ��
	bool Inventory;			// �κ��丮
	bool Move;				// �÷��̾� ������
	bool colliChkDown;

};

struct EnemyStruct	// zombie
{
	ENEMY_STATE State;
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

struct BelphegorStruct
{
	BOSS_BELPHEGOR BelphegorState;
	RECT Rc;
	RECT AttackRc;
	float X, Y;
	int FrameX, FrameY;
	int SkillFrameX, ScreamFrameX, WalkFrameX, StandFrameX;
	float BossTimeCount;

	bool Attack;		 // ������ ���� �����ΰ� �ƴѰ�
	int Count;	 // ���� �����ִ� ī��Ʈ
	int DieCount;
	bool Pattern;

	bool Die;
};

struct JavelinStruct
{
	RECT Rc;
	float X, Y;
	int FrameX, TrowFrameX, TakeFrameX, StayFrameX;
};

class Unit : public GameNode
{
private: // �÷��̾�

	PlayerStruct player;

	// �÷��̾� �浹��
	RECT playerRc[4];
	bool playerCrash[5];

	float bgMove;			// ȭ�� ������
	float bgMove3;			// ȭ�� ������
	int worldTimeCount;
	bool villageMove;

	RECT Wall[15];

private: // ��Ʋ��1 ��
	EnemyStruct zombie;

private: // ù��° ����
	BossStruct vomitBoss;

private: // �ι�° ����
	BelphegorStruct belphegor;
	JavelinStruct javelin;
	int BelphegorFrameX, BelphegorFrameY;
	// �б⺰�� ������ ������ ������Ʈ
	int ChangeBoss;
	int BossPattern;
	// ChangeBoss ���� ���� (���������� ����)
	int ChangeBossPaturn;

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

	void BelphegorInit(void);
	void BelphegorUpdate(void);
	void BelphegorRender(void);

	void setPlayerX(float X) { player.X = X; }
	void setPlayerY(float Y) { player.Y = Y; }

	void setPlayerMove(float moveControl) { player.Move = moveControl; }
	//void setPlayerMoveCheck(bool moveCheck) { player.MoveCheck = moveCheck; }
	void setPlayerDirection(bool right) { player.Right = right; }

	void setPlayerVillage(bool Move) { villageMove = Move; }

	// ��� �̵� ��ǥ ������
	float getBgMove(void) { return bgMove; }
	float getBgMove3(void) { return bgMove3; }

	// WorldTimeCount ������
	int getWorldTimeCount(void) { return worldTimeCount; }

	// �÷��̾� X, Y ��ǥ ������
	float getPlayerX(void) { return player.X; }
	float getPlayerY(void) { return player.Y; }
	// �÷��̾� ��Ʈ ������
	RECT getPlayerRc(void) { return player.Rc; }
	// �÷��̾� ���� ������
	bool getPlayerMove(void) { return player.Move; }

	// ��Ʈ �浹�� ������
	void setWall(int num, RECT rc) { Wall[num] = rc; }

	Unit() {}
	~Unit() {}
};