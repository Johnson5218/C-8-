#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


typedef int TDataType

typedef struct BNode//����ģ��
{
	TDataType data;
	struct BNode *Left;
	struct BNode *Right;
} BNode;

static BNode * PTree(TDataType data)//����һ���ڵ㣨������������ͬ�Ľڵ���ɵ�һ�ֽṹ�壩
{
	BNode *node = (Tree*)malloc(sizeof(Tree));
	node->data = data;
	node->Left = node->Right = 0;
	return node;
}

typedef struct
{
	BNode *root;
	int used;
} RESULT;

RESULT CreateTree(TDataType preorder[],int size)//����һ����������Ҫǰ��/����/����   ���ж��ٸ�����Ĵ�С
{
	//�������
	//�����С����0
	if (size == 0)
	{
		RESULT result = (NULL, 0);
		return result;
	}
	//�����С��������
	//�� ������ ������
	//size==1
	if (size == 1)
	{
		RESULT result = (preorder[0], 1);
		return result;
	}
	//size!=1
	else
	{
		
	}

}




