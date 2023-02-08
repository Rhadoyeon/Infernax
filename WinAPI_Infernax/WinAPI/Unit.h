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
	E_DIE,
	E_WEAPON
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
	//bool MoveCheck;			// ������ üũ

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
	ENEMY_STATE BelphegorState;
	RECT Rc;
	RECT JavelinRc;
	float X, Y;
	float JavelinX, JavelinY;
	int FrameX, FrameY;
	int SkillFrameX, JavelinFrameX, JavelinTrowFrameX;
	bool Die;
	bool weaponGun;
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
	int BelphegorFrameX, BelphegorFrameY;

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

	// �÷��̾� Ű�Ŵ��� ������
	//int getPlayerKeyManager(void) {return player.}

	// ��Ʈ �浹�� ������
	void setWall(int num, RECT rc) 
	{
		Wall[num] = rc;
	}

	Unit() {}
	~Unit() {}
};