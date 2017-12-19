#include<stdio.h>
#include<stdlib.h>

typedef struct listNode *listPointer;
typedef struct listNode{
	int data;
	listPointer left;
	listPointer right;
} node;

listPointer creatnode()
{
	listPointer newnode;
	newnode = (listPointer)malloc(sizeof(node));
	newnode->left = NULL;
	newnode->right = NULL;
	return newnode;
}

void add(listPointer n, int number)
{
	if(number > n->data)
	{
		if(n->left != NULL)
			add(n->left, number);		
		else
		{
			listPointer newnode = creatnode();
			newnode->data = number;
			n->left = newnode;
		}
	}
	else
	{
		if(n->right != NULL)
			add(n->right, number);
		else
		{
			listPointer newnode = creatnode();
			newnode->data = number;
			n->right = newnode;
		}
	}
}

int search(listPointer n, int number)
{
	if(number > n->data)
	{
		if(n->left != NULL)
			return search(n->left, number);
		else
			return NULL;
	}
	else if(number < n->data)
	{
		if(n->right != NULL)
			return search(n->right, number);		
		else
			return NULL;
	}
	else
		return n->data;
}

void print(listPointer p, int level)
{
	if(p->right != NULL)
		print(p->right, level + 1);	
		int i;
	for(i = 0; i < level - 1; i++)
		printf("\t");
	printf("%d\n", p->data);
	if(p->left != NULL)
		print(p->left, level + 1);
}

int main()
{
	listPointer root = NULL;
	int run = 1;
	int f = 0;
	int data, n;
	
	while(run == 1)
	{
		printf("1.新增資料 2.搜尋資料 3.印出 4.離開 請選擇:\n");
		scanf("%d", &f);
		switch(f)
		{
			case 1:
				printf("請輸入要新增的資料:\n");
				scanf("%d", &data);
				if(root == NULL)
				{
					root = creatnode();
					root->data = data;
				}
				else				
					add(root, data);
				break;
			case 2:
				if(root == NULL)
				{
					printf("Empty!\n");
					break;
				}
				printf("請輸入要搜尋的資料:\n");
				scanf("%d", &data);
				n = search(root, data);
				if(n == NULL)
					printf("查無資料\n");
				else
					printf("找到%d\n", n);
				break;
			case 3:
				print(root, 1);
				printf("\n\n");
				break;
			case 4:
				run = 0;
				break;
		}
	}
}
