#include<stdio.h>
#include<stdlib.h>
struct node
{
	int data;
	struct node *left,*right;
};
struct node *root;
void insert(int d)
{
	struct node *t,*parent;
	t=(struct node *)malloc(sizeof(struct node));
	t->data=d;
	t->left = t->right = 0;
	parent = root;
	if(root == NULL)
		root=t;
	else
	{
		struct node *current = root;
		while(current)
		{	
			parent = current;
			if(t->data > current->data)
				current = current->right;
			else
				current = current->left;
		}
		if(t->data > parent->data)
			parent->right = t; 
		else
			parent->left = t;
	}
}
void deletetree(struct node *t)
{
	if(t == NULL)
		return;
	deletetree(t -> left);
	deletetree(t -> right);
	printf("deleting node data:%d\n",t->data);
	free(t);
}
struct node *minvalue(struct node *node)
{
	struct node *current = node;
	while(current->left)
		current = current->left;
	return current;
} 
struct node *maxvalue(struct node *node)
{
	struct node *current = node;
	while(current->right)
		current = current->right;
	return current;
}
struct node *deletenode(struct node *root,int data)
{
	struct node *temp;
	if(root == NULL)
		return root;
	if(data < root->data)
		root->left = deletenode(root->left,data);
	else if(data > root->data)	
		root->right = deletenode(root->right,data);
	else
	{
		if(root->left == NULL)
		{
			temp = root->right;
			free(root);
			return temp;
		}
		else if(root->right == NULL)
		{
			temp = root->left;
			free(root);	
			return temp;
		}
		temp=minvalue(root->right);
		root->data = temp->data;
		root->right = deletenode(root->right,temp->data);
	}
	return root;
}
int leaves(struct node *t)
{
	if(t==NULL)
		return 0;
	if(t->left==NULL && t->right==NULL)
		return 1;
	return leaves(t->left)+leaves(t->right);
}
int nonleaves(struct node*t)
{
	if(t==NULL)
	return 0;
	if(t->left==NULL&& t->right==NULL)
	return 0;
	return 1+nonleaves(t->left)+nonleaves(t->right);
}
int count(struct node *t)
{
	if(t)
	{
		int l,r;
		l=count(t->left);
		r=count(t->right);
		return 1+l+r;
	}
}
int fullnode(struct node *t)
{
	if(!t)
		return 0;
	if(!t->left && !t->right)
		return 0;
	return fullnode(t->left)+fullnode(t->right)+((t->left &&t->right)?1:0);
}
int height(struct node* t)
{
	int l,r;
	if(!t)
		return 0;
	if(!t->left && !t->right)
		return 0;
	l=height(t->left);
	r=height(t->right);
	return (1+(l>r)?l:r);
}
int balanced(struct node *t)
{
	if(!t)
		return 1;
	if(!t->left && !t->right)
		return 1;
	else if(t->left && t->right)
		return balanced(t->left)&&balanced(t->right);
	else
		return 0;
}
void inorder(struct node *t)
{
	if(t)
	{
		inorder(t->left);
		printf("%d ",t->data);
		inorder(t->right);
	}
}
void preorder(struct node *t)
{
	if(t)
	{
		printf("%d ",t->data);
		preorder(t->left);	
		preorder(t->right);	
	}
}
void postorder(struct node *t)
{
	if(t)
	{
		postorder(t->left);
		postorder(t->right);
		printf("%d ",t->data);
	}
}
struct node *search(struct node *root,int data)
{
	if(root == NULL)
		return NULL;
	if(data > root->data)
		return search(root->right,data);
	else if(data < root->data)
		return search(root->left,data);
	else
		return root;
}
void main()
{
	int n,root_data,num,num1,op;
	char ch1,ch2;
	struct node *p,*ret;
	root=(struct node *)malloc(sizeof(struct node));
	root->left = root->right = 0;
	do{
	printf("select the option\n1)insert 2)inorder\n3)deletenode 4)deletetree\n5)search 6)count\n7)leaves 8)nonleaves\n");
	printf("9)fullnode 10)height 11)balanced\n");
		scanf(" %d",&op);
		switch(op)
		{		
			case 1:        printf("enter the root data=");
				       scanf("%d",&root_data);
				       root->data = root_data;
				       do{    
					       printf("enter the data:");
					       scanf("%d",&n);
					       insert(n);
					       printf("press y for more node:");
					       scanf(" %c",&ch1);
				       }while(ch1 == 'y');
				       break;
			case 2:inorder(root);	
			       printf("\n");	break;
			case 3: printf("enter the data for delete:");
				scanf("%d",&num1);
				deletenode(root,num1);
				inorder(root);
				printf("\n");	
				break;
			case 4:deletetree(root);	break;
			case 5:printf("enter the data for search:");
			       scanf("%d",&num);	
			       ret = search(root,num);
			       if(ret == NULL)
				       printf("empty tree\n");
			       else
				       printf("element is %d present\n",*ret);
			       break;
			case 6:n=count(root);
				printf("%d\n",n);
				break;
			case 7:n=leaves(root);
				printf("%d\n",n);
				break;
			case 8:n=nonleaves(root);
				printf("%d\n",n);
				break;
			case 9:n=fullnode(root);
				printf("%d\n",n);
				break;
			case 10:n=height(root);
				printf("%d\n",n);
				break;
			case 11:n=balanced(root);
				if(!n)
				printf("not balanced\n");
				else
				printf("balanced\n");	
				break;
		}
		printf("press z for terminate:");
		scanf(" %c",&ch2); 
	}while(ch2 != 'z');
}
