#pragma once
#include<Windows.h>
#include<assert.h>
//����ջ���ǿ�����˳����������ʵ�֣�ջ�Ĵ��벢���ѣ��ڴ˴���Ϊ��ʡ�£�ֱ����˳�������ʾ

typedef void* SDataType;

#define MAX_SIZE (100)


typedef struct{
	SDataType array[MAX_SIZE];
	int top;
} Stack;

void InitStack(Stack *pS)//��ʼ��ջ
{
	pS->top = 0;
}

void StackPush(Stack *pS, SDataType data)//ѹջ
{
	assert(pS->top < MAX_SIZE);
	pS->array[pS->top] = data;
	pS->top++;
}

void StackPop(Stack *pS)//��ջ,ջ��ֻ��һ����ջ�ķ���
{
	pS->top--;
}

void StackDestroy(Stack *pS)//����ջ
{
	pS->top = 0;
}

SDataType StackTop(const Stack *pS)//����ջ��Ԫ��
{
	assert(pS->top > 0);
	return pS->array[pS->top - 1];
}

int StackSize(const Stack *pS)//����ջԪ�ص�����
{
	return pS->top;
}

int StackEmpty(const Stack *pS)//�ж�ջ�Ƿ�Ϊ��
{
	return pS->top == 0 ? 1 : 0;
}
