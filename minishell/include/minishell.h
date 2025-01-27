/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:23:35 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/27 15:37:48 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <linux/limits.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include "libft.h"

# define NAME "minishell"
/*---Error messages---*/
# define ERR_HERDOC_END "warning: here-document delimited by end-of-file"
# define ERR_HERDOC_ACC "error heredoc access"
# define ERR_MALLOC "malloc failed"
# define ERR_FORK "fork failed"
# define ERR_DUP "dup failed"
# define ERR_DUP2 "dup2 failed"
# define ERR_NO_FILE "No such file or directory"
# define ERR_NO_CMD "Command not found"
# define ERR_SYNTAX_START ": syntax error near unexpected token `"
# define ERR_SYNTAX_END "'"
# define ERR_RND "Impossible to geneate a here_doc name"

/*---tab_utils.c---*/
size_t	size_tab(char **tab);
char	**strdup_tab(char **tab);
char	**tab_join(char **tab1, char **tab2);
char	**tab_join_and_free(char **tab1, char **tab2);
char	**append_to_tab(char **tab, const char *str);

/*---signals.c---*/
int		here_doc_sigaction(struct sigaction *act);
int		cmd_display_sigaction(struct sigaction *act);
int		default_sigaction(struct sigaction *act);
int		interactive_mode_sigaction(struct sigaction *act);

#endif