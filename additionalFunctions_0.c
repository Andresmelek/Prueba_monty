#include "monty.h"

/**
 * freestack - enrty point
 * @stack: stack_t variable
*/

void freestack(stack_t **stack)
{
	stack_t *tmp;

	while ((*stack) != NULL)
	{
		tmp = (*stack);
		(*stack) = (*stack)->next;
		free(tmp);
	}
}
