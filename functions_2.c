#include "monty.h"

/**
 * mod - entry point
 * @stack: stack_t variable
 * @line_number: unsigned int variable
*/

void mod(stack_t **stack, unsigned int line_number)
{
	unsigned int module;
	(void)line_number;

	if ((*stack)->next == NULL && (*stack)->prev == NULL)
	{
		fprintf(stderr, "L<line_number>: can't mod, stack too short\n");
		exit(EXIT_FAILURE);
	}
	module = (*stack)->next->n % (*stack)->n;

	pop(stack, 0);
	pop(stack, 0);
	push(stack, module);
}

/**
 * pchar - entry point
 * @stack: stack_t variable
 * @line_number: unsigned int variable
*/

void pchar(stack_t **stack, unsigned int line_number)
{
	int letter;
	(void)line_number;

	if (stack == NULL)
	{
		fprintf(stderr, "L<line_number>: can't pchar, stack empty,\n");
		exit(EXIT_FAILURE);
	}
	letter = (*stack)->n;

	if (letter >= 0 && letter <= 255)
	{
		putchar(letter);
		putchar('\n');
	}
	else
	{
		fprintf(stderr, "L<line_number>: can't pchar, value out of range,\n");
		exit(EXIT_FAILURE);
	}
}

/**
 * pstr - entry point
 * @stack: stack_t variable
 * @line_number: unsigned int variable
*/

void pstr(stack_t **stack, unsigned int line_number)
{
	int string;
	stack_t *tmp;
	(void)line_number;

	if (stack == NULL)
	{
		fprintf(stderr, "L<line_number>: can't pchar, stack empty\n");
		exit(EXIT_FAILURE);
	}

	tmp = *stack;
	while (tmp)
	{
		string = (*stack)->n;
		if (string > 0 && string <= 127)
			putchar(string);
		else
			break;
		tmp = tmp->next;
	}
	putchar('\n');
}

