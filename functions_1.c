#include "monty.h"

/**
 * pop - entry point
 * @stack: stack_t variable
 * @line_number: unsigned int variable
*/

void pop(stack_t **stack, unsigned int line_number)
{
	(void)line_number;

	if ((*stack) == NULL)
	{
		fprintf(stderr, "L<%d>: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}

	if ((*stack)->next == NULL && (*stack)->prev == NULL)
		(*stack) = NULL;
	else
	{
		(*stack) = (*stack)->next;
		(*stack)->prev = NULL;
	}
}

/**
 * add - entry point
 * @stack: stack_t variable
 * @line_number: unsigned int variable
*/

void add(stack_t **stack, unsigned int line_number)
{
	unsigned int sum;
	(void)line_number;

	if ((*stack)->next == NULL && (*stack)->prev == NULL)
	{
		fprintf(stderr, "L<%d>: can't add, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	sum = (*stack)->n + (*stack)->next->n;

	pop(stack, 0);
	pop(stack, 0);
	push(stack, sum);
}

/**
 * sub - entry point
 * @stack: stack_t variable
 * @line_number: unsigned int variable
*/

void sub(stack_t **stack, unsigned int line_number)
{
	unsigned int res;
	(void)line_number;

	if ((*stack)->next == NULL && (*stack)->prev == NULL)
	{
		fprintf(stderr, "L<%d>: can't sub, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	res = (*stack)->next->n - (*stack)->n;

	pop(stack, 0);
	pop(stack, 0);
	push(stack, res);
}

/**
 * division - entry point
 * @stack: stack_t variable
 * @line_number: unsigned int variable
*/

void division(stack_t **stack, unsigned int line_number)
{
	unsigned int divide;
	(void)line_number;

	if ((*stack)->next == NULL && (*stack)->prev == NULL)
	{
		fprintf(stderr, "L<%d>: can't div, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	divide = (*stack)->next->n / (*stack)->n;

	pop(stack, 0);
	pop(stack, 0);
	push(stack, divide);
}

/**
 * mul - entry point
 * @stack: stack_t variable
 * @line_number: unsigned int variable
*/

void mul(stack_t **stack, unsigned int line_number)
{
	unsigned int power;
	(void)line_number;

	if ((*stack)->next == NULL && (*stack)->prev == NULL)
	{
		fprintf(stderr, "L<%d>: can't mul, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	power = (*stack)->next->n * (*stack)->n;

	pop(stack, 0);
	pop(stack, 0);
	push(stack, power);
}

