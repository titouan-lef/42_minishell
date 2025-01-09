

static void	tree_traversal_in_order(t_tree *tree)
{
	if (tree != NULL)
	{
		tree_traversal_in_order(tree->left);
		ft_printf("node : %d, value : %s\n", tree->token.name, tree->token.value[0]);
		tree_traversal_in_order(tree->right);
	}
}

static void	breadth_first_search(t_tree *tree)
{
	typedef struct s_element_test
	{
		t_tree 					*tree;
		int						depth;
		struct s_element_test	*next;
	}	t_element_test;

	typedef struct s_queue_test
	{
		t_element_test	*head;
		t_element_test	*tail;
	}	t_queue_test;

	t_queue_test	queue;
	t_element_test	*element;
	t_tree			*node;
	int				i = -1;
	int				depth;

	// create
	queue.head = NULL;
	queue.tail = NULL;
	//--//
	// push
	element = (t_element_test *)malloc(sizeof(t_element_test));
	element->tree = tree;
	element->depth = 0;
	element->next = NULL;
	if (queue.head == NULL)
		queue.head = element;
	else
		queue.tail->next = element;
	queue.tail = element;
	//--//
	while (queue.head != NULL)
	{
		// pop
		element = queue.head;
		queue.head = element->next;
		depth = element->depth;
		node = element->tree;
		free(element);
		if (queue.head == NULL)
			queue.tail = NULL;
		//--//
		if (depth != i)
		{
			++i;
			ft_printf("\nDepth : %d\n",i);
		}
		ft_printf("  - node : %s\n", node->token.value[0]);
		if (node->left != NULL)
		{
			// push
			element = (t_element_test *)malloc(sizeof(t_element_test));
			element->tree = node->left;
			element->depth = i + 1;
			element->next = NULL;
			if (queue.head == NULL)
				queue.head = element;
			else
				queue.tail->next = element;
			queue.tail = element;
			//--//
		}
		if (node->right != NULL)
		{
			// push
			element = (t_element_test *)malloc(sizeof(t_element_test));
			element->tree = node->right;
			element->depth = i + 1;
			element->next = NULL;
			if (queue.head == NULL)
				queue.head = element;
			else
				queue.tail->next = element;
			queue.tail = element;
			//--//
		}
	}
}
