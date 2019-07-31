#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<assert.h>

typedef int BDataType;

typedef struct BNode{
	BDataType data;
	struct BNode *left;
	struct BNode *right;
}BNode;

static BNode* CreatNode(BDataType data)
{
	BNode *node = (BNode*)malloc(sizeof(BNode));
	node->data = data;
	node->left = node->right = NULL;
	return node;
}

typedef struct{
	BNode *root;
	int used;
}RESULT;

RESULT CreatTree(BDataType perorder[],int size)
{
	if (size == 0)
	{
		RESULT result = { NULL, 0 };
	}
	BDataType rootVelue = perorder[0];
	if (rootVelue == -1)
	{
		RESULT result = { NULL, 1 };
		return result;
	}
	
	BNode *root = CreatNode(rootVelue);

	RESULT lr = CreatTree(&perorder[1], size - 1);
	root->left = lr.root;

	RESULT rr = CreatTree(&perorder[1 + lr.used], size - 1 - lr.used);
	root->right = rr.root;

	RESULT result = { root, 1 + lr.used + rr.used };
	return result;

}

void Preorder(BNode *root)//ǰ�������
{
	//��ֹ������
	if (root == NULL)
	{
		return;
	}
	//���ڵ�ֱ�����
	printf("%d ", root->data);
	//������
	Preorder(root->left);
	//������
	Preorder(root->right);

}

void Inorder(BNode *root)//���������
{
	//��ֹ������
	if (root == NULL)
	{
		return;
	}
	Inorder(root->left);//�ҵ�����ڵ��ʼ���
	printf("%d ", root->data);
	//������
	Inorder(root->right);
}

void Postorder(BNode *root)//���������
{
	//��ֹ������
	if (root == NULL)
	{
		return;
	}
	Postorder(root->left);//�ҵ�����ڵ��ʼ
	Postorder(root->right);//��ʼ�����е��ҽڵ�
	//�����
	printf("%d ", root->data);
}

int GetSize(BNode *root)//��ڵ����
{
	if (root == NULL)
	{
		return 0;
	}
	return GetSize(root->left) + GetSize(root->right) + 1;
}

int GetLeafSize(BNode *root)//��Ҷ�ӽڵ����
{
	if (root == NULL)
	{
		return 0;
	}
	else if (root->left==NULL && root->right==NULL)
	{ 
		return 1;
	}
	else
	{
	return GetLeafSize(root->left) + GetLeafSize(root->right);
	}
}

int GetKLeafSize(BNode *root, int k)//���k���Ҷ�ӽڵ�
{
	assert(k > 0);
	if (root == NULL)
	{
		return 0;
	}
	if (k == 1)
	{
		return 1;
	}
	return GetKLeafSize(root->left, k - 1) + GetKLeafSize(root->right, k - 1);
}

#define MAX(a,b) ((a)>(b)?(a):(b))

int GetHeight(BNode *root)//�����ĸ߶�
{
	if (root == NULL){
		return 0;
	}
	int leftHeight = GetHeight(root->left);
	int rightHelght = GetHeight(root->right);
	//return MAX(GetHeight(root->left), GetHeight(root->right)) + 1;
	//ע���µ������⣬��Ҫ���ж�ε���
	return MAX(leftHeight, rightHelght) + 1;
}

BNode * Search(BNode *root,BDataType key)
{
	if (root == NULL){
		return NULL;
	}
	//������
	if (root->data == key){
		return root;
	}
	BNode * node = Search(root->left, key);
	if (node != NULL){
       return node;
	}
	node = Search(root->right, key);
	if (node != NULL){
		return node;
	}
	else{
		return NULL;
	}
}

#include"Queue.h"


void LevelOrder(BNode *root)//���������
{
	Queue queue;
	QueueInit(&queue);
	if (root == NULL)
	{
		return;
	}
	QueuePush(&queue,root);
	while (!QueueEmpty(&queue)){
		BNode *front = QueueFront(&queue);
		QueuePop(&queue);
		printf("%d ", front->data);
		if (front->left != NULL){
			QueuePush(&queue, front->left);
		}
		if (front->right != NULL){
			QueuePush(&queue, front->right);
		}
	}
	QueueDestroy(&queue);
}

int IsComplete(BNode *root)//�ж϶������Ƿ�Ϊ��ȫ������
{
	Queue queue;
	QueueInit(&queue);
	if (root == NULL)
	{
		return 1;
	}
	QueuePush(&queue, root);
	while (!QueueEmpty(&queue))
	{
		BNode *front = QueueFront(&queue);
		QueuePop(&queue);
		if (front == NULL)
		{
			break;
		}
			QueuePush(&queue, front->left);
			QueuePush(&queue, front->right);
	}
	while (!QueueEmpty(&queue))
	{
		BNode *node = QueueFront(&queue);
		QueuePop(&queue);
		if (node != NULL)
		{
			QueueDestroy(&queue);
			return 0;
		}
	}
	QueueDestroy(&queue);
	return 1;
}



#include"Stack.h"

void PreorderLoop(BNode *root)//�÷ǵݹ鷽��ʵ��ǰ�����
{
	Stack stack;
	InitStack(&stack);
	BNode *node = root;
	BNode *top;
	while (node != NULL || !StackEmpty(&stack))
	{
		while (node != NULL)
		{
			printf("%d ", node->data);
			StackPush(&stack, node);//ѹջ  ѹ���ǽڵ��ַ
			node = node->left;
		}

		top = StackTop(&stack);
		StackPop(&stack);
		node = top->right;
	}
}

void InorderLoop(BNode *root)//�÷ǵݹ鷽��ʵ���������
{
	Stack stack;
	InitStack(&stack);
	BNode *node = root;
	BNode *top;
	while (node != NULL || !StackEmpty(&stack))
	{
		while (node != NULL)
		{
			
			StackPush(&stack, node);//ѹջ  ѹ���ǽڵ��ַ
			node = node->left;
		}

		top = StackTop(&stack);
		StackPop(&stack);
		printf("%d ", top->data);
		node = top->right;
	}
}

void PostorderLoop(BNode *root)//�÷ǵݹ鷽��ʵ�ֺ������
{
	Stack stack;
	InitStack(&stack);
	BNode *node = root;
	BNode *top;
	BNode *last = NULL;
	while (node != NULL || !StackEmpty(&stack))
	{
		while (node != NULL)
		{

			StackPush(&stack, node);//ѹջ  ѹ���ǽڵ��ַ
			node = node->left;
		}


		top = StackTop(&stack);
		if (top->right == NULL || top->right == last)
		{
			printf("%d ", top->data);
			last = top;
			StackPop(&stack);
		}
		else
		{
			node = top->right;
		}
	}
}

void Mirror(BNode *root)//���������
{
	if (root == NULL)
	{
		return;
	}
	BNode *t = root->left;
	root->left = root->right;
	root->right = t;
	Mirror(root->left);
	Mirror(root->right);
}

BNode * GetNearstAncestor(BNode *root,BNode *n1,BNode *n2)//��ȡ��������Ƚڵ�
{
	BNode *n1InLeft = Search(root->left, n1->data);
	BNode *n2Inleft = Search(root->left, n2->data);
	if (n1InLeft && !n2Inleft)
	{
		return root;
	}
	if (!n1InLeft && n2Inleft)
	{
		return root;
	}
	if (n1InLeft)
	{
		return GetNearstAncestor(root->left, n1, n2);
	}
	else
	{
		return GetNearstAncestor(root->right, n1, n2);
	}
}

int IsBalance1(BNode *root)//�ж��Ƿ�Ϊƽ�������
{
	if (root == NULL)
	{
		return 1;
	}

	int isBalance = IsBalance1(root->left);
	if (isBalance == 0)
	{
		return 0;
	}
	isBalance = IsBalance1(root->right);
	if (isBalance == 0)
	{
		return 0;
	}
	int leftHeight = GetHeight(root->left);
	int rightHeight = GetHeight(root->right);
	int diff = leftHeight - rightHeight;
	if (diff<-1 || diff>1)
	{
		return 0;
	}
}

int IsBalance2(BNode *root,int *pHeight)//�ж��Ƿ�Ϊƽ�������
{
	if (root == NULL)
	{
		*pHeight = 0;
		return 1;
	}
	int leftHeight;
	int rightHeight;
	int leftBalance = IsBalance2(root->left, leftHeight);
	int rightBalance = IsBalance2(root->right, rightHeight);
	*pHeight = MAX(leftHeight, rightHeight) + 1;
	if (leftBalance == 0 || rightBalance == 0)
	{
		return 0;
	}
	int diff = leftHeight - rightHeight;
	if (diff<-1 || diff>1)
	{
		return 0;
	}
	else
	{
		return 1;
	}	
}

void test()
{
	//BDataType perorder[] = { 1, 2, 3, -1, -1, 4, 5, -1, -1, -1, 6, 7, -1, -1, -1 };
	//int size = sizeof(perorder) / sizeof(perorder[0]);
	//RESULT result = CreatTree(perorder, size);
	//Preorder(result.root);
	//printf("\n");
	//Inorder(result.root);
	//printf("\n");
	//Postorder(result.root);
	//printf("\n");
	//BNode *root = result.root;
	//printf("������: %d\n", GetSize(root));
	//printf("Ҷ�ӽ�����: %d\n", GetLeafSize(root));
	//printf("�� 3 �������: %d\n", GetKLeafSize(root, 3));
	//printf("�߶�: %d\n", GetHeight(root));
	//printf("���� D: %d\n", (Search(root, 4))->data);
	//printf("���� E: %d\n", (Search(root, 5))->data);
	//printf("���� H: %p\n", Search(root, 8));
	BDataType perorder[] = { 1, 2, 4, -1, -1,  5, -1, -1, 3, -1, -1 };
	int size = sizeof(perorder) / sizeof(perorder[0]);
	RESULT result = CreatTree(perorder, size);
	//Preorder(result.root);
	//printf("\n");
	//PreorderLoop(result.root);
	//printf("\n");
	//InorderLoop(result.root);
	//printf("\n");
	//PostorderLoop(result.root);
	//printf("\n");
	//BNode *root = result.root;
	//Mirror(result.root);
}