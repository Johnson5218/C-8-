#pragma once
#include<assert.h>
#include<stdlib.h>

typedef int DataType;


//һ��˫������Ľڵ�
typedef struct DLinkList{
	struct DLinkList *prior;
	DataType data;
	struct DLinkList *next;
} DLinkList , *PDLinkList;

//����˫�������ͷ�ڵ�
//ͷ�ڵ���Ҫ ˫������һ��Ԫ�صĵ�ַ ���ڴ�ͷ�ڵ��˫��������� ͷ�ڵ������Ԫ�� ͷ�ڵ㲻�ܱ�ɾ��

//typedef struct Head{
//	struct DLinkList *LinkList;
//	DataType num;
//};

//ͷ�ڵ㲻�ɸı�  ָ���ΪNULL

PDLinkList CreatDLinkList(DataType data)//�����½��
{	
	PDLinkList newnode = (PDLinkList)malloc(sizeof(DLinkList));
	if (NULL == newnode)
	{
		return NULL;
	}
	newnode->data = data;
	newnode->next = NULL;
	newnode->prior = NULL;
	return newnode;
}

void InitDLinkList(PDLinkList pHead)//��ʼ��
{
	assert(pHead);
	if (NULL == pHead)
	{
		return;
	}
	pHead->next = pHead;
	pHead->prior = pHead;
}



void PushHead(PDLinkList pHead,DataType data)//ͷ��
{
	assert(pHead);
	PDLinkList p = CreatDLinkList(data);
	p->next = pHead->next;
	p->prior = pHead;
	pHead->next->prior = p;
	pHead->next = p;
	pHead->data += 1;
}

void PopHead(PDLinkList pHead)//ͷɾ
{
	assert(pHead);
	if (pHead->data == 1)
	{
		free(pHead->next);
		pHead->next = NULL;
		pHead->prior = NULL;
		pHead->data -= 1;
		return;
	}
	pHead->next = pHead->next->next;
	free(pHead->next->prior);
	pHead->next->prior = pHead;
	pHead->data -= 1;
}

void PushBack(PDLinkList pHead��DataType data)  //β��
{
    

}


//

void test()
{
	PDLinkList p = CreatDLinkList(0);
	InitDLinkList(p);
	PushHead(p, 1);
	PushHead(p, 2);
	PushHead(p, 3);
	PushHead(p, 4);
	PushHead(p, 5);

}


