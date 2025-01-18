/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:23:35 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/18 18:13:03 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <linux/limits.h>
# include <fcntl.h>
# include <limits.h>
# include "libft.h"

# define NAME "minishell"
/*---Error messages---*/
# define HERDOC_END "warning: here-document delimited by end-of-file"
# define HERDOC_ACC "error here_doc access"
# define MALLOC "malloc error"
# define FORK "fork failed"
# define NO_FILE "No such file or directory"
# define NO_CMD "Command not found"

/*---tab_utils.c---*/
int		size_tab(char **tab);
char	**tab_join(char **tab1, char **tab2);
char	**tab_join_and_free(char **tab1, char **tab2);
char	**append_to_tab(char **tab, const char *str);

#endif