#include<stdio.h>
#include<stdlib.h>

typedef struct listNode *listPointer;
typedef struct listNode{
	int data; //數值 
	int index; //在tree中的索引 
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

listPointer insert(listPointer root, int n) //n為要新增的位置索引(index)
{
	if(n / 2 != 1) //還沒除完
	{
		listPointer ptr = insert(root, n / 2);  //                                    1
		if(n % 2 != 0)                          //                    2                                3
		{                                       //            4               5                6                7
			if(ptr->right != NULL)          //        8       9       10      11      12      13       14       15
				ptr = ptr->right;       //餘數    000     100      010    110     001      101      011      111 
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

void check(listPointer newnode) //檢查上下大小
{
	if(newnode->parent != NULL) //往上檢查 
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
	if(newnode->left != NULL && newnode->right != NULL) //左子右子都有 
	{
		listPointer leftc = newnode->left;
		listPointer rightc = newnode->right;
		if(leftc->data > rightc->data) //左子比右子大
		{
			if(newnode->data < leftc->data) //交換 
			{
				int temp = newnode->data;
				newnode->data = leftc->data;
				leftc->data = temp;
				check(leftc);
			}
		}
		else //左子比右子小
		{
			if(newnode->data < rightc->data) //交換 
			{
				int temp = newnode->data;
				newnode->data = rightc->data;
				rightc->data = temp;
				check(rightc);
			}
		}
	}
	else if(newnode->left != NULL && newnode->right == NULL) //只有左子 
	{
		listPointer leftc = newnode->left;
		if(newnode->data < leftc->data) //交換
		{
			int temp = newnode->data;
			newnode->data = leftc->data;
			leftc->data = temp;
			check(leftc);
		}
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

listPointer findindex(listPointer root, int index) //搜尋索引 
{
	if(root->index == index)
	{
		return root;
	}
	else
	{
		if(root->left != NULL && root->right != NULL) //有左子樹有右子樹 
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
		else if(root->left != NULL && root->right == NULL) //不會有無左子樹有右子樹的情況發生 只考慮無右子樹有左子樹 
		{
			return findindex(root->left, index);
			
		}
		else //左右子樹都沒有
		{
			return NULL;
		}
	}
}

void delet(listPointer root, listPointer lastnode) //刪除 root:整個tree的root lastnode:最後一個節點
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
	else //只剩下root
	{
		free(root);
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
				if(root == NULL) //空tree
				{
					root = createnode();
					root->data = data;
					root->index = count;
				}
				else //有root
				{
					newnode = createnode();
					newnode->data = data;
					newnode->index = count;
//========================================================
					temp = insert(root, newnode->index); //回傳要新增位置的parent 
//========================================================
					if(count % 2 == 0) //偶數放左 
						temp->left = newnode;
					else               //奇數放右
						temp->right = newnode;
					newnode->parent = temp;
//========================================================
					check(newnode); //檢查大小 
//========================================================
				}
				break;
			case 2:
				if(root == NULL) //空的
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
				if(root == NULL) //空的
				{
					printf("Empty\n");
					break;
				}
				printf("delete root: %d\n", root->data);
				temp = findindex(root, count); //找最後一個節點 
				delet(root, temp); //刪除
				count--;
				if(count == 0)
					root = NULL; 
				break;
			case 4:
				if(root == NULL) //空的
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
