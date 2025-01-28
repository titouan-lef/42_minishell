/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:58:36 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/28 21:47:30 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include "commands.h"
# include <readline/readline.h>
# include <readline/history.h>

/*---display.c---*/
char	*rl_gets(char **env);
void	print_tokens(t_queue *tokens);
char	*get_prompt(char **env);

#endif