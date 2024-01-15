#include "monty.h"
/**
 *add_nodes - Adds the top two elements of the stack.
 *@stack: Pointer to a pointer pointing to top node of the stack.
 *@line_number: Interger representing the line number of of the opcode.
 */
void add_nod(stack_t **stack, unsigned int line_number)
{
	int s;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		more_err(8, line_number, "add");

	(*stack) = (*stack)->next;
	s = (*stack)->n + (*stack)->prev->n;
	(*stack)->n = s;
	free((*stack)->prev);
	(*stack)->prev = NULL;
}
