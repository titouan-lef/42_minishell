/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:54:18 by lguerbig          #+#    #+#             */
/*   Updated: 2024/12/19 16:48:48 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef enum e_token_name
{
	TOKEN_PIPE,
	TOKEN_P,
	TOKEN_WORD,
	TOKEN_REDIR,
	TOKEN_OPE,
} t_token_name;

// return of lexer is a list(chained) of t_tokens
typedef struct s_token
{
	t_token_name	name;
	char			**value;
}	t_token;

char	*get_token_name(t_token_name token)
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
	return "OPPER";
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

t_token	get_token(const char *input, int *index, char *output_buffer)
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
		get_word(input, index, word_buffer);
		sprintf(output_buffer, "%c%s", redir, word_buffer);
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
	get_word(input, index, word_buffer);
	strcpy(output_buffer, word_buffer);
	return TOKEN_WORD;
}

void	auto_tokenizer(const char *input)
{
	int index = 0;
	t_token token;
	char buffer[100];

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
	char buffer[100] = {0};
	int buffer_size;

	while (1)
	{
		buffer_size = read(1, buffer, 100);
		auto_tokenizer(buffer);
		printf("\n");
	}
	return 0;
}
