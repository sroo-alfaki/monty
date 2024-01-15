#include "monty.h"
/**
 *open_file - opens a file
 *@file_name: the file namepath
 *Return: void
 */
void op_file(char *file_name, stack_t **head)
{
	FILE *fd = fopen(file_name, "r");

	(void)head;
	if (file_name == NULL || fd == NULL)
		err(2, file_name);

	read_file(fd);
	fclose(fd);
}
/**
 *read_file - reads a file
 *@fd: pointer to file descriptor
 *Return: void
 */
void read_file(FILE *fd)
{
	int line_number, format = 0;
	char *buffer = NULL;
	size_t len = 0;

	for (line_number = 1; getline(&buffer, &len, fd) != -1; line_number++)
	{
		format = par_line(buffer, line_number, format);
	}
	free(buffer);
}
/**
 *parse_line - function to call
 *@buffer: line from the file
 *@line_number: line number
 *@format:  storage format
 *Return: Returns 0 if the opcode is stack. 1 if queue.
 */
int par_line(char *buffer, int line_number, int format)
{
	char *opcode, *value;
	const char *delim = "\n ";

	if (buffer == NULL)
		err(4);

	opcode = strtok(buffer, delim);
	if (opcode == NULL)
		return (format);
	value = strtok(NULL, delim);

	if (strcmp(opcode, "stack") == 0)
		return (0);
	if (strcmp(opcode, "queue") == 0)
		return (1);

	find_fu(opcode, value, line_number, format);
	return (format);
}
/**
 *find_func - find the appropriate function for the opcode
 *@opcode: opcode
 *@value: argument of opcode
 *@format:  storage format. If 0 Nodes will be entered as a stack.
 *@ln: line number
 *Return: void
 */
void find_fu(char *opcode, char *value, int ln, int format)
{
	int i;
	int flag;

	instruction_t fu_list[] = {
		{"push", add_stack},
		{"pall", pr_stack},
		{"pint", pr_top},
		{"pop", pop_top},
		{"nop", nop},
		{"swap", swap_nod},
		{"add", add_nod},
		{NULL, NULL}
	};

	if (opcode[0] == '#')
		return;

	for (flag = 1, i = 0; fu_list[i].opcode != NULL; i++)
	{
		if (strcmp(opcode, fu_list[i].opcode) == 0)
		{
			call_fu(fu_list[i].f, opcode, value, ln, format);
			flag = 0;
		}
	}
	if (flag == 1)
		err(3, ln, opcode);
}
/**
 * call_fun - Calls the required function.
 * @func: Pointer to the function that is about to be called.
 * @op: string representing the opcode.
 * @val: string representing a numeric value.
 * @ln: line numeber for the instruction.
 * @format: Format specifier.
 */
void call_fu(op_func func, char *op, char *val, int ln, int format)
{
	stack_t *node;
	int flag;
	int i;
	stack_t *head = NULL;

	flag = 1;
	if (strcmp(op, "push") == 0)
	{
		if (val != NULL && val[0] == '-')
		{
			val = val + 1;
			flag = -1;
		}
		if (val == NULL)
			err(5, ln);
		for (i = 0; val[i] != '\0'; i++)
		{
			if (isdigit(val[i]) == 0)
				err(5, ln);
		}
		node = create_node(atoi(val) * flag);
		if (format == 0)
			func(&node, ln);
		if (format == 1)
			add_queue(&node, ln, &head);
	}
	else
		func(&head, ln);
}
