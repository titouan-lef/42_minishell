/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:54:18 by lguerbig          #+#    #+#             */
/*   Updated: 2024/12/19 13:36:49 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef enum e_token
{
	TOKEN_PIPE,
	TOKEN_P_OPEN,
	TOKEN_P_CLOSE,
	TOKEN_WORD,
	TOKEN_REDIR,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_UNKNOWN
} t_token;

char*	get_token_name(t_token token)
{
	if (token == TOKEN_PIPE)
		return "PIPE";
	if (token == TOKEN_P_OPEN)
		return "P_OPEN";
	if (token == TOKEN_P_CLOSE)
		return "P_CLOSE";
	if (token == TOKEN_WORD)
		return "WORD";
	if (token == TOKEN_REDIR)
		return "REDIR";
	if (token == TOKEN_AND)
		return "AND";
	if (token == TOKEN_OR)
		return "OR";
	return "UNKNOWN";
}
void	skip_spaces(const char *input, int *index)
{
	while (isspace(input[*index]))
		(*index)++;
}


void	get_word(const char *input, int *index, char *buffer)
{
	int start = *index;
	while (input[*index] && input[*index] != '|' && input[*index] != '('
		&& input[*index] != ')' && input[*index] != '&' && input[*index] != '<'
		&& input[*index] != '>' && input[*index] != ' ')
		(*index)++;
	strncpy(buffer, input + start, *index - start);
	buffer[*index - start] = '\0';
}

t_token	get_token(const char *input, int *index, char *outputBuffer)
{
	char current = input[*index];
	char wordBuffer[256] = {0};

	skip_spaces(input, index);
	current = input[*index];
	if (current == '|')
	{
		(*index)++;
		if (input[*index] == '|')
		{
			(*index)++;
			return TOKEN_OR;
		}
		return TOKEN_PIPE;
	}
	if (current == '(')
	{
		(*index)++;
		return TOKEN_P_OPEN;
	}
	if (current == ')') 
	{
		(*index)++;
		return TOKEN_P_CLOSE;
	}
	if (current == '<' || current == '>')
	{
		char redir = current;
		(*index)++;
		skip_spaces(input, index);
		get_word(input, index, wordBuffer);
		sprintf(outputBuffer, "%c%s", redir, wordBuffer);
		return TOKEN_REDIR;
	}
	if (current == '&')
	{
		(*index)++;
		if (input[*index] == '&')
		{
			(*index)++;
			return TOKEN_AND;
		}
	}

	if (input[*index] && input[*index] != '|' && input[*index] != '('
		&& input[*index] != ')' && input[*index] != '&' && input[*index] != '<'
		&& input[*index] != '>' && input[*index] != ' ')
	{
		get_word(input, index, wordBuffer);
		strcpy(outputBuffer, wordBuffer);
		return TOKEN_WORD;
	}
	(*index)++;
	return TOKEN_UNKNOWN;
}

void	auto_tokenizer(const char *input)
{
	int index = 0;
	t_token token;
	char buffer[100];

	printf("inputs : %s\n", input);
	printf("detected tokens :\n");

	while (input[index] != '\0')
	{
		memset(buffer, 0, sizeof(buffer));
		token = get_token(input, &index, buffer);
		printf(" - %s", get_token_name(token));
		if (strlen(buffer) > 0)
			printf(" : %s", buffer);
		printf("\n");
	}
	printf("end of lexical analysys.\n");
}

int main(void)
{
	int num_inputs;
	char *inputs[] = {
		"echo hello > file",
		"(ls -l) | grep test",
		"cat < input.txt && echo done",
		"echo 'hello world' || echo 'error'",
		"command && (nested command)",
		"'cat' < in > out && echo Bpn'jour'"
	};

	num_inputs = sizeof(inputs) / sizeof(inputs[0]);
	for (int i = 0; i < num_inputs; i++)
	{
		printf("\nTest %d :\n", i + 1);
		auto_tokenizer(inputs[i]);
	}
	return 0;
}
