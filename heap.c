#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct node //定義結構
{
    int data; //值 
    int index; //索引 
    struct node *left;
    struct node *right;
    struct node *parent; //parent node 
};

struct node *createnode(void) //創造新空間
{
	struct node *newnode;
	newnode=(struct node *) malloc(sizeof(struct node));
	newnode->left=NULL;
	newnode->right=NULL;
	newnode->parent=NULL;
	return newnode;
}

struct node *insert(struct node *root, int n) //n為索引(index)
{
	if(n/2!=1) //還沒到最後的餘數 
	{
		struct node *ptr=insert(root,n/2);      //                                    1
		if(n%2!=0)                              //                    2                                3
		{                                       //            4               5                6                7
			if(ptr->right!=NULL)                //        8       9       10      11      12      13       14       15
				ptr=ptr->right;                 //餘數    000     100     010    110     001     101      011      111 
		}
		else
		{
			if(ptr->left!=NULL)
				ptr=ptr->left;
		}
		return ptr;
	}
	else //到最後的餘數了
	{
		if(n%2!=0)
		{
			if(root->right!=NULL)
				root=root->right;
		}
		else
		{
			if(root->left!=NULL)
				root=root->left;
		}
		return root;
	}
}

void check(struct node *newnode) //檢查上下大小
{
	if(newnode->parent!=NULL) 
	{
		struct node *p=newnode->parent;
		if(newnode->data>p->data)
		{
			int temp=newnode->data;
			newnode->data=p->data;
			p->data=temp;
			check(p);
		}
	}
	if(newnode->left!=NULL&&newnode->right!=NULL) //左子右子都有 
	{
		struct node *leftc=newnode->left;
		struct node *rightc=newnode->right;
		if(leftc->data>rightc->data) //左子比右子大
		{
			if(newnode->data<leftc->data)
			{
				int temp=newnode->data;
				newnode->data=leftc->data;
				leftc->data=temp;
				check(leftc);
			}
		}
		else //左子比右子小
		{
			if(newnode->data<rightc->data)
			{
				int temp=newnode->data;
				newnode->data=rightc->data;
				rightc->data=temp;
				check(rightc);
			}
		}
	}
	else if(newnode->left!=NULL&&newnode->right==NULL) //只有左子 
	{
		struct node *leftc=newnode->left;
		if(newnode->data<leftc->data)
		{
			int temp=newnode->data;
			newnode->data=leftc->data;
			leftc->data=temp;
			check(leftc);
		}
	}
}

struct node *finddata(struct node *root, int data) //搜尋數值 
{
	if(root->data==data)
	{
		return root;
	}
	else
	{
		if(root->left!=NULL&&root->right!=NULL)
		{
			struct node *leftc=finddata(root->left, data);
			struct node *rightc=finddata(root->right, data);
			if(leftc!=NULL)
			{
				return leftc;
			}
			else if(rightc!=NULL)
			{
				return rightc;
			}
			else
			{
				return NULL;
			}
		}
		else if(root->left!=NULL&&root->right==NULL)
		{
			return finddata(root->left, data);
			
		}
		else
		{
			return NULL;
		}
	}
}

struct node *findindex(struct node *root, int index) //搜尋索引 
{
	if(root->index==index)
	{
		return root;
	}
	else
	{
		if(root->left!=NULL&&root->right!=NULL)
		{
			struct node *leftc=findindex(root->left, index);
			struct node *rightc=findindex(root->right, index);
			if(leftc!=NULL)
			{
				return leftc;
			}
			else if(rightc!=NULL)
			{
				return rightc;
			}
			else
			{
				return NULL;
			}
		}
		else if(root->left!=NULL&&root->right==NULL)
		{
			return findindex(root->left, index);		
		}
		else
		{
			return NULL;
		}
	}
}

void delet(struct node *del, struct node *root, int index) //刪除 del:要刪除的點 root:整個tree的root index:目前總共節點數 
{
	struct node *lastnode=findindex(root, index);
	del->data=lastnode->data;
	check(del);
	if(lastnode->parent!=NULL)
	{
		struct node *p=lastnode->parent;
		if(lastnode->index%2==0)
		{
			p->left=NULL;
		}
		else
		{
			p->right=NULL;
		}
		lastnode->parent=NULL;
	}
	else
	{
		root=NULL;
		del=NULL;
	}
}

void print(struct node *root) //中序印出 
{
	if(root->left)
		print(root->left);
	//printf("%d\t", root->index);
	printf("%d\t", root->data); 
	if(root->right)
		print(root->right);
}

int main()
{
	struct node *root=NULL;
	struct node *newnode=NULL;
	struct node *temp=NULL;
	int data;
	int index=0;
	
	bool run = 1;
	while(run)
	{
		char func;
		printf(" 1.新增\t2.刪除\t3.離開  請選擇你的動作 :\n");
		scanf("%s",&func);
		while(func!=49&&func!=50&&func!=51)
		{
			printf("請輸入正確的選項!\n\n");
			printf(" 1.新增\t2.刪除\t3.離開  請選擇你的動作 :\n");
			scanf("%s",&func);
		}
		
		switch(func)
		{
			case '1':
				index++;
				printf("\n你選擇新增\n");
				printf("請輸入數字：\n");
				scanf("%d",&data);
				if(root==NULL) //空tree
				{
					root=createnode();
					root->data=data;
					root->index=index;
				}
				else //有root
				{
					newnode=createnode();
					newnode->data=data;
					newnode->index=index;
//========================================================
					temp=insert(root, newnode->index); //回傳要新增位置的parent 
//========================================================
					if(index%2==0) //偶數放左 
						temp->left=newnode;
					else           //奇數放右
						temp->right=newnode;
					newnode->parent=temp;
//========================================================
					check(newnode); //檢查大小 
//========================================================
				}
				printf("新增完成\n");
				print(root);
				printf("\n\n");
				break;
			case '2':
				printf("\n你選擇刪除\n");
				if(root==NULL) //空的
					printf("沒有資料!\n\n");
				else //不是空的
				{
					printf("請輸入要刪除的數字:\n");
					scanf("%d",&data);
					temp=finddata(root, data); //找出要刪除的點 
					if(temp!=NULL)
					{
						delet(temp, root, index); //刪除
						index--;
						if(index==0)
						{
							root=NULL;
						}
						printf("刪除完成!\n");
						if(root!=NULL)
						{
							print(root);
							printf("\n\n");	
						}
					}
					else
					{
						printf("找不到資料!\n\n");
					}
				}
				break;
			case '3':
				printf("\n你選擇離開");
				run = 0;
				break;
		}
	}
    return 0;
}
