#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node {
	struct node *right;
	struct node *left;
	struct node *father;
	float key;
} node;

typedef struct tree {
	node *root;
	int count;
} tree;

/* propotype of funtions */
node *create_node(float data);
tree *create_tree(void);
int height(node *p_node);
int balance_cal(node *p_node);
int right_rot(tree *p_tree, node *p_node);
int left_rot(tree *p_tree, node *p_node);
int balance_tree(tree *p_tree, node *p_node);
int insert_node(tree *p_tree, node *p_node);
int insert_node_data(tree *p_tree, float node_key);
int browse_NLR(node *p_node);
node *find_successor(node *p_node);
int swap(node *node1, node *node2);
int delete_node(tree *p_tree, node *p_node);
int find_element(node *p_node, float element, int *total);

/* funtions create node of AVL tree */
node *create_node(float data)
{
	node *p_node = (node *)malloc(sizeof(node));
	if (NULL == p_node)
	{
		return NULL;
	}
	else
	{
		p_node->right = NULL;
		p_node->left = NULL;
		p_node->father = NULL;
		p_node->key = data;
		return p_node;
	}
}

/* function create AVL tree */
tree *create_tree(void)
{
	tree *p_tree = (tree *)malloc(sizeof(tree));
	if (NULL == p_tree)
	{
		return NULL;
	}
	else
	{
		p_tree->root = NULL;
		p_tree->count = 0;
		return p_tree;
	}
}

/* function create height of tree from a node */
int height(node *p_node)
{
	if (NULL == p_node)
	{
		return 0;
	}
	int right_h = height(p_node->right);
	int left_h = height(p_node->left);
	return 1 + (right_h<left_h?left_h:right_h);
}

/* function calculates balance of node */
int balance_cal(node *p_node)
{
	if (NULL == p_node)
	{
		return 0;
	}
	else 
	{
		return height(p_node->left) - height(p_node->right);
	}
}

/* functions rotate left, right around a node */
int right_rot(tree *p_tree, node *p_node)
{
	if (NULL == p_node)
	{
		return -1;
	}
	if (NULL == p_node->father) /* node is root */
	{
		node *left_child = p_node->left;
		left_child->father = NULL;
		p_tree->root = left_child;
		p_node->father = left_child;

		if (NULL != left_child->right)
		{
			node *tmp_node = left_child->right;
			left_child->right = p_node;
			p_node->left = tmp_node;
			tmp_node->father = p_node;
			return 0;
		}
		else
		{
			left_child->right = p_node;
			p_node->left = NULL;
			return 0;
		}
	}
	else
	{
		node *father_node = p_node->father;
		node *left_child = p_node->left;
		left_child->father = father_node;
		if (father_node->left == p_node)
		{
			father_node->left = left_child;
		}
		else
		{
			father_node->right = left_child;
		}
		p_node->father = left_child;

		if (NULL != left_child->right)
		{
			node *tmp_node = left_child->right;
			left_child->right = p_node;
			p_node->left = tmp_node;
			tmp_node->father = p_node;
			return 0;
		}
		else
		{
			left_child->right = p_node;
			p_node->left = NULL;
			return 0;
		}
	}
}

int left_rot(tree *p_tree, node *p_node)
{
	if (NULL == p_node)
	{
		return -1;
	}
	if (NULL == p_node->father) /* node is root */
	{
		node *right_child = p_node->right;
		p_tree->root = right_child;
		right_child->father = NULL;
		p_node->father = right_child;

		if (NULL != right_child->left)
		{
			node *tmp_node = right_child->left;
			right_child->left = p_node;
			p_node->right = tmp_node;
			tmp_node->father = p_node;
			return 0;
		}
		else
		{
			right_child->left = p_node;
			p_node->right = NULL;		
			return 0;
		}
	}	
	else 
	{
		node *father_node = p_node->father;
		node *right_child = p_node->right;
		right_child->father = father_node;
		if (father_node->left == p_node)
		{
			father_node->left = right_child;
		}
		else
		{
			father_node->right = right_child;
		}
		p_node->father = right_child;

		if (NULL != right_child->left)
		{
			node *tmp_node = right_child->left;
			right_child->left = p_node;
			p_node->right = tmp_node;
			tmp_node->father = p_node;
			return 0;
		}
		else
		{
			right_child->left = p_node;
			p_node->right = NULL;
			return 0;
		}
	}
}

/* function balances tree */
int balance_tree(tree *p_tree, node *p_node)
{
	if (NULL == p_node || NULL == p_tree)	
	{
		return -1;
	}
	while((NULL != p_node->father) && (2 > abs(balance_cal(p_node))))
	{
		p_node = p_node->father;
	}
	if (NULL == p_node->father && (2 > abs(balance_cal(p_node))))
	{
		return 0; /* browsed to root */
	}
	else /* unbalanced */
	{
		if (0 < balance_cal(p_node)) /* heavy left */
		{
			if (height(p_node->left->left) > height(p_node->left->right))
			{
				right_rot(p_tree, p_node); /* unbalance from  left subtree of left child node */
				return 0;
			}
			else /* unbalance from right subtree of left child node */
			{
				left_rot(p_tree, p_node->left);
				right_rot(p_tree, p_node);
				return 0;
			}
		}
		else
		{
			if (height(p_node->right->right) > height(p_node->right->left))
			{
				left_rot(p_tree, p_node); /* unbalance from right subtree of right child node */
				return 0;
			}
			else /* unbalance from left subtree of right child node */
			{
				right_rot(p_tree, p_node->right);
				left_rot(p_tree, p_node);
				return 0;
			}
		}
	}
}

/* function insert node */
int insert_node(tree *p_tree, node *p_node)
{
	if (NULL == p_tree || NULL == p_node)
	{
		return -1;
	}
	if (0 == p_tree->count)
	{
		p_tree->root = p_node;
		p_tree->count++;
		return 0;
	}
	else
	{
		node *father_node = p_tree->root;
		node *tmp_node = father_node;
		while (NULL != tmp_node)
		{
			father_node = tmp_node;
			if (p_node->key > tmp_node->key)
			{
				tmp_node = tmp_node->right;
			}
			else
			{
				tmp_node = tmp_node->left;
			}
		}
		if (p_node->key > father_node->key)
		{
			father_node->right = p_node;
			p_node->father = father_node;
			p_tree->count++;
			balance_tree(p_tree, father_node);
			return 0;
		}
		else
		{
			father_node->left = p_node;
			p_node->father = father_node;
			p_tree->count++;
			balance_tree(p_tree, father_node);
			return 0;
		}
	}
}

int insert_node_data(tree *p_tree, float node_key)
{
	node *p_node = create_node(node_key);
	return insert_node(p_tree, p_node);
}

/* function find successor of node, which has min key greater than node key */
node *find_successor(node *p_node)
{
	if (NULL == p_node)
		return NULL;
	node *tmp_node = p_node->right;
	while (NULL != tmp_node->left)
	{
		tmp_node = tmp_node->left;
	}
	return tmp_node;
}

/* funtion swaps key of two nodes */
int swap(node *node1, node *node2)
{
	if (NULL == node1 || NULL == node2)
		return -1;
	float tmp_key;
	tmp_key = node1->key;
	node1->key = node2->key;
	node2->key = tmp_key;
	return 0;
}

/* function delete a node from AVL tree */
int delete_node(tree *p_tree, node *p_node)
{
	if (NULL == p_tree || NULL == p_node)
		return -1;
	if (p_tree->root == p_node) /* node is root */
	{
		if (NULL == p_node->left && NULL == p_node->right)
		{
			free(p_node);
			p_tree->root = NULL;
			p_tree->count--;
			return 0;
		}
		else if (NULL == p_node->left && NULL != p_node->right)
		{
			node *tmp_node = p_node->right;
			free(p_node);
			p_tree->root = tmp_node;
			p_tree->count--;
			tmp_node->father = NULL;
			return 0;
		}
		else if (NULL != p_node->left && NULL == p_node->right)
		{
			node *tmp_node = p_node->left;
			free(p_node);
			p_tree->root = tmp_node;
			p_tree->count--;
			tmp_node->father = NULL;
			return 0;
		}
		else
		{
			node *tmp_node = find_successor(p_node);
			swap(tmp_node, p_node);
			node *father_node = tmp_node->father;
			if (father_node->left == tmp_node)
			{
				father_node->left = NULL;
			}
			else
			{
				father_node->right = NULL;
			}
			free(tmp_node);
			p_tree->count--;
			balance_tree(p_tree, father_node);
			return 0;
		}
	}
	else /* node is not root */
	{
		if (NULL == p_node->left && NULL == p_node->right)
		{
			node *father_node = p_node->father;
			if (father_node->left == p_node)
			{
				father_node->left = NULL;
			}
			else
			{
				father_node->right = NULL;
			}
			free(p_node);
			p_tree->count--;
			balance_tree(p_tree, father_node);
			return 0;
		}
		else if (NULL == p_node->left && NULL != p_node->right)
		{
			node *father_node = p_node->father;
			node *right_node = p_node->right;
			if (father_node->left == p_node)
			{
				father_node->left = right_node;
			}
			else 
			{
				father_node->right = right_node;
			}
			right_node->father = father_node;
			free(p_node);
			p_tree->count--;
			balance_tree(p_tree, right_node);
			return 0;
		}
		else if (NULL != p_node->left && NULL == p_node->right)
		{
			node *father_node = p_node->father;
			node *left_node = p_node->left;
			if (father_node->left == p_node)
			{
				father_node->left = left_node;
			}
			else
			{
				father_node->right = left_node;
			}
			left_node->father = father_node;
			free(p_node);
			p_tree->count--;
			balance_tree(p_tree, left_node);
			return 0;
		}
		else
		{
			node *successor_node = find_successor(p_node);
			node *father_node = successor_node->father;
			swap(successor_node, p_node);
			if (father_node->left == successor_node)
			{
				father_node->left = NULL;
			}
			else
			{
				father_node->right = NULL;
			}
			free (successor_node);
			p_tree->count--;
			balance_tree(p_tree, father_node);
			return 0;
		}
	}
}

/* function finds total number of an element in tree */
int find_element(node *p_node, float element, int *total)
{
	if (NULL == p_node || NULL == total)
		return 0;
	node *tmp_node = p_node;
	while (NULL != tmp_node && (tmp_node->key - element) != 0.00)
	{
		if (tmp_node->key < element)
		{
			tmp_node = tmp_node->right;
		}
		else
		{
			tmp_node = tmp_node->left;
		}
	}
	if (NULL != tmp_node)
	{
		(*total)++;
		find_element(tmp_node->left, element, total);
	}
	return *total;
}

/* function browses NLR */
int browse_NLR(node *p_node)
{
	if (NULL == p_node)
		return -1;
	node *tmp_node = p_node;
	printf("%3.2f	", tmp_node->key);
	browse_NLR(tmp_node->left);
	browse_NLR(tmp_node->right);
	return 0;
}

/* main function */
int main(int argc, char *argv[])
{
	tree *AVL_tree = create_tree();

	insert_node_data(AVL_tree, 1.5);
	browse_NLR(AVL_tree->root);
	printf("\n");
	insert_node_data(AVL_tree, 1.7);
	browse_NLR(AVL_tree->root);
	printf("\n");

	insert_node_data(AVL_tree, 1.9);
	browse_NLR(AVL_tree->root);
	printf("\n");

	insert_node_data(AVL_tree, 1.3);
	insert_node_data(AVL_tree, 1.2);
	insert_node_data(AVL_tree, 1.6);
	insert_node_data(AVL_tree, 1.1);
	insert_node_data(AVL_tree, 1.0);
	insert_node_data(AVL_tree, 1.2);
	insert_node_data(AVL_tree, 1.2);
	browse_NLR(AVL_tree->root);
	printf("\n");

	delete_node(AVL_tree, AVL_tree->root->right);
	delete_node(AVL_tree, AVL_tree->root->right);
	browse_NLR(AVL_tree->root);
	printf("\n");

	int total = 0;
	find_element(AVL_tree->root, 1.2, &total);
	printf("total = %d\n", total);

	return 0;
}
