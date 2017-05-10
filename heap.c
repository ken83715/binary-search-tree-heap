#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct node //�w�q���c
{
    int data; //�� 
    int index; //���� 
    struct node *left;
    struct node *right;
    struct node *parent; //parent node 
};

struct node *createnode(void) //�гy�s�Ŷ�
{
	struct node *newnode;
	newnode=(struct node *) malloc(sizeof(struct node));
	newnode->left=NULL;
	newnode->right=NULL;
	newnode->parent=NULL;
	return newnode;
}

struct node *insert(struct node *root, int n) //n������(index)
{
	if(n/2!=1) //�٨S��̫᪺�l�� 
	{
		struct node *ptr=insert(root,n/2);      //                                    1
		if(n%2!=0)                              //                    2                                3
		{                                       //            4               5                6                7
			if(ptr->right!=NULL)                //        8       9       10      11      12      13       14       15
				ptr=ptr->right;                 //�l��    000     100     010    110     001     101      011      111 
		}
		else
		{
			if(ptr->left!=NULL)
				ptr=ptr->left;
		}
		return ptr;
	}
	else //��̫᪺�l�ƤF
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

void check(struct node *newnode) //�ˬd�W�U�j�p
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
	if(newnode->left!=NULL&&newnode->right!=NULL) //���l�k�l���� 
	{
		struct node *leftc=newnode->left;
		struct node *rightc=newnode->right;
		if(leftc->data>rightc->data) //���l��k�l�j
		{
			if(newnode->data<leftc->data)
			{
				int temp=newnode->data;
				newnode->data=leftc->data;
				leftc->data=temp;
				check(leftc);
			}
		}
		else //���l��k�l�p
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
	else if(newnode->left!=NULL&&newnode->right==NULL) //�u�����l 
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

struct node *finddata(struct node *root, int data) //�j�M�ƭ� 
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

struct node *findindex(struct node *root, int index) //�j�M���� 
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

void delet(struct node *del, struct node *root, int index) //�R�� del:�n�R�����I root:���tree��root index:�ثe�`�@�`�I�� 
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

void print(struct node *root) //���ǦL�X 
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
		printf(" 1.�s�W\t2.�R��\t3.���}  �п�ܧA���ʧ@ :\n");
		scanf("%s",&func);
		while(func!=49&&func!=50&&func!=51)
		{
			printf("�п�J���T���ﶵ!\n\n");
			printf(" 1.�s�W\t2.�R��\t3.���}  �п�ܧA���ʧ@ :\n");
			scanf("%s",&func);
		}
		
		switch(func)
		{
			case '1':
				index++;
				printf("\n�A��ܷs�W\n");
				printf("�п�J�Ʀr�G\n");
				scanf("%d",&data);
				if(root==NULL) //��tree
				{
					root=createnode();
					root->data=data;
					root->index=index;
				}
				else //��root
				{
					newnode=createnode();
					newnode->data=data;
					newnode->index=index;
//========================================================
					temp=insert(root, newnode->index); //�^�ǭn�s�W��m��parent 
//========================================================
					if(index%2==0) //���Ʃ� 
						temp->left=newnode;
					else           //�_�Ʃ�k
						temp->right=newnode;
					newnode->parent=temp;
//========================================================
					check(newnode); //�ˬd�j�p 
//========================================================
				}
				printf("�s�W����\n");
				print(root);
				printf("\n\n");
				break;
			case '2':
				printf("\n�A��ܧR��\n");
				if(root==NULL) //�Ū�
					printf("�S�����!\n\n");
				else //���O�Ū�
				{
					printf("�п�J�n�R�����Ʀr:\n");
					scanf("%d",&data);
					temp=finddata(root, data); //��X�n�R�����I 
					if(temp!=NULL)
					{
						delet(temp, root, index); //�R��
						index--;
						if(index==0)
						{
							root=NULL;
						}
						printf("�R������!\n");
						if(root!=NULL)
						{
							print(root);
							printf("\n\n");	
						}
					}
					else
					{
						printf("�䤣����!\n\n");
					}
				}
				break;
			case '3':
				printf("\n�A������}");
				run = 0;
				break;
		}
	}
    return 0;
}
