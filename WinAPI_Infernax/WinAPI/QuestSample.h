#pragma once
#include "Quest.h"

/*
	▶ 큐(queue) 
	- FIFO(First In First Out): 선입선출 ★
	- 큐는 삽입과 삭제가 용이하다.
		ㄴ 리스트의 일종
	- 스텍과는 다르게 가장 처음에 들어간 데이터가 처음에 나오는 FIFO 구조를 가지고 있다.
	- 삽입이 일어나는 쪽을 뒤 (rear), 삭제가 일어나는 쪽을 앞(frond) 라고 한다.

	// 게임을 구축할 때 큐를 자주 사용한다.
	// 리스트부터 굉장히 가볍다
	// 리스트는 STL, 벡터 등..
	// 큐는 멤버함수가 적고 간소화 되어있다.

	※ 큐를 사용하면 좋은 상황
	- 프린트 큐
	- CPU 스케쥴링
	- 데이터 버퍼 확인 작업
	- BFS / DFS (너비 / 깊이)

	// 프린트 큐: 자료구조, 큐를 출력한다. 큐 자체가 강력하게 어필할 수 있기에 프린트 큐라고 부른다.
	// 1000개 미만의 아이템 데이터를 펼쳐서 보고 싶을 때가 있다. 고유 식별 번호를 확인해야 할때 고유 식별번호가 같을때 트레킹해야할때
	// 한번에 뿌려놓고 중복되는 식별번호를 찾는다.
	// 어떤 칼인지, 갯수, 식별번호, 등등등을 찾아낸다.

	※ 자주 사용하는 멤버 함수

	- front()
		ㄴ 첫번째 요소에 접근
	- back()
		ㄴ 마지막 요소에 접근
	- push()
		ㄴ 큐에 데이터를 삽입
	- size()
		ㄴ 크기를 반환
	- empty()
		ㄴ 비어있는지 확인

	배열: 삽입 삭제가 용이 하지 않다. 계속해서 반복을 돌아야하기 때문에 느려질 수 있다.
*/

class Quest;

class QuestSample
{

private:
	queue <Quest*> _quest;

public:
	void init(void);
	void questSetUp(Quest* pQuest = nullptr);

	queue<Quest*>* getQuest() {return &this->_quest; }

	QuestSample() {}
	~QuestSample() {}
};