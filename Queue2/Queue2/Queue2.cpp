#include "stdafx.h"
#include <stdlib.h>

// ��ü���������� Queue �����
class Queue {
public :
	// Queue�� FIFO(First in First out) �����̴�.
	typedef struct node {
		int data;
		struct node *prev;
		struct node *next;
	} NODE;

	NODE *cur; // ������
	NODE *head;
	NODE *tail;
	int nodeCnt;

	Queue(void) { // ������
		// �ʱⰪ ����
		cur = NULL;
		head = NULL;
		tail = NULL;
		nodeCnt = 0;
	}

	~Queue(void) { // �Ҹ���

	}

	void push(int _data);	// ���ο� ��� �߰�
	void pop();							// ��Ʈ ����
	void ptrQueue();					// ť�� ������ ������ִ� �Լ�


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
	printf("��� ���� %d\n", nodeCnt);
}

void Queue::pop(void)
{
	NODE *delNode = tail;

	// tail ��ġ üũ�Ͽ� pop ��Ű��
	if (head == NULL) {
		printf("pop ��ų ��尡 �����ϴ�.");
		return;
	} else if (head == tail) { // ������ ���(head)�� NULL�� ����
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
	if (head == NULL) printf("����� ���(������)�� �����ϴ�.");
	
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
	// �������ʹ� �ƹ��͵� �Ȱ���Ű�µ� delete�Լ��� �Ǵ� ������
	// delete�Լ��� �˾Ƽ� �Ǵ��ϱ� �����̴�.(�������Ϳ� ���ؼ��� �ƹ��� ������ �ȵǰ� ���ǵ�����)
	int *a = NULL;
	delete(a);
	// +delete�Ŀ��� �׻� ������ NULL�� �����ؾ� �Ѵ�.�׷��� �ٽ� ����� �Ҵ��� �� ����

	printf("a�� �ּ� : %d - %d - %d\n", &a, a, sizeof(a));
	a = new int();
	//int a = 2;
	printf("a�� �ּ� : %d - %d - %d\n", &a, a, sizeof(a));
	delete(a);
*/
	
	return 0;
}