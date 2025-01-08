/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:49:43 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/08 18:16:13 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"
#include "commands.h"

/*
* Goal: Check if a there is an syntax error with parenthesis.
*
* Return: 0 if error, 1 if not.
*
* Warning: nb_par must not be null.
*/
int	valid_parenthesis(char *input)
{
	int		nb_par;

	nb_par = 0;
	while (*input)
	{
		if (*input == '(')
			nb_par++;
		if (*input == ')')
			nb_par--;
		if (nb_par < 0)
		{
			printf("syntax error near token '%c'\n", *input);
			return (0);
		}
		input++;
	}
	if (nb_par > 0)
	{
		printf("syntax error\n"); //heredoc ?
		return (0);
	}
	return (1);
}
