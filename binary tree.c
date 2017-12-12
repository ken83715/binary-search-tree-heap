#include<stdio.h>
#include<stdlib.h>

typedef struct listNode *listPointer;
typedef struct listNode{
	int data; //數值 
	int index; //在tree中的索引 
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

listPointer insert(listPointer root, int n) //n為要新增的位置索引(index)
{
	if(n / 2 != 1) //還沒除完
	{
		listPointer ptr = insert(root, n / 2);  //                                    1
		if(n % 2 != 0)                          //                    2                                3
		{                                       //            4               5                6                7
			if(ptr->right != NULL)              //        8       9       10      11      12      13       14       15
				ptr = ptr->right;               //餘數    000     100     010    110     001     101      011      111 
		}                                       //餘數要倒著看 0往左 1往右 
		else
		{
			if(ptr->left != NULL)
				ptr = ptr->left;
		}
		return ptr;
	}
	else //除完了
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

listPointer finddata(listPointer root, int data) //搜尋數值 
{
	if(root->data == data)
	{
		return root;
	}
	else
	{
		if(root->left != NULL && root->right != NULL) //有左子樹有右子樹 
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
		else if(root->left != NULL && root->right == NULL) //不會有無左子樹有右子樹的情況發生 只考慮無右子樹有左子樹 
		{
			return finddata(root->left, data);
			
		}
		else //左右子樹都沒有
		{
			return NULL;
		}
	}
}

void print(listPointer p, int level) //印出 
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
		printf("1.新增資料 2.搜尋 3.印出 4.離開 請選擇:\n");
		scanf("%d", &f);
		switch(f)
		{
			case 1:
				index++;
				printf("你選擇新增 請輸入數字：\n");
				scanf("%d", &data);
				if(root == NULL) //空tree
				{
					root = createnode();
					root->data = data;
					root->index = index;
				}
				else //有root
				{
					newnode = createnode();
					newnode->data = data;
					newnode->index = index;
//========================================================
					temp = insert(root, newnode->index); //回傳要新增位置的parent 
//========================================================
					if(index % 2 == 0) //偶數放左
						temp->left = newnode;
					else               //奇數放右
						temp->right = newnode;
				}
				printf("新增完成\n\n");
				break;
			case 2:
				if(root == NULL)
				{
					printf("Empty!\n\n");
					break;
				}
				printf("你選擇搜尋 請輸入數字：\n");
				scanf("%d", &data);
//========================================================				
				temp = finddata(root, data); //找出要搜尋的點
//========================================================
				if(temp != NULL)			
					printf("找到%d\n", temp->data);				
				else				
					printf("找不到資料!\n\n");
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
