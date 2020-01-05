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
	unsigned int ln = 1;
	int file_read, i = 0, j = 0, cant_read;
	char buffer[1024], buff[1024];

	if (ac != 2)
		fprintf(stderr, "USAGE: monty file\n"), exit(EXIT_FAILURE);
	file_read = open(av[1], O_RDONLY, 0600);
	if (file_read == -1)
	{
		fprintf(stderr, "Error: Can't open file %s\n", av[1]);
		exit(EXIT_FAILURE);
	}

	while ((cant_read = read(file_read, buffer, 1024)) > 0)
	{
		i = 0;
		while (buffer[i] != '\0')
		{
			if (buffer[i] == '#')
				while (buffer[i] != '\n')
					i++;
			if (buffer[i] != '\n')
				buff[j] = buffer[i];
			else
			{
				buff[j] = '\0';
				is_opcode(buff, &st, ln);
				j = -1;
				ln++;
			}
			i++, j++;
		}
	}

	freestack(&st);
	if (close(file_read) == -1)
		exit(EXIT_FAILURE);

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
	if (cmds == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	cmd = strtok(buffer, delim);
	while (cmd != NULL && i < 2)
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
 * @ln: unsigned int variable
*/

void is_opcode(char *buff, stack_t **st, unsigned int ln)
{
	char **cmds;
	instruction_t opts[] = {
		{"push", push}, {"pall", pall}, {"pint", pint}, {"pop", pop},
		{"swap", swap}, {"nop", nop}, {"add", add}, {"sub", sub},
		{"div", division}, {"mul", mul}, {"mod", mod}, {"pchar", pchar},
		{"pstr", pstr},	{NULL, NULL}
	};
	int i = 0, j = 0, len, b = 0;

	cmds = parse(buff);
	while (cmds[i] != NULL)
	{
		j = 0;
		while (opts[j].opcode != NULL)
		{
			len = strlen(opts[j].opcode);
			if (strncmp(opts[j].opcode, cmds[i], len) == 0)
			{ b = 1;
				if (j == 0)
					check_push(st, cmds, ln);
				else
					opts[j].f(st, ln);
				break; }
			j++;
		}
		if (b == 0)
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", ln, cmds[i]);
			free(cmds), freestack(st);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	free(cmds);
}

/**
 * check_push - entry point
 * @st: stack_t variable
 * @cmds: char variable
 * @ln: unsigned int
*/

void check_push(stack_t **st, char **cmds, unsigned int ln)
{
	int i = 0, b = 0;
	char *cmds1;

	if (cmds[1] == NULL)
	{
		fprintf(stderr, "L%d: usage: push integer\n", ln);
		free(cmds), freestack(st);
		exit(EXIT_FAILURE);
	}
	cmds1 = cmds[1];
	while (cmds1[i] != '\0')
	{
		if (cmds1[0] == '-' && b == 0)
			i++, b = 1;
		if (_isdigit(cmds1[i]) == 0)
		{
			fprintf(stderr, "L%d: usage: push integer\n", ln);
			free(cmds), freestack(st);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	push(st, atoi(cmds1));
}
