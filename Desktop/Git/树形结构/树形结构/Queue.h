#pragma once
#include<assert.h>
#include<stdlib.h>
//������ʵ�ֶ���

typedef int BDataType;

typedef struct QNode{//�������е�һ���ڵ�
	BDataType data;
	struct BNode *next;
}QNode;

typedef struct Queue{
	QNode *front;
	QNode *rear;
	int size;
}Queue;

void QueueInit(Queue *pQ)//���еĳ�ʼ��
{
	assert(pQ != NULL);
	pQ->front = pQ->rear = NULL;
	pQ->size = 0;
}

void QueueDestroy(Queue *pQ)//���ٶ���
{
	assert(pQ);
	QNode *del, *next;
	for (del = pQ->front; del != NULL; del = next)
	{
		next = del->next;
		free(del);
	}
	pQ->front = pQ->rear = NULL;
	pQ->size = 0;
}

void QueuePush(Queue *pQ, BDataType data)//����Ԫ��
{
	pQ->size++;
	QNode *node = (QNode*)malloc(sizeof(QNode));
	node->next = NULL;
	node->data -= data;
	if (pQ->front == NULL)
	{
		pQ->front = pQ->rear = node;
		return;
	}
	pQ->rear->next = node;
	pQ->rear = NULL;
}

void QueuePop(Queue *pQ)//ɾ��Ԫ�أ���Ϊ������ѭ�Ƚ��ȳ���������������ɾ��Ҳ����ͷɾ
{
	pQ->size--;
	assert(pQ != NULL);
	assert(pQ->front != NULL);
	if (pQ->front == pQ->rear)
	{
		free(pQ->front);
		pQ->front = pQ->rear = NULL;
	}
	QNode *cur = pQ->front;
	pQ->front = pQ->front->next;
	free(cur);

}

BDataType QueueFront(const Queue *pQ)//����ͷԪ��
{
	assert(pQ != NULL);
	assert(pQ->front != NULL);

	return pQ->front->data;
}

int QueueEmpty(const Queue *pQ)//�ж϶����Ƿ�Ϊ��
{
	assert(pQ != NULL);
	return pQ->front == NULL ? 1 : 0;
}

int QueueSize(const Queue *pQ)//���ض��еĴ�С
{
	assert(pQ != NULL);
	//���ַ��� 
	//һ���ǶԶ��б������Ӹ�������
	//��������ÿռ任ȡʱ��ķ��� ��Queue�Ķ����һ��size
	return pQ->size;
}