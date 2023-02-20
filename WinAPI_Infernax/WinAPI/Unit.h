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

// 인벤토리
enum PLAYER_INVEN
{
	MAGIC,
	QUEST,
	CHARECTER
};

// 1번째 보스 파이몬(vomit)
enum ENEMY_STATE
{
	E_WALK,
	E_ATTACK,	// 불쏘기
	E_DIE
};
// 2번째
enum BOSS_BELPHEGOR
{
	B_STAND,
	B_WALK,		// 창 X 걷기
	B_WALK2,	// 창 O 걷기
	B_TAKE,		// 창 가져가기
	B_ATTACK,	// 창 공격
	B_ATTACK2,	// 걷기
	B_ATTACK3,	// 불덩이 공격
	B_ATTACK4,	// 발차기 공격
	B_ATTACK5,	// 걷기2
	B_DEAL,		// 플레이어에게 공격받음
	B_SCREAM,	// 소리치고 포탈소환
	B_DIE
};
// 3번째
enum BOSS_CROCELL
{
	C_ATTACK1,	// 좀비소환
	C_ATTACK2,	// 총알
	C_DIE
};
// 4번째
enum BOSS_ANCIENTWORM
{
	A_ATTACK1,	// 대기
	A_ATTACK2,	// 레이저
	A_ATTACK3,	// 화염구
	A_ATTACK4,	// 낙석
	A_DIE
};
// 5번째
enum BOSS_LEVIATHAN
{
	L_STAY,	   // 대기
	L_ATTACK1, // 화염 오른쪽
	L_ATTACK2, // 화염 왼쪽
	L_ATTACK3, // 레이저 오른쪽
	L_ATTACK4, // 레이저 왼쪽
	L_DOWN,	   // 입수
	L_UP,	   // 올라오기
	L_DIE
};
// 6번째
enum BOSS_LYCANTHROPE
{
	LT_WALK,		// 걷기
	LT_ATTACK1,		// 크게 할퀴기
	LT_ATTACK2,		// 연속 할퀴기
	LT_JUMPATTACK,	// 점프
	LT_DIE
};

// 플레이어
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
	bool colliChkDown;

};

// 보스 파이몬(vomit) 1번째
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

// 보스 벨페고르 2번째
struct BelphegorStruct
{
	BOSS_BELPHEGOR BelphegorState;
	RECT Rc;
	RECT AttackRc;
	float X, Y;
	int FrameX, FrameY;
	int SkillFrameX, ScreamFrameX, WalkFrameX, StandFrameX, KickFrameX, DieFrameX;
	float BossTimeCount;

	bool Attack;		// 보스가 공격 상태인가 아닌가
	int Count;			// 패턴 나눠주는 카운트
	//int DieCount;		// 죽음의 카운트
	int Hp;

	//float WalkCount;

	//float Time;			// 전역 타임

	//bool ChangePotal;	// 포탈 체인지
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

// 보스 크로셀 3번째
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

// 보스 고대웜 4번째
struct AncientWormStruct
{
	BOSS_ANCIENTWORM AncientWormState;
	RECT Rc;
	float X, Y;
	// 레이저, 파이어볼, 낙석
	int FrameX, FrameX1, FireballFrameX, FireballFrameX1, RockfallFrameX, DieFrameX;
	int Time, Pattern;
	int Hp;	
	float currentTime;
	float gravity;
	float rockGravity;

	bool UpDown;
	bool Die;
};
struct AncientBullet // 파이어볼
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

// 보스 레비아탄 5번째
struct LeviathanStruct
{
	BOSS_LEVIATHAN LeviathanState;
	RECT Rc;
	RECT FireRc;
	float X, Y;
	float FireX, FireY;
	// 대기, 레이저, 불
	int FrameX, FrameY, FireMotionFrameX, FireFrameX, DownFrameX, LaserMotionX, DieFrameX;
	int Time, Pattern;
	int Hp;
	float currentTime1, currentTime2, currentTime3;
	float gravity;

	bool Down, Shake, Die;
};

// 보스 공동 스킬 (고대웜 & 레비아탄)
struct Laser
{
	float X, Y;
	RECT Rc;
	int LaserFrameX, LaserFrameX1;
	bool shot, change;
};

// 보스 늑대인간 6번째
struct LycanthropeStruct
{

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
	//int playerJumpCheck;
	bool villageMove;

	RECT Wall[15];

private: // 배틀씬1 적(좀비)
	EnemyStruct zombie;

private: // 첫번째 보스(파이몬)
	BossStruct vomitBoss;

private: // 두번째 보스(벨페고르)
	BelphegorStruct belphegor;
	JavelinStruct javelin;
	PotalStruct potal;

	// 분기별로 나눠준 랜더와 업데이트
	int ChangeBoss;
	int BossPattern;
	// ChangeBoss 안의 패턴 (순차적으로 진행)
	int ChangeBossPaturn;

private: // 세번째 보스(크로셀)
	CrocellStruct Crocell;
	SkeletonStruct Skeleton;

	vector<CrocellBullet> vBullet;
	// 시간 흐름대로 지나가는 패턴
	float currentTime;
	int CrocellPattern;

private: // 네번째 보스(고대웜)
	AncientWormStruct AncientWorm;
	Laser AncientWormLaser;
	AncientBullet FireBall;
	AncientRockFall RockFall;

	vector<AncientBullet> vABullet;
	vector<AncientBullet>::iterator viABullet;
	vector<AncientRockFall> vRock;

	int RedOceanFrame;
	int bulletCount;

private: // 다섯번째 보스(레비아탄)
	LeviathanStruct Leviathan;
	Laser LeviathanLaser;

	int BlueOceanFrame;

private: // 여섯번째 보스(늑대인간)
	LycanthropeStruct Lycanthrope;

//private: // 일곱번째 보스(아폴리온)

//private: // 여덟번째 보스(마몬 or 마할몬 or 지옥의 투사 or 변형체(헬 모나크))

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void playerInit(void);
	void playerUpdate(void);
	void playerRender(void);
	// 적(좀비)
	void enemyInit(void);
	void enemyUpdate(void);
	void enemyRender(void);
	// 1번째 보스
	void bossVomitInit(void);
	void bossVomitUpdate(void);
	void bossVomitRender(void);
	// 2번째 보스
	void BelphegorInit(void);
	void BelphegorUpdate(void);
	void BelphegorRender(void);
	// 3번째 보스
	void CrocellInit(void);
	void CrocellUpdate(void);
	void CrocellRender(void);
	void CrocellSkeletonReset(void);
	// 4번째 보스
	void AncientWormInit(void);
	void AncientWormUpdate(void);
	void AncientWormRender(void);
	// 5번째 보스
	void LeviathanInit(void);
	void LeviathanUpdate(void);
	void LeviathanRender(void);
	// 6번째 보스
	void LycanthropeInit(void);
	void LycanthropeUpdate(void);
	void LycanthropeRender(void);

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

	// 렉트 충돌용 설정자
	void setWall(int num, RECT rc) { Wall[num] = rc; }

	Unit() {}
	~Unit() {}
};