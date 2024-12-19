/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:54:18 by lguerbig          #+#    #+#             */
/*   Updated: 2024/12/19 22:41:29 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>
#include <ctype.h>

static void	skip_spaces(const char *input, int *index)
{
	while (isspace(input[*index]))
		(*index)++;
}

static void	get_word(const char *input, int *index, char *buffer)
{
	int start = *index;
	while (input[*index] && input[*index] != '|' && input[*index] != '('
		&& input[*index] != ')' && input[*index] != '&' && input[*index] != '<'
		&& input[*index] != '>' && input[*index] != ' ')
	{
		if (input[*index] == '\'')
		{
			(*index)++;
			while (input[*index] && input[*index] != '\'')
				(*index)++;
		}
		if (input[*index] == '"')
		{
			(*index)++;
			while (input[*index] && input[*index] != '"')
				(*index)++;
		}
		(*index)++;
	}
	strncpy(buffer, input + start, *index - start);
	buffer[*index - start] = '\0';
}

static t_token_name	get_token(const char *input, int *index, char *output_buffer)
{
	char current = input[*index];
	char word_buffer[100] = {0};

	skip_spaces(input, index);
	current = input[*index];
	if (current == '|')
	{
		(*index)++;
		if (input[*index] == '|')
		{
			(*index)++;
			return TOKEN_OPE;
		}
		return TOKEN_PIPE;
	}
	if (current == '(')
	{
		(*index)++;
		return TOKEN_PAR;
	}
	if (current == ')') 
	{
		(*index)++;
		return TOKEN_PAR;
	}
	if (current == '<' || current == '>')
	{
		char redir = current;
		int test = 0;
		(*index)++;
		if (input[*index] == current)
		{
			(*index)++;
			test = 1;
		}
		skip_spaces(input, index);
		get_word(input, index, word_buffer);
		if (test)
			sprintf(output_buffer, "%c%c%s", redir, redir, word_buffer);
		else
			sprintf(output_buffer, "%c%s", redir, word_buffer);
		return TOKEN_REDIR;
	}
	if (current == '&')
	{
		(*index)++;
		if (input[*index] == '&')
		{
			(*index)++;
			return TOKEN_OPE;
		}
	}
	get_word(input, index, word_buffer);
	strcpy(output_buffer, word_buffer);
	return TOKEN_WORD;
}

void	auto_tokenizer(const char *input)
{
	int index = 0;
	t_token_name token;
	char buffer[100];

	printf("detected tokens :\n");

	while (input[index] != '\0')
	{
		memset(buffer, 0, sizeof(buffer));
		token = get_token(input, &index, buffer);
		printf(" - %d", token);
		if (strlen(buffer) > 0)
			printf(" : %s", buffer);
		printf("\n");
	}
	printf("end of lexical analysys.\n");
}

