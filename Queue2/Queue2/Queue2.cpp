#include "stdafx.h"
#include <stdlib.h>

// 객체지향적으로 Queue 만들기
class Queue {
public :
	// Queue는 FIFO(First in First out) 구조이다.
	typedef struct node {
		int data;
		struct node *prev;
		struct node *next;
	} NODE;

	NODE *cur; // 현재노드
	NODE *head;
	NODE *tail;
	int nodeCnt;

	Queue(void) { // 생성자
		// 초기값 설정
		cur = NULL;
		head = NULL;
		tail = NULL;
		nodeCnt = 0;
	}

	~Queue(void) { // 소멸자

	}

	void push(int _data);	// 새로운 노드 추가
	void pop();							// 노트 제거
	void ptrQueue();					// 큐의 내용을 출력해주는 함수


private :

};

void Queue::push(int _data)
{
	NODE *newNode = new NODE();
	NODE *tempNode;
	newNode->data = _data;

	if (head == NULL) {
		head = newNode;
		tail = newNode;
	} else {
		tempNode = head;
		head = newNode;
		newNode->next = tempNode;
		tempNode->prev = newNode;
	}

	cur = newNode;
	nodeCnt++;
	printf("노드 저장 %d\n", nodeCnt);
}

void Queue::pop(void)
{
	NODE *delNode = tail;

	// tail 위치 체크하여 pop 시키기
	if (head == NULL) {
		printf("pop 시킬 노드가 없습니다.");
		return;
	} else if (head == tail) { // 마지막 노드(head)를 NULL로 설정
		head = NULL;
		tail = NULL;
		nodeCnt--;
		return;
	}

	tail->prev->next = NULL;
	tail = tail->prev;
	nodeCnt--;

	delete(delNode);
	delNode = NULL;
}

void Queue::ptrQueue(void)
{
	NODE *tempNode = head;
	if (head == NULL) printf("출력할 노드(데이터)가 없습니다.");
	
	while (tempNode != NULL) {
		printf("%d - ", tempNode->data);
		tempNode = tempNode->next;
	}
	putchar('\n');
}

int main(void)
{
	Queue *_queue = new Queue();

	_queue->push(1);
	_queue->ptrQueue();
	_queue->push(2);
	_queue->ptrQueue();
	_queue->pop();
	_queue->ptrQueue();
	_queue->pop();
	_queue->ptrQueue();
	_queue->push(3);
	_queue->ptrQueue();
	_queue->push(4);
	_queue->ptrQueue();
	_queue->push(5);
	_queue->ptrQueue();
	_queue->pop();
	_queue->ptrQueue();
	_queue->pop();
	_queue->ptrQueue();
	_queue->pop();
	_queue->ptrQueue();
	_queue->pop();
	_queue->ptrQueue();
	_queue->pop();
	_queue->ptrQueue();

	/*
	// 널포인터는 아무것도 안가리키는데 delete함수가 되는 이유는
	// delete함수가 알아서 판단하기 때문이다.(널포인터에 대해서는 아무런 동작이 안되게 정의되있음)
	int *a = NULL;
	delete(a);
	// +delete후에는 항상 변수에 NULL을 대입해야 한다.그래야 다시 제대로 할당할 수 있음

	printf("a의 주소 : %d - %d - %d\n", &a, a, sizeof(a));
	a = new int();
	//int a = 2;
	printf("a의 주소 : %d - %d - %d\n", &a, a, sizeof(a));
	delete(a);
*/
	
	return 0;
}