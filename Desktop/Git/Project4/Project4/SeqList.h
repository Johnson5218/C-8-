#pragma once

#include<stdio.h>
#include<assert.h>
#include <stdlib.h>
#include<malloc.h>

#define ADD_SIZE 3

typedef int DataType;

typedef  struct SeqList
{
	DataType *p;
	int sz;
	int capacity;
}SeqList, *PSeqList;


int CheakCapcity(PSeqList Seq)//���˳����Ƿ�����
{
	DataType *temp = Seq->p;
	assert(Seq);
	if (Seq->sz >= Seq->capacity)
	{
		DataType Newcapacity = Seq->capacity + 5;
		Seq->p = (DataType*)realloc(Seq->p, Newcapacity * sizeof(DataType));
		if (Seq->p == NULL)
		{
			Seq->p = temp;
			printf("����ʧ��\n");
			return -1;
		}
		else
		{
			Seq->capacity = Newcapacity;
		}
	}
	return 1;
}

void InitSeqList(PSeqList pSeqList)//��ʼ��˳���
{
	pSeqList->sz = 0;
	pSeqList->capacity = 5;
	pSeqList->p = (DataType *)malloc(pSeqList->capacity * sizeof(DataType));
	if (NULL == pSeqList->p)
	{
		printf("��ʼ��˳���ʧ��");
	}
}


void PushFront(PSeqList Seq,DataType data)//ͷ��
{
	int i = 0;
	int ret = 0;
	assert(Seq);
	ret = CheakCapcity(Seq);
	if (1 == ret)
	{
		for (i = Seq->sz; i > 0; i--)
		{
			Seq->p[i] = Seq->p[i - 1];

		}
		Seq->p[0] = data;
		Seq->sz++;
	}

}

void PopFront(PSeqList Seq)//ͷɾ
{
	if (Seq == NULL)
	{
		printf("�ѿ�\n");
		return;
	}
	else
	{
		for (int i = 0; i < Seq->sz - 1; i++)
		{
			Seq->p[i] = Seq->p[i + 1];
		}
	}
	Seq->sz--;
}

void PushBack(PSeqList Seq,DataType data)//β��
{
	int ret = 0;
	assert(Seq);
	ret = CheakCapcity(Seq);
	if (1 == ret)
	{
		Seq->p[Seq->sz] = data;
		Seq->sz++;
	}
}

void PopBack(PSeqList Seq)//βɾ
{
	assert(Seq);
	if (Seq->p == NULL)
	{
		printf("�ѿ�\n");
		return;
	}
	else
		Seq->sz--;
}

int Search(PSeqList Seq,DataType data)//����˳����е�һ��Ԫ��data��������λ��
{
	assert(Seq);
	for (int i = 0; i < Seq->sz; i++)
	{
		if (Seq->p[i] == data)
		{
			printf("��˳����еĵ�%d��\n", i+1);
			return i + 1;
		}
	}
	return -1;
}

void Insert(PSeqList Seq, int pos, DataType data)//������posλ��
{
	assert(Seq);
	int ret = CheakCapcity(Seq);
	for (int i = Seq->sz; i >= pos; i--)
	{
		Seq->p[i + 1] = Seq->p[i];
	}
	Seq->p[pos] = data;
	Seq->sz++;
}


void Erase(PSeqList Seq, int pos)//ɾ����posλ��
{
	assert(Seq);
	for (int i = pos; i < Seq->sz; i++)
	{
		Seq->p[i] = Seq->p[i + 1];
	}
	Seq->sz--;
}

void Remove(PSeqList Seq, DataType data)//ɾ��˳����еĵ�һ��dataԪ��
{
	assert(Seq);
	Erase(Seq, Search(Seq, data));
	printf("ɾ���ɹ�\n");
}

void RmeoveAll(PSeqList Seq, DataType data)//ɾ��˳��������е�dataԪ��
{
	assert(Seq);
	int j = Seq->sz;
	for (int i = 0; i < j; i++)
	{
		if (Seq->p[i] == data)
		{
			Remove(Seq, data);
			i--;
			j--;
		}
	}
	printf("ɾ���ɹ�\n");
}

void Swap(size_t *num1,size_t *num2)
{
	DataType tmp = *num1;
	*num1 = *num2;
	*num2 = tmp;
}

void BorbbleSort(PSeqList Seq)//ð������
{
	size_t i = 0;
	size_t j = 0;
	assert(Seq);
		for (i = 0; i < ((Seq->sz) - 1); i++)
		{
			for (j = 0; j < ((Seq->sz) - 1); j++)
			{

				if (Seq->p[j]>Seq->p[j + 1])
				{
					Swap(&Seq->p[j + 1], &Seq->p[j + 1]);
				}
			}
		}
}

void SelectSort(PSeqList Seq)//��������
{
	size_t left = 0;
	size_t i = 0;
	size_t num = 0;
	size_t min = 0;
	size_t max = 0;
	assert(Seq);
	for (left = 0; left < (Seq->sz/2+1); left++)
	{
		for (i = left; i < Seq->sz - left;i++)
		{
			min = Seq->p[i] > Seq->p[min] ? min : i;
			max = Seq->p[i] < Seq->p[max] ? max : i;
		}
		Swap(&Seq->p[left], &Seq->p[min]);
		Swap(&Seq->p[Seq->sz - left], &Seq->p[max]);
		min += 1;
		max += 1;
	}
}

void PrintSeqList(PSeqList Seq)//��ӡ
{
	assert(Seq);
	for (int i = 0;i < (Seq->sz); i++)
	{
		printf("%d  ", Seq->p[i]);
	}
	printf("\n");
}


void DestroyList(PSeqList Seq)
{
	assert(Seq);
	Seq->sz = 0;
	Seq->capacity = 0;
	free(Seq->p);
}

void test()
{
	SeqList seqList;
	InitSeqList(&seqList);
	printf("˳���");
	PushBack(&seqList, 1);
	PushBack(&seqList, 4);
	PushBack(&seqList, 7);
	PushBack(&seqList, 8);
	PushBack(&seqList, 5);
	PushBack(&seqList, 2);
	PushBack(&seqList, 3);
	PushBack(&seqList, 6);
	PushBack(&seqList, 9);
	SelectSort(&seqList);
	PrintSeqList(&seqList);
}