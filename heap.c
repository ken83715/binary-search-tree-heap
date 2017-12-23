#include<stdio.h>
#include<stdlib.h>

typedef struct listNode *listPointer;
typedef struct listNode{
	int data; //�ƭ� 
	int index; //�btree�������� 
	listPointer left;
	listPointer right;
	listPointer parent; //parent node
} node;

listPointer createnode()
{
	listPointer newnode;
	newnode = (listPointer)malloc(sizeof(node));
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->parent = NULL;
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

void check(listPointer newnode) //�ˬd�W�U�j�p
{
	if(newnode->parent != NULL) //���W�ˬd 
	{
		listPointer p = newnode->parent;
		if(newnode->data > p->data)
		{
			int temp = newnode->data;
			newnode->data = p->data;
			p->data = temp;
			check(p);
		}
	}
	if(newnode->left != NULL && newnode->right != NULL) //���l�k�l���� 
	{
		listPointer leftc = newnode->left;
		listPointer rightc = newnode->right;
		if(leftc->data > rightc->data) //���l��k�l�j
		{
			if(newnode->data < leftc->data) //�洫 
			{
				int temp = newnode->data;
				newnode->data = leftc->data;
				leftc->data = temp;
				check(leftc);
			}
		}
		else //���l��k�l�p
		{
			if(newnode->data < rightc->data) //�洫 
			{
				int temp = newnode->data;
				newnode->data = rightc->data;
				rightc->data = temp;
				check(rightc);
			}
		}
	}
	else if(newnode->left != NULL && newnode->right == NULL) //�u�����l 
	{
		listPointer leftc = newnode->left;
		if(newnode->data < leftc->data) //�洫
		{
			int temp = newnode->data;
			newnode->data = leftc->data;
			leftc->data = temp;
			check(leftc);
		}
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

listPointer findindex(listPointer root, int index) //�j�M���� 
{
	if(root->index == index)
	{
		return root;
	}
	else
	{
		if(root->left != NULL && root->right != NULL) //�����l�𦳥k�l�� 
		{
			listPointer leftc = findindex(root->left, index);
			listPointer rightc = findindex(root->right, index);
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
			return findindex(root->left, index);
			
		}
		else //���k�l�𳣨S��
		{
			return NULL;
		}
	}
}

void delet(listPointer root, listPointer lastnode) //�R�� root:���tree��root lastnode:�̫�@�Ӹ`�I
{
	root->data = lastnode->data;
	check(root);
	if(lastnode->parent != NULL)
	{
		listPointer p = lastnode->parent;
		if(lastnode->index % 2 == 0)
		{
			p->left = NULL;
		}
		else
		{
			p->right = NULL;
		}
		free(lastnode);
	}
	else //�u�ѤUroot
	{
		free(root);
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
	listPointer root = NULL;
	listPointer newnode = NULL;
	listPointer temp = NULL;
	int data;
	int count = 0;
	int run = 1;
	
	while(run)
	{
		int func;
		printf("1.insert 2.search 3.delete 4.print 5.leave:\n");
		scanf("%d", &func);
		
		switch(func)
		{
			case 1:
				count++;
				printf("enter the number:\n");
				scanf("%d", &data);
				if(root == NULL) //��tree
				{
					root = createnode();
					root->data = data;
					root->index = count;
				}
				else //��root
				{
					newnode = createnode();
					newnode->data = data;
					newnode->index = count;
//========================================================
					temp = insert(root, newnode->index); //�^�ǭn�s�W��m��parent 
//========================================================
					if(count % 2 == 0) //���Ʃ� 
						temp->left = newnode;
					else               //�_�Ʃ�k
						temp->right = newnode;
					newnode->parent = temp;
//========================================================
					check(newnode); //�ˬd�j�p 
//========================================================
				}
				break;
			case 2:
				if(root == NULL) //�Ū�
				{
					printf("Empty\n");
					break;
				}
				printf("enter the number:\n");
				scanf("%d", &data);
				temp = finddata(root, data);
				if(temp != NULL)
					printf("found %d\n", temp->data);
				else
					printf("Not found\n");
				break;
			case 3:
				if(root == NULL) //�Ū�
				{
					printf("Empty\n");
					break;
				}
				printf("delete root: %d\n", root->data);
				temp = findindex(root, count); //��̫�@�Ӹ`�I 
				delet(root, temp); //�R��
				count--;
				if(count == 0)
					root = NULL; 
				break;
			case 4:
				if(root == NULL) //�Ū�
				{
					printf("Empty\n");
					break;
				}
				print(root, 1);
				break;
			case 5:
				run = 0;
				break;
		}
	}
    return 0;
}
