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

// �κ��丮
enum PLAYER_INVEN
{
	MAGIC,
	QUEST,
	CHARECTER
};

// ���� ���̸�(vomit)
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
	B_ATTACK2,				// �ȱ�
	B_ATTACK3,				// �ҵ��� ����
	B_ATTACK4,				// ������ ����
	B_ATTACK5,				// �ȱ�2
	B_DEAL,					// �÷��̾�� ���ݹ���
	B_DIE,
	B_WEAPON,
	B_SCREAM
};

enum BOSS_CROCELL
{
	C_ATTACK1,
	C_ATTACK2,
	C_DIE
};

enum BOSS_ANCIENTWORM
{
	A_ATTACK1,
	A_ATTACK2,
	A_ATTACK3,
	A_ATTACK4,
	A_DIE
};

enum BOSS_LEVIATHAN
{
	L_ATTACK1,
	L_ATTACK2,
	L_DIE
};

// �÷��̾�
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

// ���� ���̸�(vomit)
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

// ���� �����
struct BelphegorStruct
{
	BOSS_BELPHEGOR BelphegorState;
	RECT Rc;
	RECT AttackRc;
	float X, Y;
	int FrameX, FrameY;
	int SkillFrameX, ScreamFrameX, WalkFrameX, StandFrameX, KickFrameX, DieFrameX;
	float BossTimeCount;

	bool Attack;		// ������ ���� �����ΰ� �ƴѰ�
	int Count;			// ���� �����ִ� ī��Ʈ
	//int DieCount;		// ������ ī��Ʈ
	int Hp;

	//float WalkCount;

	//float Time;			// ���� Ÿ��

	//bool ChangePotal;	// ��Ż ü����
	bool Pattern;

	bool Die;
};
struct JavelinStruct
{
	RECT Rc;
	float X, Y;
	int FrameX, TrowFrameX, TakeFrameX, StayFrameX;
};
struct PotalStruct
{
	RECT Rc;
	RECT FireballRc;
	float X, Y;
	int FrameX1, FrameX2;
	int FireBallFrameX;
	int tick;
};

// ���� ũ�μ�
struct CrocellStruct
{
	BOSS_CROCELL CrocellState;
	RECT Rc;
	float X, Y;
	int SkillFrameX1, SkillFrameX2, DieFrameX;
	int Hp;

	//bool EnemyDiePatternChange;
	bool Die;
};
struct SkeletonStruct
{
	RECT Rc;
	float X, Y;
	int WalKFrame, AttackFrame;
	int Hp;

	bool Die;
};
struct CrocellBullet
{
	float X, Y;
	RECT BulletRc;
	float degree;
	bool shot;
};

// ���� ����
struct AncientWormStruct
{
	BOSS_ANCIENTWORM AncientWormState;
	RECT Rc;
	float X, Y;
	// ������, ���̾, ����
	int FrameX, FrameX1, FireballFrameX, FireballFrameX1, RockfallFrameX, DieFrameX;
	int Time, Pattern;
	int Hp;	
	float currentTime;
	float gravity;
	float rockGravity;

	bool UpDown;
	bool Die;
};
struct AncientBullet // ���̾
{
	float X, Y;
	RECT BulletRc;
	int count;
	//float degree;
	float speed;
	float gravity;
	int oneShot;
	bool shot;
};
struct AncientRockFall
{
	int X, Y;
	RECT Rc;
	int count;
	float speed;
	float gravity;
};

// ���� �����ź
struct LeviathanStruct
{
	BOSS_LEVIATHAN LeviathanState;
	RECT Rc;
	float X, Y;
	// ���, ������, ��
	int FrameX, FrameX1, FireFrameX, LaserFrameX, DieFrameX;
	int Time, Pattern;
	int Hp;
	float currentTime;
	float gravity;

	bool Down;
	bool Die;
};
struct LeviathanLaser
{
	float X, Y;
	RECT Rc;
	int LaserFrameX, LaserFrameX1;
	bool shot, change;
};

// ���� (���� & �����ź)
struct Laser
{
	float X, Y;
	RECT Rc;
	int LaserFrameX, LaserFrameX1;
	bool shot, change;
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
	//int playerJumpCheck;
	bool villageMove;

	RECT Wall[15];

private: // ��Ʋ��1 ��(����)
	EnemyStruct zombie;

private: // ù��° ����(���̸�)
	BossStruct vomitBoss;

private: // �ι�° ����(�����)
	BelphegorStruct belphegor;
	JavelinStruct javelin;
	PotalStruct potal;

	// �б⺰�� ������ ������ ������Ʈ
	int ChangeBoss;
	int BossPattern;
	// ChangeBoss ���� ���� (���������� ����)
	int ChangeBossPaturn;

private: // ����° ����(ũ�μ�)

	CrocellStruct Crocell;
	SkeletonStruct Skeleton;

	vector<CrocellBullet> vBullet;
	// �ð� �帧��� �������� ����
	float currentTime;
	int CrocellPattern;

private: // �׹�° ����(����)
	AncientWormStruct AncientWorm;
	Laser AncientWormLaser;
	AncientBullet FireBall;
	AncientRockFall RockFall;

	vector<AncientBullet> vABullet;
	vector<AncientBullet>::iterator viABullet;
	vector<AncientRockFall> vRock;

	int RedOceanFrame;
	int bulletCount;

private: // �ټ���° ����(�����ź)
	LeviathanStruct Leviathan;
	Laser LeviathanLaser;

	int BlueOceanFrame;

private: // ������° ����(�����ΰ�)

private: // �ϰ���° ����(��������)

private: // ������° ����(���� or ���Ҹ� or ������ ���� or ����ü(�� ��ũ))

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
	//void BelphegorPattern(void);

	void CrocellInit(void);
	void CrocellUpdate(void);
	void CrocellRender(void);
	//##
	void CrocellSkeletonReset(void);

	void AncientWormInit(void);
	void AncientWormUpdate(void);
	void AncientWormRender(void);

	void LeviathanInit(void);
	void LeviathanUpdate(void);
	void LeviathanRender(void);

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