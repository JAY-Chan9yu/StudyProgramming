#include "stdafx.h"
#include <stdlib.h>

typedef struct node {
	int data;
	struct node *prev;
	struct node *next;
} NODE;

typedef struct list {
	NODE *cur; // ������
	NODE *head;
	NODE *tail;
	int nodeCnt = 0;
} LIST;

// ��� �߰�
void createNode(LIST *_list, int _data)
{
	NODE *newNode = (NODE*)malloc(sizeof(NODE));
	newNode->data = _data;
	newNode->next = NULL;

	if (_list->head == NULL) {
		_list->head = newNode;
	}
	else {
		NODE *tempNode = _list->head;
		while (tempNode->next != NULL) {
			tempNode = tempNode->next;
		}
		newNode->prev = tempNode; // �� ���
		tempNode->next = newNode; // �� ���
		_list->tail = newNode;
	}
	//_list->cur = newNode;
	_list->nodeCnt++;
}

// �� �κп��� �˰����� �����սô�.
// ���ϴ� ������ ã�Ƽ� ��� �����ϴ� �Լ�
void deleteNode(LIST *_list, int _data)
{
	NODE *delNode = _list->head;
	int i;

	for (i = 0; i < _list->nodeCnt; i++) {
		if (delNode->data == _data) {
			//NODE *tempNode;
			if (delNode == _list->head) {
				_list->head = delNode->next;
				delNode->next->prev = _list->head;
				free(delNode);
			}
			else {
				delNode->prev->next = delNode->next;
				delNode->next->prev = delNode->prev;
				free(delNode);
			}
			_list->nodeCnt--;
			return;
		}
		else {
			delNode = delNode->next;
		}
	}

	printf("�����Ϸ��� �����Ͱ� ���� ����Ʈ�� �������� �ʽ��ϴ�.\n");
}

// ����Ʈ ����
void deleteList(LIST *_list)
{
	NODE *delNode;
	while (_list->head != _list->tail) {
		// tail���� �����Ҵ� ����
		delNode = _list->tail;
		_list->tail = _list->tail->prev;
		_list->tail->next = NULL;
		printf("������ ��� %d ", delNode->data);
		free(delNode);
	}
	free(_list); // ����Ʈ �����Ҵ� ����
	putchar('\n');
}

// ����Ʈ ���(������)
void printList(LIST *_list)
{
	NODE *ptrNode = _list->head;
	while (ptrNode != NULL) {
		printf("%d - ", ptrNode->data);
		ptrNode = ptrNode->next;
	}
	printf("count : %d", _list->nodeCnt);
	putchar('\n');
}

int main(void)
{
	LIST *list = (LIST *)malloc(sizeof(LIST));
	list->head = NULL;
	list->nodeCnt = 0;

	createNode(list, 1);
	createNode(list, 2);
	createNode(list, 3);
	createNode(list, 4);
	createNode(list, 5);
	createNode(list, 6);
	printList(list);
	deleteNode(list, 8);
	printList(list);
	deleteList(list);

	return 0;
}