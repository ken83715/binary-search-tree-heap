#include<stdio.h>
#include<stdlib.h>

typedef struct listNode *listPointer;
typedef struct listNode{
	int data;
	listPointer parent;
	listPointer left;
	listPointer right;
} node;

listPointer creatnode()
{
	listPointer newnode;
	newnode = (listPointer)malloc(sizeof(node));
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->parent = NULL;
	return newnode;
}

void add(listPointer n, int number)
{
	if(number < n->data)
	{
		if(n->left != NULL)
			add(n->left, number);		
		else
		{
			listPointer newnode = creatnode();
			newnode->data = number;
			n->left = newnode;
			newnode->parent = n;
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
			newnode->parent = n;
		}
	}
}

int search(listPointer n, int number)
{
	if(n->data > number)
	{
		if(n->left != NULL)
			return search(n->left, number);
		else
			return NULL;
	}
	else if(n->data < number)
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
	if(p->left != NULL)
		print(p->left, level + 1);
		int i;
	for(i = 0; i < level; i++)
		printf("\t");
	printf("%d\n",p->data);
	if(p->right != NULL)
		print(p->right, level + 1);
}

int main()
{
	listPointer root = NULL;
	
	int run = 1;
	int f = 0;
	int data, n;
	while(run == 1)
	{
		printf("1.新增資料 2.搜尋資料 3.印出 請選擇:\n");
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
				printf("請輸入要搜尋的資料:\n");
				scanf("%d", &data);
				if(root == NULL)
					printf("查無資料\n");
				else
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
		}
	}
}
