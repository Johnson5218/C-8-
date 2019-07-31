#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
typedef int DataType;

typedef struct LinkList
{
	DataType data;
	struct LinkList * next;
}LinkList, *PLinkList;

PLinkList initLink()//��ʼ������  һ����ͷ�ڵ������
{
	LinkList* p = (LinkList*)malloc(sizeof(LinkList));//����һ��ͷ���
	p->data = 0;//��ʾ�����е�Ԫ�ظ���
	p->next = NULL;
	return p;
}

PLinkList CreateLink(PLinkList Link)//����һ���½ڵ�
{
	PLinkList a = (PLinkList)malloc(sizeof(LinkList));
		a->next = NULL;
		a->data = 0;
		Link->data += 1;
		return a;
}

void LPushFront(PLinkList Link,DataType data)//ͷ��
{
		PLinkList a = CreateLink(Link);
		a->next = Link->next;
		a->data = data;
		Link->next = a;
}



void LPushBack(PLinkList Link, DataType data)//β��
{
	assert(Link);
	PLinkList cur = Link;
	PLinkList a = CreateLink(Link);
	a->data = data;
	a->next = NULL;
	while (cur->next != NULL)
	{
		cur = cur->next;
	}
	cur->next = a;
}



void LPopFront(PLinkList Link)//ͷɾ
{
	if (Link->next == NULL)
	{
		printf("�����ѿ�\n");
		return;
	}
	else
	{
		PLinkList del = Link->next;
		Link->next = Link->next->next;
		Link->data -= 1;
		free(del);
		del = NULL;
	}
}

void LPopBack(PLinkList Link)//βɾ
{
	PLinkList del = Link;
	if (del->next == NULL)
	{
		return;
	}
	else
	{
		while (del->next->next!=NULL)
		{
			del = del->next;
		}
		free(del->next->next);
		del->next = NULL;
	}

}



int SelectLinkList(PLinkList Link,DataType data)//����ĳԪ�ز��������������е�λ��
{
	int i = 0;
	for (PLinkList cur = Link; cur->next != NULL; cur = cur->next)
	{
		if (cur->data == data)
		{
			return i;
		}
		i += 1;
	}
	return -1;
}

void PInsertLinkList(PLinkList Link, int pos, DataType data)//������������
{
	PLinkList cur = Link;
	while (pos-1)
	{
		cur = cur->next;
		pos--;
	}
	PLinkList Ins = CreateLink(Link);
	Ins->next = cur->next->next;
	cur->next = Ins;
	Ins->data = data;
}

void PDelLinkList(PLinkList Link, int pos)//ɾ�������еĽڵ�
{
	PLinkList del = Link;
	PLinkList tmp = Link;
	while (pos)
	{
		tmp = del;
		del = del->next;
		pos--;
	}
	tmp->next = del->next;
	free(del);
	del = NULL;
	Link->data -= 1;
}

void PRINTF(PLinkList Link)//�������
{
	PLinkList cur = Link;
	while (cur->next != NULL)
	{
		cur = cur->next;
		printf("%d-->", cur->data);
	}
	printf("NULL", cur->data);
}

void test()
{
	PLinkList p = initLink();
	LPushFront(p, 5);
	LPushFront(p, 4);
	LPushFront(p, 3);
	LPushFront(p, 2);
	LPushFront(p, 1);
	LPopFront(p);
	LPushBack(p, 6);
	LPopBack(p);
	PInsertLinkList(p, 2, 10);
	PDelLinkList(p, 3);
	PRINTF(p);
}
