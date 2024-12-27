/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:54:18 by lguerbig          #+#    #+#             */
/*   Updated: 2024/12/27 16:43:31 by lguerbig         ###   ########.fr       */
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
		if (test)
			sprintf(output_buffer, "%c%c", redir, redir);
		else
			sprintf(output_buffer, "%c", redir);
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

t_queue	auto_tokenizer(const char *input)
{
	int		index = 0;
	t_token	*token;
	t_queue	tokens;
	char	buffer[100];

	printf("detected tokens :\n");
	tokens = queue_create();
	while (input[index] != '\0')
	{
		token = (t_token *)malloc(sizeof(t_token));
		memset(buffer, 0, sizeof(buffer));
		token->name = get_token(input, &index, buffer);
		token->value = (char **)malloc(sizeof(char *) * 2);
		token->value [0] = buffer;
		token->value [1] = NULL;
		printf(" - %d", token->name);
		if (strlen(buffer) > 0)
			printf(" : %s", buffer);
		printf("\n");
		queue_push(&tokens, *token);
	}
	printf("end of lexical analysys.\n");
	return(tokens);
}

