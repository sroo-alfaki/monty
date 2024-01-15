#include "monty.h"
#include <stdio.h>
/**
 * main - entry point
 * @argc: arguments count
 * @argv: list of arguments
 * Return: always 0
 */
int main(int argc, char *argv[])
{
	stack_t *head = NULL;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	op_file(argv[1], &head);
	free_nod(&head);
	return (0);
}
/**
 *create_node - Creates a node.
 *@n: Number to  node.
 *Return: sucess a pointer to the node. Otherwise NULL.
 */
stack_t *create_node(int n)
{
	stack_t *node;

	node = malloc(sizeof(stack_t));
	if (node == NULL)
		err(4);
	node->next = NULL;
	node->prev = NULL;
	node->n = n;
	return (node);
}
/**
 *free_nod - Frees nodes in the stack.
 */
void free_nod(stack_t **head)
{
	stack_t *tmp = NULL;


	while (*head != NULL)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
	}
}
/**
 * add_queue - Adds a node to the queue.
 * @new_node: Pointer to the new node.
 * @ln: line number of the opcode.
 */
void add_queue(stack_t **new_node, __attribute__((unused))unsigned int ln,
stack_t **head)
{
	stack_t *tmp = *head;

	if (new_node == NULL || *new_node == NULL)
		exit(EXIT_FAILURE);
	if (tmp == NULL)
	{
		*head = *new_node;
		return;
	}
	else
		while (tmp->next != NULL)
			tmp = tmp->next;
	tmp->next = *new_node;
	(*new_node)->prev = tmp;

}
