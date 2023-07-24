 #include "shell.h"

/**
 * add_node - it will add a node at the beginning of the list
 * @head: the address of the ptr to head/lead node
 * @str: declares the string field of the node
 * @num: the node index which the history will use
 *
 * Return: Returns the list size
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->number = num;
	if (str)
	{
		new_head->string = _strdup(str);
		if (!new_head->string)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - It will add node to the end list
 * @head: the address of the ptr to node
 * @str: declares the string field
 * @num: the node index which the history
 * Return: Returns the list size
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->number = num;
	if (str)
	{
		new_node->string = _strdup(str);
		if (!new_node->string)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_str - this will print string element of linked list
 * @h: ptr to head/lead node
 *
 * Return: Returns the list size
 */
size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->string ? h->string : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * delete_node_at_index - at a given index,
 * it will delete the identified node.
 * @head: address of ptr to head/lead node
 * @index: the index of the identified node to be deleted
 * Return: A value of 1 is returned on successful execution,
 * 0 is returned on execution failure.
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->string);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->string);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - all of the nodes of list are freed
 * @head_ptr: address of ptr to head/lead node
 * Return: Returns a void value
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->string);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
