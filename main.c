#include "monty.h"

/**
 * main - entry point
 * @ac: int variable
 * @av: char variable
 *
 * Return: 0
*/

int main(int ac, char **av)
{
	stack_t *st = NULL;
	int file_read, i = 0, j = 0, cant_read;
	char buffer[1024], buff[1024];

	if (ac != 2)
		dprintf(STDERR_FILENO, "Usage: ./monty <file>.m\n"), exit(EXIT_FAILURE);
	file_read = open(av[1], O_RDONLY, 0600);
	if (file_read == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", av[1]);
		exit(EXIT_FAILURE);
	}

	while ((cant_read = read(file_read, buffer, 1024)) > 0)
	{
		i = 0;
		while (buffer[i] != '\0')
		{
			if (buffer[i] != '\n')
				buff[j] = buffer[i];
			else
			{
				buff[j] = '\0';
				is_opcode(buff, &st);
				j = -1;
			}
			i++, j++;
		}
	}

	return (0);
}

/**
 * parse - entry point
 * @buffer: char variable
 *
 * Return: cmds
*/

char **parse(char *buffer)
{
	char **cmds, *cmd, *delim;
	int i = 0;

	delim = "\t \r\a";
	cmds = malloc(sizeof(char *) * 3);

	cmd = strtok(buffer, delim);
	while (cmd != NULL)
	{
		cmds[i] = cmd;
		cmd = strtok(NULL, delim);
		i++;
	}
	cmds[i] = NULL;
	return (cmds);
}

/**
 * is_opcode - entry point
 * @buff: char variable
 * @st: stack_t variable
*/

void is_opcode(char *buff, stack_t **st)
{
	char **cmds;

	instruction_t opts[] = {
		{"push", push},
		{"pall", pall},
		{"pint", pint},
		{"pop", pop},
		{"swap", swap},
		{"nop", nop},
		{"add", add},
		{"sub", sub},
		{"div", division},
		{"mul", mul},
		{"mod", mod},
		{"pchar", pchar},
		{NULL, NULL}
	};
	int i = 0, j = 0, len, b;

	cmds = parse(buff);
	while (cmds[i] != NULL)
	{
		j = 0;
		while (opts[j].opcode != NULL)
		{
			len = strlen(cmds[i]);
			if (strncmp(opts[j].opcode, cmds[i], len) == 0)
			{
				b = 1;
				if (j == 0)
					opts[j].f(st, atoi(cmds[1]));
				else
					opts[j].f(st, 0);
				break;
			}
			j++;
		}
		i++;
	}
	b = b;
}

