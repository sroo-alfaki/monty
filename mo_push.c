#include "monty.h"
/**
 *add_to_stack - Adds a node to the stack.
 * @new_node: Pointer to the new node.
 * @ln: Interger representing the line number of of the opcode.
 */
void add_stack(stack_t **head, __attribute__((unused))unsigned int ln)
{
	stack_t *new_node = NULL;

	if (head == NULL)
	{
		*head = new_node;
		return;
	}
	*head = new_node;
	(*head)->next = new_node;
	new_node->prev = *head;
}
/**
 * print_stack - Adds a node to the stack.
 * @stack: Pointer to a pointer pointing to top node of the stack.
 * @line_number: line number of  the opcode.
 */
void pr_stack(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp;

	(void) line_number;
	if (stack == NULL)
		exit(EXIT_FAILURE);
	tmp = *stack;
	while (tmp != NULL)
	{
		printf("%d\n", tmp->n);
		tmp = tmp->next;
	}
}

