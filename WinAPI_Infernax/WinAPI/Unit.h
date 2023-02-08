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
	float X, Y, Speed, Gravity;		// 위치/중력

	RECT Rc;				// 렉트
	RECT UpRc;
	RECT DownRc;
	RECT LeftRc;
	RECT RightRc;
	RECT AttackRc;			// 공격렉트

	PLAYER_STATE State;		// enum
	PLAYER_INVEN Inven;
	int FrameX, FrameY;		// 프레임
	int JumpFrameX;			
	int AttackFrameX;
	int Hp;					// 체력
	int Mp;					// 마력
	int Life;				// 목숨
	float Exp;				// 경험치
	float Gold;				// 골드
	float moveControl;		// 움직임
	bool Right;				// 좌/우
	bool Jump;				// 점프
	bool Die;				// 죽음
	bool JumpCount;			// 점프확인
	bool Inventory;			// 인벤토리
	bool Move;				// 플레이어 움직임
	//bool MoveCheck;			// 움직임 체크

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
private: // 플레이어

	PlayerStruct player;

	// 플레이어 충돌용
	RECT playerRc[4];
	bool playerCrash[5];

	float bgMove;			// 화면 움직임
	float bgMove3;			// 화면 움직임
	int worldTimeCount;
	bool villageMove;

	RECT Wall[15];

private: // 배틀씬1 적
	EnemyStruct zombie;

private: // 첫번째 보스
	BossStruct vomitBoss;

private: // 두번째 보스
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

	// 배경 이동 좌표 접근자
	float getBgMove(void) { return bgMove; }
	float getBgMove3(void) { return bgMove3; }

	// WorldTimeCount 접근자
	int getWorldTimeCount(void) { return worldTimeCount; }

	// 플레이어 X, Y 좌표 접근자
	float getPlayerX(void) { return player.X; }
	float getPlayerY(void) { return player.Y; }
	// 플레이어 렉트 접근자
	RECT getPlayerRc(void) { return player.Rc; }
	// 플레이어 무브 접근자
	bool getPlayerMove(void) { return player.Move; }

	// 플레이어 키매니저 접근자
	//int getPlayerKeyManager(void) {return player.}

	// 렉트 충돌용 설정자
	void setWall(int num, RECT rc) 
	{
		Wall[num] = rc;
	}

	Unit() {}
	~Unit() {}
};