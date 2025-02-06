/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:05:16 by tle-floc          #+#    #+#             */
/*   Updated: 2025/02/06 18:39:57 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include <dirent.h>
# include "utils.h"

int		expand(char ***value, t_data *data, int is_redir);

/*---environement variable---*/
int		expand_env_var(char ***value, char **env, int is_redir);
char	*replace_word_env(char *word, char **env, int here_doc, int redir);
char	*get_quoted_value(char *name, char **env);

/*---exit status---*/
char	*replace_word_exit(char *word, int last_exit);
int		expand_exit_status(char ***value, int last_exit);

/*---tilde---*/
int		expand_tilde(char ***value, char **env, int is_redir);

/*---wildcard---*/
t_list	*find_matches(char *patern);
int		expand_wildcard(char ***value, int is_redir);
char	*replace_word_wildcard(char *patern);

/*---quote removal---*/
int		remove_quotes(char ***value);
char	*replace_word_quotes(char *word);

/*---utils---*/
t_token	split_command(t_queue tokens);
int		value_length_quoted(char *value);
void	quote_value(char *value, char *quoted_value, int *i);
int		update_quote(char **word, char *updated_word, int letter);

#endif