#include<stdio.h>
#include<stdlib.h>

struct node
{
	int data;
	struct node *parent;
	struct node *left;
	struct node *right;
};

struct node *creatnode(void)
{
	struct node *newnode;
	newnode=(struct node *)malloc(sizeof(struct node));
	newnode->left=NULL;
	newnode->right=NULL;
	newnode->parent=NULL;
	return newnode;
}

void add(struct node *n, int number)
{
	if(number<n->data)
	{
		if(n->left!=NULL)		
			add(n->left,number);		
		else
		{
			struct node *newnode=creatnode();
			newnode->data=number;
			n->left=newnode;
			newnode->parent=n;
		}
	}
	else
	{
		if(n->right!=NULL)		
			add(n->right,number);		
		else
		{
			struct node *newnode=creatnode();
			newnode->data=number;
			n->right=newnode;
			newnode->parent=n;
		}
	}
}

int search(struct node *n, int number)
{
	if(n->data>number)
	{
		if(n->left!=NULL)		
			return search(n->left,number);		
		else
			return NULL;
	}
	else if(n->data<number)
	{
		if(n->right!=NULL)		
			return search(n->right,number);		
		else
			return NULL;		
	}
	else if(n->data==number)	
		return n->data;	
}

void print(struct node *p)
{
	if(p->left!=NULL)
		print(p->left);
	printf("%d\t",p->data);
	if(p->right!=NULL)
		print(p->right);
}

void delete(struct node *n)
{
	if(n->parent!=NULL)
	{
		struct node *p=n->parent;
		if(n->left==NULL&&n->right==NULL)
		{
			if(n->data<p->data)
			{
				p->left=NULL;
				n->parent=NULL;
			}
			else
			{
				p->right=NULL;
				n->parent=NULL;
			}
		}
		else if(n->left==NULL&&n->right!=NULL)
		{
			if(n->data<p->data)
			{
				n=n->right;
				p->left=n;
				n->parent=p;
			}
			else
			{
				n=n->left;
				p->right=n;
				n->parent=p;
			}						
		}
		else if(n->left!=NULL&&n->right==NULL)
		{
			if(n->data<p->data)
			{
				n=n->left;
				p->left=n;
				n->parent=p;
			}
			else
			{
				n=n->left;
				p->right=n;
				n->parent=p;
			}	
		}
		else
		{
			findmax()
		}
	}
	else
	{
		
	}	
	
}

int main()
{
	struct node *root=NULL;
	
	int run=1;
	int f=0;
	int data;
	int n;
	while(run==1)
	{
		printf("1.新增資料 2.搜尋資料 3.刪除資料 4.修改資料 5.中序印出 請選擇:\n");
		scanf("%d",&f);
		switch(f)
		{
			case 1:
				printf("請輸入要新增的資料:\n");
				scanf("%d",&data);
				if(root==NULL)
				{
					root=creatnode();
					root->data=data;
				}
				else				
					add(root,data);				
			break;
			case 2:
				printf("請輸入要搜尋的資料:\n");
				scanf("%d",&data);
				if(root==NULL)
					printf("查無資料\n");
				else
					n=search(root,data);
					if(n==NULL)
						printf("查無資料\n");
					else
						printf("找到%d\n",n);
			break;
			case 3:
				
			break;
			case 4:
				
			break;
			case 5:
				print(root);
				printf("\n\n");
			break;
		}
	}
}
