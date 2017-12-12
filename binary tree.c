#include<stdio.h>
#include<stdlib.h>

typedef struct listNode *listPointer;
typedef struct listNode{
	int data; //�ƭ� 
	int index; //�btree�������� 
	listPointer left;
	listPointer right;
} node;

listPointer createnode()
{
	listPointer newnode;
	newnode = (listPointer)malloc(sizeof(node));
	newnode->left = NULL;
	newnode->right = NULL;
	return newnode;
}

listPointer insert(listPointer root, int n) //n���n�s�W����m����(index)
{
	if(n / 2 != 1) //�٨S����
	{
		listPointer ptr = insert(root, n / 2);  //                                    1
		if(n % 2 != 0)                          //                    2                                3
		{                                       //            4               5                6                7
			if(ptr->right != NULL)              //        8       9       10      11      12      13       14       15
				ptr = ptr->right;               //�l��    000     100     010    110     001     101      011      111 
		}                                       //�l�ƭn�˵۬� 0���� 1���k 
		else
		{
			if(ptr->left != NULL)
				ptr = ptr->left;
		}
		return ptr;
	}
	else //�����F
	{
		if(n % 2 != 0)
		{
			if(root->right != NULL)
				root = root->right;
		}
		else
		{
			if(root->left != NULL)
				root = root->left;
		}
		return root;
	}
}

listPointer finddata(listPointer root, int data) //�j�M�ƭ� 
{
	if(root->data == data)
	{
		return root;
	}
	else
	{
		if(root->left != NULL && root->right != NULL) //�����l�𦳥k�l�� 
		{
			listPointer leftc = finddata(root->left, data);
			listPointer rightc = finddata(root->right, data);
			if(leftc != NULL)
			{
				return leftc;
			}
			else if(rightc != NULL)
			{
				return rightc;
			}
			else
			{
				return NULL;
			}
		}
		else if(root->left != NULL && root->right == NULL) //���|���L���l�𦳥k�l�𪺱��p�o�� �u�Ҽ{�L�k�l�𦳥��l�� 
		{
			return finddata(root->left, data);
			
		}
		else //���k�l�𳣨S��
		{
			return NULL;
		}
	}
}

void print(listPointer p, int level) //�L�X 
{
	if(p->right != NULL)
		print(p->right, level + 1);
	int i;
	for(i = 1; i < level; i++)
		printf("\t");
	printf("%d\n", p->data);
	if(p->left != NULL)
		print(p->left, level + 1);
}

int main()
{
	listPointer root = NULL, temp = NULL, newnode = NULL;
	
	int run = 1, f, data, index = 0;
	
	while(run)
	{
		printf("1.�s�W��� 2.�j�M 3.�L�X 4.���} �п��:\n");
		scanf("%d", &f);
		switch(f)
		{
			case 1:
				index++;
				printf("�A��ܷs�W �п�J�Ʀr�G\n");
				scanf("%d", &data);
				if(root == NULL) //��tree
				{
					root = createnode();
					root->data = data;
					root->index = index;
				}
				else //��root
				{
					newnode = createnode();
					newnode->data = data;
					newnode->index = index;
//========================================================
					temp = insert(root, newnode->index); //�^�ǭn�s�W��m��parent 
//========================================================
					if(index % 2 == 0) //���Ʃ�
						temp->left = newnode;
					else               //�_�Ʃ�k
						temp->right = newnode;
				}
				printf("�s�W����\n\n");
				break;
			case 2:
				if(root == NULL)
				{
					printf("Empty!\n\n");
					break;
				}
				printf("�A��ܷj�M �п�J�Ʀr�G\n");
				scanf("%d", &data);
//========================================================				
				temp = finddata(root, data); //��X�n�j�M���I
//========================================================
				if(temp != NULL)			
					printf("���%d\n", temp->data);				
				else				
					printf("�䤣����!\n\n");
				break;
			case 3:
				if(root == NULL)
				{
					printf("Empty!\n\n");
					break;
				}
				print(root, 1);
				printf("\n\n");
				break;
			case 4:
				run = 0;
				break;
		}
	}
}
